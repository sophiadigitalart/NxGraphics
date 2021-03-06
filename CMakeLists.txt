if (APPLE)
  cmake_minimum_required(VERSION 2.8.8)
  SET(CMAKE_SIZEOF_VOID_P 4)
else()
  cmake_minimum_required(VERSION 2.6)
endif ()

project(NxGraphicsEngine)

if (APPLE AND OGRE_BUILD_PLATFORM_APPLE_IOS)
  # Set build variables
  set(CMAKE_OSX_SYSROOT iphoneos)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "")
  set(XCODE_ATTRIBUTE_SDKROOT iphoneos)
  set(CMAKE_OSX_ARCHITECTURES ${ARCHS_STANDARD_32_BIT})
elseif (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
  # Set 10.5 as the base SDK by default
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.5)

  if (NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES ${ARCHS_STANDARD_32_64_BIT})
  endif()
endif ()

# provide configuration options to choose which of the dependencies to build
option(NXGRAPHICSSOURCE_BUILD_NXVIDEO "Build NxVideo dependency" TRUE)
option(NXGRAPHICSSOURCE_BUILD_NXSOUND "Build NxSound dependency" TRUE)
option(NXGRAPHICSSOURCE_BUILD_NXMOCAP "Build NxMocap dependency" TRUE)
option(NXGRAPHICSSOURCE_BUILD_NXNETWORK "Build NxNetwork dependency" TRUE)
option(NXGRAPHICSSOURCE_BUILD_NXDEVICE "Build NxDevice dependency" TRUE)
option(NXGRAPHICSSOURCE_BUILD_NXGRAPHICS "Build NxGraphics dependency" TRUE)
option(NXGRAPHICSSOURCE_INSTALL_DEV "Install development headers and libraries" TRUE)
set(NXGRAPHICSSOURCESOURCE_LIB_DIRECTORY "lib${LIB_SUFFIX}" CACHE STRING "Install path for libraries, e.g. 'lib64' on some 64-bit Linux distros.")
mark_as_advanced(NXGRAPHICSSOURCE_LIB_DIRECTORY)

# choose paths to build and install dependencies to
if (NOT NXGRAPHICSSOURCE_RUNTIME_OUTPUT)
  set(NXGRAPHICSSOURCE_RUNTIME_OUTPUT ${NXGRAPHICSSOURCE_BINARY_DIR}/bin)
endif ()
if (WIN32)
  set(NXGRAPHICSSOURCE_RELEASE_PATH "/Release")
  set(NXGRAPHICSSOURCE_DEBUG_PATH "/Debug")
else ()
  set(NXGRAPHICSSOURCE_RELEASE_PATH "")
  set(NXGRAPHICSSOURCE_DEBUG_PATH "")
endif ()

# postfix debug libraries with a _d
if (NOT APPLE)
set(CMAKE_DEBUG_POSTFIX "_d")
endif()

# determine if we are compiling for a 32bit or 64bit system
include(CheckTypeSize)
CHECK_TYPE_SIZE("void*" NXGRAPHICSSOURCE_PTR_SIZE BUILTIN_TYPES_ONLY)
if (NXGRAPHICSSOURCE_PTR_SIZE EQUAL 8)
  set(NXGRAPHICSSOURCE_PLATFORM_X64 TRUE)
else ()
  set(NXGRAPHICSSOURCE_PLATFORM_X64 FALSE)
endif ()

# Add -fPIC flag to x64 GCC builds
if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
  if (NXGRAPHICSSOURCE_PLATFORM_X64 AND NOT APPLE)
    add_definitions(-fPIC)
  endif ()
endif ()


# by default, install to NxGraphicsSourceSdk subfolder in build directory
#if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#  if (NXGRAPHICSSOURCE_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
      set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/NxGraphicsSdk" CACHE PATH "Sdk install prefix" FORCE)
#  endif ()
#endif ()

# enforce that CMAKE_BUILD_TYPE is set, otherwise install commands
# will not work for Makefile based generators.
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug, Release" FORCE)
endif ()


macro(copy_files INCLUDE INCLUDE_DIR)
install(FILES ${ARGN} DESTINATION ${INCLUDE_DIR})
endmacro()

macro(copy_directory INCLUDE INCLUDE_DIR)
install(DIRECTORY ${ARGN} DESTINATION ${INCLUDE_DIR})
endmacro()



# configure and install dependency LIBRARY
# INCLUDE_DIR specifies where header files need to be installed
# Any additional parameters are treated as a list of header files
# to install.
macro(install_dep LIBRARY INCLUDE_DIR)
  set_target_properties(${LIBRARY} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${NXGRAPHICSSOURCE_RUNTIME_OUTPUT}
  )

  # always install runtime libraries (i.e. DLL, so)
  install(TARGETS ${LIBRARY}
    RUNTIME DESTINATION "bin${NXGRAPHICSSOURCE_RELEASE_PATH}" CONFIGURATIONS Release
    LIBRARY DESTINATION "${NXGRAPHICSSOURCE_LIB_DIRECTORY}${NXGRAPHICSSOURCE_RELEASE_PATH}" CONFIGURATIONS Release
    ARCHIVE DESTINATION "${NXGRAPHICSSOURCE_BINARY_DIR}/notwanted" CONFIGURATIONS Release
  )
  install(TARGETS ${LIBRARY}
    RUNTIME DESTINATION "bin${NXGRAPHICSSOURCE_DEBUG_PATH}" CONFIGURATIONS Debug
    LIBRARY DESTINATION "${NXGRAPHICSSOURCE_LIB_DIRECTORY}${NXGRAPHICSSOURCE_DEBUG_PATH}" CONFIGURATIONS Debug
    ARCHIVE DESTINATION "${NXGRAPHICSSOURCE_BINARY_DIR}/notwanted" CONFIGURATIONS Debug
  )

  if (NXGRAPHICSSOURCE_INSTALL_DEV)
    # also install development parts
    install(TARGETS ${LIBRARY}
      RUNTIME DESTINATION "bin${NXGRAPHICSSOURCE_RELEASE_PATH}" CONFIGURATIONS Release
      LIBRARY DESTINATION "${NXGRAPHICSSOURCE_LIB_DIRECTORY}${NXGRAPHICSSOURCE_RELEASE_PATH}" CONFIGURATIONS Release
      ARCHIVE DESTINATION "${NXGRAPHICSSOURCE_LIB_DIRECTORY}${NXGRAPHICSSOURCE_RELEASE_PATH}" CONFIGURATIONS Release
    )
    install(TARGETS ${LIBRARY}
      RUNTIME DESTINATION "bin${NXGRAPHICSSOURCE_DEBUG_PATH}" CONFIGURATIONS Debug
      LIBRARY DESTINATION "${NXGRAPHICSSOURCE_LIB_DIRECTORY}${NXGRAPHICSSOURCE_DEBUG_PATH}" CONFIGURATIONS Debug
      ARCHIVE DESTINATION "${NXGRAPHICSSOURCE_LIB_DIRECTORY}${NXGRAPHICSSOURCE_DEBUG_PATH}" CONFIGURATIONS Debug
    )
    install(FILES ${ARGN} DESTINATION ${INCLUDE_DIR})
  endif ()
endmacro()

# setup the individual dependencies
if (NXGRAPHICSSOURCE_BUILD_NXVIDEO)
	add_subdirectory(NxVideo)
endif ()
if (NXGRAPHICSSOURCE_BUILD_NXSOUND)
	add_subdirectory(NxSound)
endif ()
if (NXGRAPHICSSOURCE_BUILD_NXMOCAP)
  add_subdirectory(NxMocap)
endif ()
if (NXGRAPHICSSOURCE_BUILD_NXNETWORK)
  add_subdirectory(NxNetwork)
endif ()
if (NXGRAPHICSSOURCE_BUILD_NXDEVICE)
	add_subdirectory(NxDevice)
endif ()

if (NXGRAPHICSSOURCE_BUILD_NXGRAPHICS)
	add_subdirectory(NxGraphics)
	ADD_DEPENDENCIES (NxGraphics NxDevice)
	ADD_DEPENDENCIES (NxGraphics NxNetwork)
	ADD_DEPENDENCIES (NxGraphics NxMocap)
	ADD_DEPENDENCIES (NxGraphics NxSound)
	ADD_DEPENDENCIES (NxGraphics NxVideo)
endif ()
 

# header files

file(GLOB NXDEVICE_HEADERS "${CMAKE_SOURCE_DIR}/NxDevice/*.h")
INSTALL(FILES ${NXDEVICE_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxDevice)

file(GLOB NXGRAPHICS_HEADERS "${CMAKE_SOURCE_DIR}/NxGraphics/*.h")
INSTALL(FILES ${NXGRAPHICS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxGraphics)
 
file(GLOB NXGUI_HEADERS "${CMAKE_SOURCE_DIR}/NxGraphics/NxGui/*.h")
INSTALL(FILES ${NXGUI_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxGraphics/NxGui)

file(GLOB NXGUI_PHYSICS "${CMAKE_SOURCE_DIR}/NxGraphics/Physics/empty/*.h")
INSTALL(FILES ${NXGUI_PHYSICS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxGraphics/physics/empty)

file(GLOB NXMOCAP_HEADERS "${CMAKE_SOURCE_DIR}/NxMocap/*.h")
INSTALL(FILES ${NXMOCAP_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxMocap)

file(GLOB NXSOUND_HEADERS "${CMAKE_SOURCE_DIR}/NxSound/*.h")
INSTALL(FILES ${NXSOUND_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxSound)

file(GLOB NXNETWORK_HEADERS "${CMAKE_SOURCE_DIR}/NxNetwork/*.h")
INSTALL(FILES ${NXNETWORK_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxNetwork)

file(GLOB NXVIDEO_HEADERS "${CMAKE_SOURCE_DIR}/NxVideo/*.h")
INSTALL(FILES ${NXVIDEO_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/NxVideo)



if (APPLE)
	message( "Detected Apple OS" ) 

elseif(WIN32)
	message( "Detected Windows OS" )
	file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/Bin/${CMAKE_BUILD_TYPE}/plugins")
 
	

 

elseif(ANDROID)
	message( "Detected ANDROID OS" )
 			
else()
	message( "Detected linux OS" )
	
endif()
 
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/NxDeps/ DESTINATION ${CMAKE_INSTALL_PREFIX}/NxDeps )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Lib/ DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)
  
add_subdirectory(NxSamples)

add_subdirectory(NxGraphicsSdk)

 

