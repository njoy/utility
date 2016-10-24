#include "utility.hpp"

using namespace utility::stream;

/** 
 * @param is A stream which a real number is to be extracted.
 * @param[in] name The name of the variable to be read from stream. Used when
 *                 logging information before throwing an exception. 
 * @param[in] bound The (inclusive) lower of real values that may be read 
 *                  without throwing an exception. 
 * @param[out] found Records whether a value could read from stream. If EOF is
 *                   encountered before a value can be read, **found** is set to
 *                   false. Otherwise, **found** is set to true.
 * @result When found and not in error, the real number value read from the input
 *         stream **in**. Otherwise, returns zero.
 *
 * @details 
 * This function should be used when the next string in a stream is required 
 * to be an real number value, but may not exist. If a string cannot be extracted 
 * from the stream (end of file), the **found** flag is set to false and zero is 
 * returned. Otherwise the **found** flag is set to true. If a string is extracted 
 * and isn't a real number value or is less than the **bound** argument, this method 
 * records an error via the logger specifying the variable name (see the **name** 
 * argument) and error type and throws an exception.
 */
double 
getRealWithLBound( std::istream& is, const std::string& name,
		   const double bound, bool& found ){
  const double realNumber = getRealNumber( is, name, found );
  if ( found && ( realNumber < bound ) ) {
    Log::error( "{} argument must be greater than or equal to {}",
		name, bound );
    throw std::exception();
  }
  return realNumber;
}

/** 
 * @param is A stream which a real number is to be extracted.
 * @param[in] name The name of the variable to be read from stream. Used when
 *                 logging information before throwing an exception. 
 * @param[in] bound The (inclusive) lower of real values that may be read 
 *                  without throwing an exception. 
 * @result When found and not in error, the real number value read from the input
 *         stream **in**. Otherwise, returns zero.
 *
 * @details 
 * This function should be used when the next string in a stream is required 
 * to be an real number value. If a string cannot be extracted from the stream 
 * (end of file), if the string is extracted and isn't an real number value or is
 * less than the *bound* argument, this method records an error via the logger 
 * specifying the variable name (see the *name* argument) and error type and 
 * throws an exception.
 */
double
getRealWithLBound
( std::istream& is, const std::string& name, const double bound ){
  bool found;
  const double realNumber = getRealWithLBound( is, name, bound, found );
  if ( not found ){
    Log::error( "{} argument could not be read from input.", name );
    throw std::exception();
  } 
  return realNumber;
}
