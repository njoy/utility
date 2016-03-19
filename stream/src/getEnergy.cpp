#include <exception>

#include "utility/stream.hpp"

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an energy value, but the string argument may not exist. If a string cannot
 * be extracted from the stream (end of file), the *found* flag is set to false and
 * 0.0 is returned. If the string isn't a positive real number, this method 
 * records an error via the logger specifying the sort of failure and throws an 
 * exception.
 */
double
utility::stream::getEnergy( std::istream& is,
			    bool& found,
			    const std::string& name ){
  const double energy = utility::stream::getRealNumber(is, name, found);
  if (found && (energy < 0) ){
    LOG(ERROR) << name << " must be greater tha 0 eV";
    throw std::exception();
  }
  return energy;
}

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an energy value. If a string cannot be extracted from the stream (end of 
 * file) or the string isn't a positive real number, this method records an 
 * error via the logger specifying the sort of failure and throws an exception.
 */ 
double
utility::stream::getEnergy( std::istream& is,
			    const std::string& name ){
  bool found;
  const double energy = utility::stream::getEnergy(is, found, name);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  }
  return energy;
}
