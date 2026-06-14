# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/appPrejectOp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appPrejectOp_autogen.dir/ParseCache.txt"
  "appPrejectOp_autogen"
  )
endif()
