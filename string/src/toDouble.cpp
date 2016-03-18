#include <cmath>
#include <exception>

#include "utility/string.hpp"

/**
 * @brief
 * Returns a double precision number corresponding to a real number string.
 *
 * @param[in] s 
 * A string in a Fortran-recognized real number format to parse to a double.
 *
 * @result The double parsed from @p s.
 *
 * @details
 * Fortran accepts a wider variety of real number formats than the std::stod 
 * function in the string header of the standard library. This function 
 * addresses this shortfall.
 */
double 
utility::string::toDouble( const std::string& s ){
  double d;
  size_t l;
  d = std::stod(s, &l);
  if (l == s.length()){ return d; }
  const char* cp = isalpha(s[l]) ? &s[l+1] : &s[l];
  char** cpp = nullptr;
  int i = std::strtol(cp, cpp, 10);
  d = d*pow(10, i);
  return d;
}
