#include "utility.hpp"

/** 
 * @details 
 * This function should be used when a string argument (delimited by quotations) 
 * should be pulled from the stream, but may not exist. If a the string cannot be
 * extracted from the stream (end of file), the **found** flag is set to false 
 * "" is returned. If a matching quotation delimiter cannot be found or the 
 * length exceeds the specified maximum, this method records an error via the 
 * logger specifying the variable name (see the name argument) and error type and 
 * throws an exception.
 */
std::string 
njoy::utility::stream::getStringArg
( std::istream& is, const std::string& name, const int length, bool& found ){
  if ( length < 0 ){
    njoy::Log::error( "Length argument must be greater than or equal to zero" );
    njoy::Log::info( "Error in getStringArg" );
    throw std::exception();
  }
  std::set<char> quoteCharacters = { '\'', '\"' };
  char nextChar;
  is >> nextChar;
  found = not is.fail();
  std::string output = ""; // declared to massage compiler into using rvo
  if ( not found ){ return output; }
  if ( quoteCharacters.find( nextChar ) == quoteCharacters.end() ){
    njoy::Log::error( "Opening quote delimiter not found" );
    njoy::Log::info( "{} must be a string with length < {} delimited by quotes",
	       name, length ); 
    throw std::exception();
  }
  const char delimiter = nextChar;
  // empty string check  
  nextChar = is.get(); 
  if (nextChar == delimiter) {
    output += delimiter;
    output += nextChar;
    return output;
  } 
  std::stringbuf buffer;
  buffer.sputc( nextChar );
  is.get( buffer, delimiter );
  nextChar = is.get();
  if ( ( is.fail() ) || ( nextChar != delimiter ) ){
    njoy::Log::error( "No matching quote delimiter found" );
    njoy::Log::info( "{} must be a string with length < {} delimited by quotes",
	       name, length );
    throw std::exception();
  }
  output = delimiter + buffer.str() + nextChar;
  if ( int( output.length() ) > (length + 2) ){
    njoy::Log::error( "String argument exceeds maximum length" );
    njoy::Log::info( "{} must be a string with length < {} delimited by quotes",
	       name, length ); 
    throw std::exception();
  }
  return output;
}

/** 
 * @details 
 * This function should be used when a string argument (delimited by quotations) 
 * should be pulled from the stream. If a the string cannot be extracted from the
 * stream (end of file), a matching quotation delimiter cannot be found, or the 
 * length exceeds the specified maximum, this method records an error via the 
 * logger specifying the variable name (see the name argument) and error type and 
 * throws an exception.
 */
std::string 
njoy::utility::stream::getStringArg
( std::istream& is, const std::string& name, const int length ){
  bool found;
  const std::string stringArg = getStringArg( is, name, length, found );
  if ( not found ){
    njoy::Log::error( "{} argument could not be read from input.", name );
    throw std::exception();
  } 
  return stringArg;
}
