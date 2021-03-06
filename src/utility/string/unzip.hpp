template< typename... T >
struct unzip {
  /** @brief Extract tuples of whitespace-delimited values from a string.
   *
   * @details
   * If the string doesn't have enough values, an exception is thrown. If there
   * are more than enough numbers, the rest of the string is ignored.
   *
   * @return A std::tuple where each element of the tuple is a vector. The type of
   * vector is dependent on the template parameters.
   *
   * @param s String from which the numbers are parsed (read)
   * @param nTuples How many entries to read *for each vector*. The actual number
   *        of values read is nTuples * (Number of vectors).
   */
  static std::tuple< std::vector<T>... >
  parse( const std::string& s, const int nTuples ){
    return unzip_<sizeof...(T)>::parse(s, nTuples);
  }
  
private:
  /* What's the purpose the of the dummy template parameter? */ 
  /* Explicit class template specialization within the context of another class
   * template is forbidden. Partial specialization, however, is not. By using
   * a dummy parameter, this nested class template can be specialized to provide 
   * recusion termination
   */
  template<int N, bool dummy = true >
  struct unzip_ {
    
    static std::tuple< std::vector<T>... >
    parse( const std::string& s, const int nTuples ){
      std::tuple< std::vector<T>... > vectorTuple;
      unzip_< N >::reserve(vectorTuple, nTuples);
      std::istringstream ss(s);
      int entriesRemaining = nTuples;
      while(entriesRemaining--){ unzip_< N >::read(ss, vectorTuple); }
      if( ss.fail() ){
	Log::error( "Trouble unzipping numbers from a string." );
	Log::info( "Number of values requested was: {}",  nTuples );
	Log::info( "Number of vectors requested was: {}", sizeof...(T) );
        throw std::exception();
      }
      return vectorTuple;
    }

    /** @brief Reserve enough space for the requested number of numbers. */
    static void 
    reserve( std::tuple< std::vector<T>... >& vectorTuple, const int nEntries ){
      std::get<N-1>(vectorTuple).reserve(nEntries);
      unzip_<N-1>::reserve(vectorTuple, nEntries);
    }

    /** @brief Read in a single value */
    static void 
    read( std::istringstream& ss, std::tuple< std::vector<T>... >& vectorTuple ){
      typename std::tuple_element< sizeof...(T) - N, std::tuple<T...> >::type x;
      ss >> x;
      std::get< sizeof...(T) - N >(vectorTuple).push_back(x);
      unzip_< N-1 >::read(ss, vectorTuple);
    }
  };

  /** @brief Specialization needed to terminate recursion */
  template<bool dummy>
  struct unzip_< 1, dummy > {
    
    static std::tuple< std::vector<T>... >
    parse( const std::string& s, const int nTuples ){
      std::tuple< std::vector<T>... > vectorTuple;
      unzip_< 1 >::reserve(vectorTuple, nTuples);

      std::istringstream ss(s);
      int entriesRemaining = nTuples;
      while (entriesRemaining--){ unzip_< 1 >::read(ss, vectorTuple); }
      return vectorTuple;
    }
  
    static void 
    reserve( std::tuple< std::vector<T>... >& vectorTuple, const int nTuples ){
  	  std::get<0>(vectorTuple).reserve(nTuples);
    }

    static void 
    read( std::istringstream& ss, std::tuple< std::vector<T>... >& vectorTuple ){
      typename std::tuple_element< sizeof...(T) - 1, std::tuple<T...> >::type x;
      ss >> x;
      std::get<sizeof...(T) - 1>(vectorTuple).push_back(x);
    }
  };
};
