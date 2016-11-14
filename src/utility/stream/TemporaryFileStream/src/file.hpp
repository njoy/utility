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

