#include <exception>

#include "utility/stream.hpp"

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an absolute temperature value, but the string argument may not exist. If a
 * string cannot be extracted from the stream (end of file), the *found* flag is
 * set to false and 0.0 is returned. If the string isn't a positive real number,
 * this method records an error via the logger specifying the sort of failure 
 * and throws an exception.
 */
double
utility::stream::getTemperature( std::istream& is,
				 bool& found,
				 const std::string& name ){
  const double tempd = utility::stream::getRealNumber(is, name, found);
  if (found && 
      (tempd < 0) ){
    LOG(ERROR) << name << " must be greater tha 0 K";
    throw std::exception();
  }
  return tempd;
}

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an absolute temperature value. If a string cannot be extracted from the
 * stream (end of file) or the string isn't a positive real number, this method 
 * records an error via the logger specifying the sort of failure and throws an 
 * exception.
 */
double
utility::stream::getTemperature( std::istream& is,
				 const std::string& name ){
  bool found;
  const double tempd = utility::stream::getTemperature(is, found, name);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return tempd;
}
