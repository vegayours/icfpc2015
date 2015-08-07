# Finds folly.
#
# This module defines:
# FOLLY_INCLUDE_DIR
# FOLLY_LIBRARY
#

find_path(FOLLY_INCLUDE_DIR
    NAMES
      folly-config.h
    PATHS
      /usr/include/folly
      /usr/local/include/folly)
find_library(FOLLY_LIBRARY NAMES folly)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    FOLLY DEFAULT_MSG
    FOLLY_LIBRARY FOLLY_INCLUDE_DIR)

if (NOT FOLLY_FOUND)
    message(FATAL_ERROR "Folly not found")
else()
    message(STATUS "Found folly: ${FOLLY}")
endif()
