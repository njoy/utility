virtual ~basic_FILE_streambuf(){
  this->flush();
  fclose( this->filePtr );
}

