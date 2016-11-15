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

