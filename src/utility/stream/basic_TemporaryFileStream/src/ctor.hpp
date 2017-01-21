private:

basic_TemporaryFileStream
( std::pair<std::string, basic_FILE_streambuf<Char_t>*> pair ) :
  std::basic_ostream< Char_t, Traits >( pair.second ),
  filepath( pair.first ){}

public:

basic_TemporaryFileStream( int n = 100 )
  try : basic_TemporaryFileStream( file( n ) ) {}
  catch ( std::exception& e ){
    Log::info( "Error while constructing basic_TemporaryFile" );
    throw e;
  }

basic_TemporaryFileStream( const basic_TemporaryFileStream & ) = delete;
basic_TemporaryFileStream( basic_TemporaryFileStream && other ) :
  std::basic_ostream< Char_t, Traits >( other.rdbuf() ){
  other.rdbuf( nullptr );
  this->filepath = std::move( other.filepath );
}
