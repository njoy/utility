static auto file( int n ){
  std::pair< std::string, basic_FILE_streambuf<Char_t>* > result;
  FILE* ptr = nullptr;
  while( ( not ptr ) and n-- ){
    result.first = path();
    ptr = fopen( result.first.c_str(), "wx" );
  };

  if( not ptr ){
    Log::error( "Unable to create a unique name for temporary file" );
    Log::info( "{} attempts made", n );
    throw std::exception();
  }
  result.second =
    std::make_unique< basic_FILE_streambuf<Char_t> >(ptr).release();
  return result;
}

