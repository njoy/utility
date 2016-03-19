#include <exception>

#include "utility/stream.hpp"

/** 
 * @details 
 * This function should be used when the next string in a stream is required 
 * to be an integer value, but may not exist. If a string  cannot be extracted 
 * from the stream (end of file), the *found* flag is set to false and zero is 
 * returned. Otherwise the *found* flag is set to true. If a string is extracted 
 * and isn't an integer value or is less than the *bound* argument, this method 
 * records an error via the logger specifying the variable name (see the name 
 * argument) and error type and throws an exception.
 */
int 
utility::stream::getIntWithLBound( std::istream& is, 
				   const std::string& name, 
				   const int bound, 
				   bool& found ){
  const int integer = utility::stream::getInteger(is, name, found);
  if ( found && 
       (integer < bound) ) {
    LOG(ERROR) << name << " argument must be greater than or equal to " << bound;
    throw std::exception();
  }
  return integer;
}

/** 
 * @details 
 * This function should be used when the next string in a stream is required to
 * be an integer value. If a string cannot be extracted from the stream (end of 
 * file), if the extracted string isn't an integer value, or is less than the 
 * bound argument, this method records an error via the logger specifying the 
 * variable name (see the name argument) and error type and throws an exception.
 */
int 
utility::stream::getIntWithLBound( std::istream& is, 
				   const std::string& name, 
				   const int bound ){
  bool found;
  const int integer = utility::stream::getIntWithLBound(is, name, bound, found);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return integer;
}
