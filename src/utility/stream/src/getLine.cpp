#include "utility.hpp"

using namespace utility::stream;

/**
 * @details
 * Differs from the standard library function in that it throws if a line of 
 * text cannot be extracted.
 */
std::string 
getLine( std::istream& is ){
  std::string card;
  std::getline( is, card );
  if ( is.fail() ){
    Log::error( "Could not extract a new line" );
    Log::info( "End of input file encountered" );
    throw std::exception();
  }
  return card;
}
