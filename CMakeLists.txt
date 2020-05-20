########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.16 )
project( utility LANGUAGES CXX )

########################################################################
# Dependencies
########################################################################

include( cmake/utility_dependencies.cmake )

########################################################################
# Project targets
########################################################################

add_library( utility INTERFACE )
target_include_directories( utility INTERFACE src/ )
target_link_libraries( utility
    INTERFACE catch-adapter
    INTERFACE header-utilities
    )
