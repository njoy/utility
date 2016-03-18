#include <exception>

#include "utility.hpp"

/**
 * @brief
 * Extracts a substring preceding the first Fortran EOL character.
 *
 * @param[in] card A string which should be truncated at the first instance of 
 *                 the Fortran EOL character. 
 * @result A copy of a substring of @p card preceeding the first instance the
 *         Fortran EOL character.
 *
 * @details
 * This function ignores EOL characters within string arguments (delimited by
 * quotation characters). 
 */

std::string 
utility::extractCommand( const std::string& card ){
  char quoteChar;
  size_t searchPosition = 0;
  size_t quotePosition;
  size_t nextQuotePosition; 
  size_t slashPosition;
  while (true) {
    slashPosition = card.find('/', searchPosition);
    if (slashPosition != std::string::npos){
      quotePosition = card.find_first_of("\'\"", searchPosition);
      if (quotePosition < slashPosition){
	quoteChar = card[quotePosition];
	nextQuotePosition = card.find(quoteChar, quotePosition + 1);
	if (nextQuotePosition == std::string::npos){
	  LOG(ERROR) << "Unmatched quotation character";
	  throw std::exception();
	}
	searchPosition = nextQuotePosition + 1;
      } else{
	break;
      }
    } else{
      break;
    }
  }
  return card.substr(0, slashPosition);
}
