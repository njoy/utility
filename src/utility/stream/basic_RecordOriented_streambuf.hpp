template< typename IOTag,
	  typename Char_t, typename Traits = std::char_traits< Char_t > >
class basic_RecordOriented_streambuf;

template< typename Char_t, typename Traits >
class basic_RecordOriented_streambuf< InputTag, Char_t, Traits > :
  public std::basic_streambuf< Char_t, Traits >{

  std::basic_streambuf< Char_t, Traits >& core;
  std::basic_string< Char_t, Traits >& buffer;
  long& lineNumber;
  Char_t psuedo;
  
public:
  using int_type = typename Traits::int_type;
  
  basic_RecordOriented_streambuf
  ( std::basic_streambuf< Char_t, Traits >& core,
    std::basic_string< Char_t >& buffer,
    long& lineNumber )
  try :
    core( core ),
    buffer( buffer ),
    lineNumber( lineNumber ){
      auto begin = &( this->psudo );
      auto end = begin + 1;
      this->setg( begin, end, end );
  } catch ( std::exception& e ){
    throw e;
  }
  
  virtual ~basic_RecordOriented_streambuf(){ this->sync(); }
  
private:    
  int sync(){ return this->core.pubsync(); }

  int_type underflow(){
    auto ch = this->core.sbumpc();
    if ( ch != Traits::eof() ){
      this->pseudo = ch;
      if ( this->pseudo == '\n' ){
	this->buffer.clear();
	++lineNumber;
      }
      if ( ch != '\n' ){
	this->buffer.push_back( ch );
      }
      auto begin = &( this->pseudo );
      auto end = begin + 1;
      this->setg( begin, begin, end );
      return Traits::to_int_type( ch );
    }
    return Traits::eof();
  }

  int_type pbackfail ( int c = Traits::eof() ){
    if ( this->buffer.empty() ){ return Traits::eof(); }
    auto trial = this->left.sputbackc( c );
    if ( trial != Traits::eof() ){
      this->buffer.pop_back();
      auto begin = &( this->pseudo );
      auto end = begin + 1;
      this->setg( begin, begin, end );
    } else {
      return not trial;
    }
    return trial;
  }
  
};

