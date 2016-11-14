virtual ~TemporaryFileStream(){
  delete this->rdbuf();
  std::remove( this->filename.c_str() );
}
