#include "utility.hpp"

/**
 * @details
 * Differs from the standard library function in that it throws if a line of 
 * text cannot be extracted.
 */
std::string 
njoy::utility::stream::getLine( std::istream& is ){
  std::string card;
  std::getline( is, card );
  if ( is.fail() ){
    njoy::Log::error( "Could not extract a new line" );
    njoy::Log::info( "End of input file encountered" );
    throw std::exception();
  }
  return card;
}
