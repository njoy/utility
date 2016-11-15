virtual ~TemporaryFileStream(){
  if ( this->rdbuf() ){
    delete this->rdbuf();
    std::remove( this->filename.c_str() );
  }
}
