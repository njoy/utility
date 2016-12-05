namespace stream {

struct InputTag{};
struct OutputTag{};

#include "utility/stream/basic_RecordOrientedStream.hpp"
using iRecordOrientedStream =
  basic_RecordOrientedStream< std::basic_istream, char >;

using wiRecordOrientedStream =
  basic_RecordOrientedStream< std::basic_istream, wchar_t >;

#include "utility/stream/basic_FILE_streambuf.hpp"
using FILE_streambuf = basic_FILE_streambuf<char>;
using wFILE_streambuf = basic_FILE_streambuf<wchar_t>;

#include "utility/stream/basic_TemporaryFileStream.hpp"
using TemporaryFileStream = basic_TemporaryFileStream<char>;
using wTemporaryFileStream = basic_TemporaryFileStream<wchar_t>;

#include "utility/stream/basic_TeeStream.hpp"
using iTeeStream = basic_TeeStream< std::basic_istream, char >;
using wiTeeStream = basic_TeeStream< std::basic_istream, wchar_t >;

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * trimmed string is either '1' or '0'. Permits EOF without throwing an 
 * exception. */
bool 
getBool( std::istream& is, const std::string& name, bool& found );

/**
* @brief 
* Extracts the next white space delimited string from a stream and verifies the 
* trimmed string is either '1' or '0'. */
bool 
getBool( std::istream& is, const std::string& name );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string represent a valid energy value (in eV). Permits EOF without throwing an
 * exception. */
double 
getEnergy( std:: istream& is, bool& found, const std::string& name );

/** 
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string represent a valid energy value (in eV) */
double 
getEnergy( std:: istream& is, const std::string& name );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the 
 * string describes an integer. Permits EOF without throwing an exception. */
int
getInteger( std::istream& is, const std::string& name, bool& found );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string corresponds to an integer. */
int 
getInteger( std::istream& is, const std::string& name );

/**
 * @brief
 * Extracts the next white space delimited string from a stream and verifies
 * the string corresponds to an integer between lBound (inclusive) and rBound 
 * (exclusive) argument values. Permits EOF without throwing an exception. */
int 
getIntInRange( std::istream& is, const std::string& name,
	       const int lBound, const int rBound, bool& found );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies
 * the string corresponds to an integer between lBound (inclusive) and rBound 
 * (exclusive) argument values. */
int 
getIntInRange( std::istream& is, const std::string& name, 
	       const int lBound, const int rBound );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the 
 * string corresponds to an integer greater than the *bound* argument. Permits 
 * EOF without throwing an exception. */
int 
getIntWithLBound
( std::istream& is, const std::string& name, const int bound, bool& found );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string corresponds to an integer greater than the *bound* argument. */
int 
getIntWithLBound( std::istream& is, const std::string& name, const int bound );

/** @brief Extracts the next newline character delimited string from a stream. */
std::string 
getLine( std::istream& is );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string corresponds to a real number format recognized in the Fortran language. 
 * Permits EOF without throwing an exception. */
double 
getRealNumber( std::istream& is, const std::string& name, bool& found );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string correspond to a real number format recognized in the Fortran language. 
 */
double 
getRealNumber( std::istream& is, const std::string& name );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies
 * the string corresponds to a real number greater than or equal to the *bound* 
 * argument. Permits EOF without throwing an exception. */
double
getRealWithLBound
( std::istream& is, const std::string& name, const double bound, bool& found );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies
 * the string corresponds to an real number greater than or equal to the *bound* 
 * argument. */
double
getRealWithLBound
( std::istream& is, const std::string& name, const double bound );

/**
 * @brief 
 * Extracts the next quote delimited string from a stream and verifies the 
 * length is less than or equal to the *length* argument. Allow EOF without
 * throwing. */
std::string 
getStringArg( std::istream& is, const std::string& name, const int length );

/**
 * @brief 
 * Extracts the next quote delimited string from a stream and verifies the length
 * is less than or equal to the *length* argument. */
std::string 
getStringArg( std::istream& is, const std::string& name,
	      const int length, bool& found );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string represent a valid temperature value (in Kelvin). Permits EOF without 
 * throwing an exception. */
double 
getTemperature( std::istream& is, bool& found,
		const std::string& name = std::string("tempd") );

/**
 * @brief 
 * Extracts the next white space delimited string from a stream and verifies the
 * string represent a valid temperature value (in Kelvin) */
double 
getTemperature( std::istream& is,
		const std::string& name = std::string("tempd") );

/** @brief  Read a specified number of characters from the stream */
std::string 
readString( std::istream& is, const std::string::size_type count );

/**
 * @brief 
 * Reads a specified number of characters from the stream or until the
 * delimeter is found. */
std::string 
readString
( std::istream& is, const std::string::size_type count, const char delim );

}
