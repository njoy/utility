#include <exception>
#include <set>

#include "utility/stream.hpp"

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
utility::stream::getStringArg( std::istream& is, 
			       const std::string& name, 
			       const int length,
			       bool& found ){
  if (length < 0){
    LOG(ERROR) << "Length argument must be greater than or equal to zero";
    LOG(INFO) << "Error in getStringArg";
    throw std::exception();
  }
  std::set<char> quoteCharacters = { '\'', '\"' };
  char nextChar;
  is >> nextChar;
  found = !(is.fail());
  std::string output = ""; // declared to massage compiler into using rvo
  if ( !found ) return output;
  if ( quoteCharacters.find(nextChar) == quoteCharacters.end() ){
    LOG(ERROR) << "Opening quote delimiter not found";
    LOG(INFO) << name << " must be a string with length < " << length << 
      " delimited by quotes";
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
  buffer.sputc(nextChar);
  is.get(buffer, delimiter);
  nextChar = is.get();
  if ( ( is.fail() ) || ( nextChar != delimiter ) ){
    LOG(ERROR) << "No matching quote delimiter found";
    LOG(INFO) << name << " must be a string with length < " << length << 
      " delimited by quotes";
    throw std::exception();
  }
  output = delimiter + buffer.str() + nextChar;
  if ( int(output.length()) > (length + 2) ){
    LOG(ERROR) << "String argument exceeds maximum length";
    LOG(INFO) << name << " must be a string with length < " << length << 
      " delimited by quotes";
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
utility::stream::getStringArg( std::istream& is, 
			       const std::string& name, 
			       const int length ){
  bool found;
  const std::string stringArg = 
    utility::stream::getStringArg(is, name, length, found);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return stringArg;
}
