basic_TeeStream&
operator=( const basic_TeeStream& ) = delete;

basic_TeeStream&
operator=( basic_TeeStream&& other ){
  if ( this->rdbuf() ){ delete this->rdbuf(); }

  this->rdbuf() = other.rdbuf();
  other.rdbuf( nullptr );
}
