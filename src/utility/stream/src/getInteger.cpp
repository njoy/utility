#include "utility.hpp"

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an integer value, but may not exist. If a string cannot be extracted from 
 * the stream (end of file), the found is set to false and 0 is returned. 
 * Otherwise the found flag is set to true. If a string extracted and isn't an 
 * integer value, this method records an error via the logger specifying the 
 * variable name (see the name argument) and throws an exception.
 */
int 
njoy::utility::stream::getInteger
( std::istream& is, const std::string& name, bool& found ){
  std::string staging;
  is >> staging;
  found = not is.fail();
  if ( not found ){
    return 0; 
  } else if ( not ( string::isInteger( staging ) ) ){
    njoy::Log::error( "{} argument must be an integer value", name );
    throw std::exception();
  } 
  return std::stoi( staging );
}

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an integer value. If a string cannot be extracted from the stream (end of 
 * file) or the string isn't an integer value, this method records an error via
 * the logger specifying the variable name (see the name argument) and the sort 
 * of failure and throws an exception.
 */
int 
njoy::utility::stream::getInteger( std::istream& is, const std::string& name ){
  bool found;
  const int integer = getInteger( is, name, found );
  if ( not found ){
    njoy::Log::error( "{} argument could not be read from input.", name );
    throw std::exception();
  } 
  return integer;
}
