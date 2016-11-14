virtual ~FILE_streambuf(){
  this->flush();
  fclose( this->filePtr );
}

