typename Traits::int_type underflow(){
  if ( this->gptr() < this->egptr() ){
    return Traits::to_int_type( *( this->gptr() ) );
  }
  char* base = &( this->buffer.front() );
  char* start = base;

  if ( this->eback() == base ){
    std::memmove( base, this->egptr() - this->putBack, this->putBack );
    start += this->putBack;
  }

  std::size_t nConsumedCharacters = std::fread( 
      start, sizeof(Char_t), this->buffer.size() - (start - base), filePtr );
  if ( not nConsumedCharacters ){ 
    return Traits::eof(); 
  }

  this->setg( base, start, start + nConsumedCharacters);
  return Traits::to_int_type( *(this->gptr() ) );
}

