#include <exception>

#include "utility/stream.hpp"
#include "utility/string.hpp"

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
utility::stream::getInteger( std::istream& is, 
			     const std::string& name, 
			     bool& found ){
  std::string staging;
  is >> staging;
  found = !is.fail();
  if (!found){
    return 0; 
  } else if ( !(utility::string::isInteger(staging)) ){
    LOG(ERROR) << name << " argument must be an integer value";
    throw std::exception();
  } 
  return std::stoi(staging);
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
utility::stream::getInteger(std::istream& is, 
			    const std::string& name ){
  bool found;
  const int integer = utility::stream::getInteger(is, name, found);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return integer;
}
