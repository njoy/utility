basic_TeeStream( const basic_TeeStream& ) = delete;
basic_TeeStream( basic_TeeStream&& other ){
  this->rdbuf() = other.rdbuf();
  other.rdbuf( nullptr );
}
