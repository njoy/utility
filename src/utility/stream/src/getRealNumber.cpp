#include "utility.hpp"

/** 
 * @details
 * This function should be used when the next string in a stream is required to 
 * be a real number value, but may not exist. If a string cannot be extracted 
 * from the stream (end of file), the *found* flag  is set to false and 0.0 is 
 * returned. Otherwise the *found* flag is set to true. If a string extracted 
 * but isn't a real number value, this method records an error via the logger 
 * specifying the variable name (see the *name* argument) and throws an 
 * exception. This function recognizes any real number string format acceptable 
 * in fortran read statements.
 */
double 
njoy::utility::stream::getRealNumber
( std::istream& is, const std::string& name, bool& found ){
  std::string staging;
  is >> staging;
  found = not is.fail();
  if ( not found ){
    return 0.0;
  } else if ( not ( utility::string::isRealNumber( staging ) ) ){
    njoy::Log::error( "{} argument must be an real number value", name );
    throw std::exception();
  } 
  return string::toDouble(staging);
}

/** 
 * @details 
 * This function should be used when the next string in a stream is required to 
 * be an integer value. If a string cannot be extracted from the stream (end of 
 * file) or the string isn't a real number value, this method records an error 
 * via the logger specifying the variable name (see the *name* argument) and the 
 * sort of failure and throws an exception. This function recognizes any real 
 * number string format acceptable in fortran read statements.
 */
double 
njoy::utility::stream::getRealNumber
( std::istream& is, const std::string& name ){
  double realNumber; 
  bool found;
  realNumber = getRealNumber( is, name, found );
  if ( not found ){
    njoy::Log::error( "{} argument could not be read from input.", name );
    throw std::exception();
  } 
  return realNumber;
}
