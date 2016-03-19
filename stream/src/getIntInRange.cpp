#include <exception>

#include "utility/stream.hpp"

/**
 * @details 
 * This function should be used when the next string in a stream is required 
 * to be an integer value, but may not exist. If a string cannot be extracted 
 * from the stream (end of file), the *found* flag is set to false and zero is 
 * returned. Otherwise the *found* flag is set to true. If a string is extracted 
 * and isn't an integer value or is outside the bound arguments, this method 
 * records an error via the logger specifying the variable name (see the *name* 
 * argument) and error type and throws an exception.
 */
int 
utility::stream::getIntInRange(std::istream& is, 
			       const std::string& name, 
			       const int lBound,
			       const int rBound,
			       bool& found){
  const int integer = utility::stream::getInteger(is, name, found);
  if ( found && 
       ((integer < lBound) || (integer >= rBound)) ) {
    LOG(ERROR) << name << " argument must be be ϵ [ " << lBound << ", " << rBound << " )"; 
    throw std::exception();
  }
  return integer;
}

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an integer value. If a string cannot be extracted, isn't an integer value,
 * or is outside the bound arguments, this method records an error via the logger
 * specifying the variable name (see the name argument) and error type and throws
 * an exception.
 */
int 
utility::stream::getIntInRange( std::istream& is, 
				const std::string& name,
				const int lBound,
				const int rBound){
  bool found;
  const int integer = utility::stream::getIntInRange(is, name, lBound, rBound, found);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return integer;
}
