typename Traits::int_type 
overflow( typename Traits::int_type ch ){
  if ( ch != Traits::eof() ){
    *this->pptr() = ch;
    this->pbump(1);
    if ( this->flush() ){ return ch; }
  }

  return Traits::eof();
}

