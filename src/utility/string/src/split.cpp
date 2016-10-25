#include "utility.hpp"

/* Two version of split which (when considered) together mimic the python split 
 * method.
 *
 * The first is used to split string on one or more consecutive whitespace 
 * characters. This is the default behavior of the python split command. Because
 * whitespace characters are known in advance, no delimter argument is allowed. 
 * This function is written in an idiomatic C++ style.
 * 
 * The second is used to split strings on a user-specified delimiter string 
 * As with the python split, consecutive occurances of the delimiter string
 * render empty string entries in the return list. This function is written in 
 * (mostly) functional style employing tail-recursion.
 */ 

/**
 * @brief 
 * Used to split a substring on whitespace.
 *
 * @param[in] s A string to be split on whitespace
 * @result A vector of strings which existed as whitespace delimited substrings 
 *         in @p s
 *
 * @details
 * This function finds the boundaries of non-whitespace substrings using two
 * string iterators, 
 * 
 *  + `c`: the non-whitespace iterator
 *  + `ws`: the whitespace iterator
 *
 * The function begins by setting the whitespace iterator, `ws`, to the first character 
 * of the string parameter, @p s, and begins a loop. In each step of the loop,
 * the non-whitespace iterator, `c`, begins at the current position of of the 
 * non-whitespace iterator, `ws`, and iterates through the characters of @p s,
 * searching non-whitespace characters. If no more non-whitespace characters 
 * remain, the loop is exited. If a non-whitespace character is encountered,
 * `ws` begins iterating through the string starting from the current position of
 * `c` until a whitespace character is encountered. At this point, the iterators 
 * lie on the boundaries of a non-whitespace substring with `c` at the
 * left boundary and `ws` one character beyond the right boundary. The string 
 * iterator-range constructor is then called to copy the substring, which is in 
 * turn pushed onto the end of the output vector. If `ws` encountered the end of 
 * @p s in the last iteration, the loop is exited.\n
 * Once the loop is exited, the output vector is returned.
 */
std::vector< std::string > 
njoy::utility::string::split( const std::string& s ){
  std::vector< std::string > v{};
  auto ws = std::begin( s );
  auto isSpace = []( char i ){ return std::isspace( i ); };
  while ( true ) {
    auto c = std::find_if_not( ws, std::end( s ), isSpace );
    if ( c == std::end( s ) ){ break; }
    ws = std::find_if( c, std::end( s ), isSpace );
    v.push_back( std::string( c, ws ) );
    if ( ws == std::end( s ) ){ break; }
  }
  return v;
} 

namespace {

std::vector< std::string > 
trSplit( const std::string& s, 
         const std::string& delimiter, 
         const size_t pos, 
         std::vector< std::string >& v ){ 
  const size_t delimiter_pos = s.find( delimiter, pos );
  v.push_back( s.substr( pos, delimiter_pos - pos ) );
  return ( delimiter_pos == std::string::npos ) ? 
    v : trSplit( s, delimiter, delimiter_pos + delimiter.length(), v );
}

}

/**
 * @brief 
 * Used to split a string on a specified delimiter substring.
 *
 * @param[in] s A string to be split on a user-specified delimiter substring, @p delimiter
 * @param[in] delimiter A string on which to split the @p s
 * @result A vector of strings which existed as substrings delimited by 
 *         @p delimiter in @p s
 */
std::vector< std::string > 
njoy::utility::string::split
( const std::string & s, const std::string& delimiter ){ 
  std::vector< std::string > v{};
  return trSplit( s, delimiter, 0, v ); 
} 
