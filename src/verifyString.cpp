#include <algorithm>
#include <iterator>

#include "utility.hpp"

/**
 * @brief
 * Verifies an input string has quotation delimiters and is no more than 
 * @p length characters long. 
 */
bool 
utility::verifyString( const std::string& card, 
		       const int length ){
  /* find the first non-whitespace character */
  auto wsfront = std::find_if_not( card.begin(),
				   card.end(),
				   [](int c){return std::isspace(c);});
  /* is that character a quote delimiter? */
  if ((*wsfront != '\'') && (*wsfront != '\"')) return false;
  const char delimiter = *wsfront;
  /* is the last non-whitspace character a corresponding quote delimiter? */
  auto wsback = std::find_if_not( card.rbegin(),
				  card.rend(),
				  [](int c){return std::isspace(c);}).base();
  if (*(wsback-1) != delimiter) return false;
  /* is the next instance of the quote delimiter at the end of the string? */
  {
    auto next = ++(std::find_if( wsfront + 1, //copied
                                 wsback,      //copied
                                 [delimiter](int c){return c == delimiter;}));
    if (next != wsback) return false;
  }
  /* is the string length less than or equal to the specified length? */
  if ( std::distance(wsfront, wsback) > (length + 2) ) return false;
  return true;
}
