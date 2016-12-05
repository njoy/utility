virtual ~basic_RecordOrientedStream(){
  if ( this->rdbuf() ){ delete this->rdbuf(); }
}
