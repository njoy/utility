template< typename LeftTag,
	  typename Char_t, typename Traits = std::char_traits< Char_t > >
class basic_Tee_streambuf;

template< typename Char_t, typename Traits >
class basic_Tee_streambuf< InputTag, Char_t, Traits > :
  public std::basic_streambuf< Char_t, Traits >{

  static constexpr std::size_t flushThreshold = 64;
  std::deque< Char_t > buffer {0};
  std::basic_streambuf< Char_t, Traits >& left;
  std::basic_streambuf< Char_t, Traits >& right;
  
  template< typename T >
  T& dereference( T* t, bool isLeft ){
    if ( not t ){ throw isLeft; }
    return *t;
  }
  
public:
  using int_type = typename Traits::int_type;
  
  basic_Tee_streambuf( std::basic_streambuf< Char_t, Traits >* leftPtr,
		       std::basic_streambuf< Char_t, Traits >* rightPtr )
  try :
    left( dereference( leftPtr, true ) ),
    right( dereference( rightPtr, false ) ){
      auto begin = &( this->buffer.front() );
      auto end = begin + 1;
      this->setg( begin, end, end );
    }
  catch( bool b ){
    if ( b ){
      Log::error("nullptr passed in place of left streambuf pointer");
    } else {
      Log::error("nullptr passed in place of right streambuf pointer");
    }
    Log::info("Error while constructing basic_Tee_streambuf");
    throw std::exception();
  } catch( std::exception& e ){
    Log::info("Error while constructing basic_Tee_streambuf");
    throw e;
  }

  virtual ~basic_Tee_streambuf(){
    this->sync();
  }
  
private:    
  int sync(){
    const int leftFailure = this->left.pubsync();
    this->buffer.pop_front();
    while ( this->buffer.size() ){
      this->right.sputc( this->buffer.front() );
      this->buffer.pop_front();
    }
    this->buffer.push_front( 0 );
    auto right = &( this->buffer.back() );
    this->setg( right, right, right + 1 );
    const int rightFailure = this->right.pubsync();
    return leftFailure || rightFailure ? -1 : 0;
  }

  int_type underflow(){
    auto ch = this->left.sbumpc();
    if ( ch != Traits::eof() ){
      this->buffer.push_back( ch );
      if ( this->buffer.size() > flushThreshold ){
	this->buffer.pop_front();
	this->right.sputc( this->buffer.front() );
	this->buffer.front() = 0;
      }
      auto right = &( this->buffer.back() );
      this->setg( right, right, right + 1 );
      return Traits::to_int_type( ch );
    }
    return Traits::eof();
  }

  int_type pbackfail ( int c = Traits::eof() ){
    if ( this->buffer.size() < 2 ){ return Traits::eof(); }
    auto trial = this->left.sputbackc( c );
    if ( trial != Traits::eof() ){
      this->buffer.pop_back();
      this->buffer.push_back( c );
      auto right = &( this->buffer.back() );
      this->setg( right, right, right + 1 );
    } else {
      return not trial;
    }
    return trial;
  }
};
