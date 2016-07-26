#include "utility.hpp"

std::string
utility::slurpFileToMemory( const std::string& path ){
  std::string sink;
  std::ifstream input( path, std::ios::in | std::ios::binary );
  if ( not input ){
    LOG(ERROR) << "File could not opened for reading";
    LOG(INFO) << "Specified file path: " << path;
    LOG(INFO) << "Error while slurping file to memory";
    throw std::runtime_error("input file could not be opened");
  }
  input.seekg( 0, std::ios::end );
  std::streampos file_size = input.tellg();
  input.seekg( 0, std::ios::beg );
  sink.resize( file_size / sizeof(char) );
  input.read( &( sink[ 0 ] ), file_size );
  return sink;
}
