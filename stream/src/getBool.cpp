#include <exception>

#include "utility/stream.hpp"

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be a boolean value, but may not exist. If a string cannot be extracted from 
 * the stream (end of file), the *found* is set to false and false is returned. 
 * Otherwise the *found* flag is set to true. If a string is extracted but isn't 
 * a boolean value, this method records an error via the logger specifying the 
 * variable name (see the *name* argument) and throws an exception.
 *
 * Although fortran has accepted boolean variable (called logical variables in 
 * fortran) as **t** / **f** (and variants thereof) for 25 years at the time of 
 * writing this, NJOY2012 still reads and stores boolean variables as integers, 
 * with 0 corresponding to false and 1 corresponding to true.
 *
 * NJOY21 will support reading boolean variables this way for backwards 
 * compatability reasons
 */
bool 
utility::stream::getBool( std::istream& is, 
			  const std::string& name, 
			  bool& found ){
  const int test = utility::stream::getInteger(is, name, found);
  if (found && ((test < 0) || (test > 1))){
    LOG(ERROR) << name << " argument acts as a boolean and must assume a value of 1 or 0";
    throw std::exception();
  }
  return test;
}

/** 
 * @details
 * This function should be used when the next string in a stream is required to 
 * be a boolean value. If a string cannot be extracted from the stream (end of 
 * file) or the string isn't a boolean value, this method records an error via 
 * the logger specifying the variable name (see the *name* argument) and the sort
 * of failure and throws an exception.
 * Although fortran has accepted boolean variable (called logical variables in 
 * fortran) as **t** / **f** (and variants thereof) for 25 years at the time of 
 * writing this, NJOY2012 still reads and stores boolean variables as integers, 
 * with 0 corresponding to false and 1 corresponding to true.
 *
 * NJOY21 will support reading boolean variables this way for backwards 
 * compatability reasons
 */
bool 
utility::stream::getBool( std::istream& is, 
			  const std::string& name ){
  bool found;
  const bool test = utility::stream::getBool(is, name, found);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return test;
}
