# once done this will define
# UNITTEST++_FOUND
# UNITTEST++_INCLUDE_DIRS
# UNITTEST++_LIBRARIES

find_path(UNITTEST++_INCLUDE_DIR NAMES UnitTest++.h
          HINTS "lib/UnitTest++/src")
find_library(UNITTEST++_LIBRARY NAMES UnitTest++ libUnitTest++
             HINTS "lib/UnitTest++/build")
set(UNITTEST++_INCLUDE_DIRS ${UNITTEST++_INCLUDE_DIR})
set(UNITTEST++_LIBRARIES ${UNITTEST++_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UnitTest++ DEFAULT_MSG
                                  UNITTEST++_LIBRARY UNITTEST++_INCLUDE_DIR)
mark_as_advanced(UNITTEST++_INCLUDE_DIR UNITTEST++_LIBRARY)