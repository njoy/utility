[![Build Status](https://travis-ci.org/njoy/utility.svg?branch=master)](https://travis-ci.org/njoy/utility)
[![Coverage Status](https://coveralls.io/repos/github/njoy/utility/badge.svg?branch=master)](https://coveralls.io/github/njoy/utility?branch=master)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/8474/badge.svg)](https://scan.coverity.com/projects/njoy-utility)

[![Stories in In Progress](https://badge.waffle.io/njoy/utility.svg?label=In%20Progress&title=In%20Progress)](http://waffle.io/njoy/utility)
[![Stories in Ready](https://badge.waffle.io/njoy/utility.svg?label=ready&title=Ready)](http://waffle.io/njoy/utility)

Nuclear Data C++ Utilities
==========================

The utility library provides

+ The `View`, a class providing a std::vector-like interface to reference spans of data owned by other objects 
+ Routines for extracting and verifying values drawn from input streams 
    - integer values (with and without legal bound specifications)
    - real number values (with and without legal bound specifications)
    - quote delimited strings
    - energy values (in electron-volts)
    - temperature values (in kelvin)
+ Routines for verifying strings can be safely parsed to numeric variables
+ Routines for parsing real number formats available in Fortran that are otherwise not recognized by C++ standard library routines.
+ Collections of real number strings for unit testing and verifying parsing routines

## License
This software is distributed according to the terms specified in the [LICENSE](LICENSE) file.

