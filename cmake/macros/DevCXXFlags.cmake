# TODO set flags on macos, linux and windows
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING  "Set Current Build Type Release." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_COMPILER_IS_GNUCXX)
    include(GCCFlags)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    include(ClangFlags)
elseif(MSVC)
    include(MSVCFlags)
endif()

message(STATUS "[DevCXXFlags] Using C++ compiler: " ${CMAKE_CXX_COMPILER})
message(STATUS "[DevCXXFlags] Using C compiler: " ${CMAKE_C_COMPILER})
message(STATUS "[DevCXXFlags] Build type: ${CMAKE_BUILD_TYPE}")