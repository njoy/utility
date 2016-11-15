bool flush(){
  std::ptrdiff_t n = this->pptr() - this->pbase();
  this->pbump(-n);
  return n == int( 
      std::fwrite( this->pbase(), sizeof(Char_t), n, this->filePtr ) );
}

