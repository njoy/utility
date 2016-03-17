#include <cmath> // Provides 'pow' function (retro, right?)
#include <exception>

#include "utility/string.hpp"

/**
 * @author Austin McCartney
 * @date 5 Septemeber, 2015
 *
 * @brief
 * Returns a double precision number corresponding to a real number string.
 *
 * @param[in] s A string in a Fortran-recognized real number format to parse to a
 *              double.
 * @result The double parsed from @p s.
 *
 * @details
 * Fortran accepts a wider variety of real number formats than the std::stod 
 * function in the string header of the standard library. This function 
 * addresses this shortfall.
 */
double 
utility::string::toDouble(const std::string& s){
  double d;
  size_t l;
  d = std::stod(s, &l);
  if (l == s.length()){ return d; }
  const char* cp = isalpha(s[l]) ? &s[l+1] : &s[l];
  char** cpp = nullptr;
  int i = std::strtol(cp, cpp, 10);
  d = d*pow(10, i);
  return d;
  /*
  std::smatch match;
  std::regex_search( s, 
		     match, 
		     utility::string::decimalFormPattern_);
  if (match.size() == 0) throw std:: exception();
  const double significand = std::stod(match[0]);
  auto remain = s.substr(match[0].length());
  std::regex_search( remain,  
		     match, 
		     utility::string::integerPattern_);
  const int exponent = match.size() > 0 ? std::stoi(match[0]) : 0;
  return significand * pow(10, exponent);
  */
}
