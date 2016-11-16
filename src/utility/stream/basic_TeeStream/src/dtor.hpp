virtual ~basic_TeeStream(){
  if ( this->rdbuf() ){ delete this->rdbuf(); }
}
