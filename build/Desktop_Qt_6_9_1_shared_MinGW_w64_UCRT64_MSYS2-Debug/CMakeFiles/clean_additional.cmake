# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Spice_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Spice_autogen.dir\\ParseCache.txt"
  "Spice_autogen"
  )
endif()
