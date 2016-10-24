#include "utility.hpp"

using namespace utility::stream;

/**
 * @param is A stream to read characters from.
 * @param[in] count The number of characters to read from the stream
 * @result A string composed of the @p count characters read from @p is
 *
 * @details
 * This function throws an exception if the stream fails to render the prescribed
 * number of character (see the @p count paramter).
 */
std::string 
readString( std::istream& is, const std::string::size_type count ){
  std::string s;
  s.resize( count );
  is.read( &s[0], count );
  if ( is.fail() ){ throw std::exception(); }
  return s;
}

/**
 * @param is A stream to read characters from.
 * @param count[in] The maximum number of characters to read from the stream
 * @par delim[in] A delimiter character which signals no additional characters should be read
 * @result A string composed of characters read from @p is
 *
 * @details
 * If the stream begins with the delimiter, it continues to read until it finds
 * something that isn't the delimiter. The count of the number of characters
 * doesn't begin until a non-delimiter is found.
 */
std::string 
readString
( std::istream& is, const std::string::size_type count, const char delim ){
  std::string s;
  s.reserve( count );
  while( is.peek() == delim ) { is.get(); }
  if ( is.fail() ){ throw std::exception(); }
  for( std::string::size_type i = 0; i < count; ++i ){
    s.push_back(is.get());
    if( s.back() == delim ) {
      s.pop_back();
      break;
    }
  }
  if ( is.fail() ){ throw std::exception(); }
  return s;
}
