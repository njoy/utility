#include <exception>

#include "utility/stream.hpp"

/**
 * @details
 * Differs from the standard library function in that it throws if a line of text
 * cannot be extracted.
 */
std::string 
utility::stream::getLine( std::istream& is ){
  std::string card;
  std::getline(is, card);
  if (is.fail()){
    LOG(ERROR) << "Could not extract a new line";
    LOG(INFO)  << "End of input file encountered";
    throw std::exception();
  }
  return card;
}
