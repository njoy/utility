virtual ~basic_TemporaryFileStream(){
  if ( this->rdbuf() ){
    delete this->rdbuf();
    std::remove( this->filepath.c_str() );
  }
}
