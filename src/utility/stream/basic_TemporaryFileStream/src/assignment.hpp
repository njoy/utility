basic_TemporaryFileStream&
operator=( const basic_TemporaryFileStream& ) = delete;

basic_TemporaryFileStream&
operator=( basic_TemporaryFileStream&& other ){
  if ( this->rdbuf() ){ delete this->rdbuf(); }

  this->rdbuf() = other.rdbuf();
  other.rdbuf( nullptr );
  this->path = std::move( other.path );
}
