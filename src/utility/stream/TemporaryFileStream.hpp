template < class Char_t, class Traits = std::char_traits< Char_t > >
class TemporaryFileStream : public std::basic_ostream< Char_t, Traits > {
public:
  TemporaryFileStream( int n = 100)
    try : TemporaryFileStream( file(n) ) {}
    catch ( std::exception& e ){
      /* Log error */
      throw e;
    }

  virtual ~TemporaryFileStream(){
    delete this->rdbuf();
    std::remove( this->filename.c_str() );
  }
  
  const std::string filename;

private:

  static std::string path(){
    #ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #endif
    return std::tmpnam( nullptr );
    #ifdef __GNUC__
    #pragma GCC diagnostic pop
    #endif
  }

  static auto file(int n){
    std::pair< std::string, FILE_streambuf<Char_t>* > result;
    FILE* ptr = nullptr;
    while( ( ptr == nullptr ) and n-- ){
      result.first = path();
      ptr = fopen(result.first.c_str(), "wx");
    };

    if( ptr == nullptr ){
      Log::error("Unable to create a unique filename after {} tries", n);
      throw std::exception();
    }
    result.second = new FILE_streambuf<Char_t>(ptr);
    return result;
  }

  TemporaryFileStream( std::pair<std::string, FILE_streambuf<Char_t>*> pair ) :
    std::basic_ostream< Char_t, Traits >( pair.second ),
    filename( pair.first ){}

};


