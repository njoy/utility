template< typename IOTag,
	  typename Char_t, typename Traits = std::char_traits< Char_t > >
class basic_RecordOriented_streambuf;

template< typename Char_t, typename Traits >
class basic_RecordOriented_streambuf< InputTag, Char_t, Traits > :
  public std::basic_streambuf< Char_t, Traits >{

  std::basic_streambuf< Char_t, Traits >& core;
  std::basic_string< Char_t, Traits >& buffer;
  long& lineNumber;
  Char_t pseudo = 0;
  
public:
  using int_type = typename Traits::int_type;
  
  basic_RecordOriented_streambuf
  ( std::basic_streambuf< Char_t, Traits >& core,
    std::basic_string< Char_t >& buffer,
    long& lineNumber ) :
    core( core ),
    buffer( buffer ),
    lineNumber( lineNumber ){
      auto begin = &( this->pseudo );
      auto end = begin + 1;
      this->setg( begin, end, end );
  }
  
  virtual ~basic_RecordOriented_streambuf(){ this->sync(); }
  
private:    
  int sync(){ return this->core.pubsync(); }

  int_type underflow(){
    auto ch = this->core.sbumpc();
    if ( ch != Traits::eof() ){
      if( this->pseudo ){
	this->buffer.push_back( this->pseudo );
	if ( this->buffer.back() == '\n' ){
	  this->buffer.clear();
	  ++lineNumber;
	}
      }
      this->pseudo = ch;
      auto begin = &( this->pseudo );
      auto end = begin + 1;
      this->setg( begin, begin, end );
      return Traits::to_int_type( ch );
    } else {
      if( this->pseudo ){
	this->buffer.push_back( this->pseudo );
	this->pseudo = 0;
      }
    }
    return Traits::eof();
  }

  int_type pbackfail ( int c = Traits::eof() ){
    if ( this->buffer.empty() ){
      return Traits::eof();
    }
    auto trial = this->core.sputbackc( c );
    if ( trial != Traits::eof() ){
      if ( not this->buffer.empty() ){
	this->pseudo = this->buffer.back();
	this->buffer.pop_back();
      } else {
	this->pseudo = 0;
      }
      auto begin = &( this->pseudo );
      auto end = begin + 1;
      this->setg( begin, begin, end );
    } else {
      return not trial;
    }
    return trial;
  }
  
};

