###############################################################################
#  Copyright (c) 2014-2026 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################
cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

if ( NOT CMAKE_SCRIPT_MODE_FILE )
    find_package(Git QUIET)
endif()

set( GIT_COMMIT_HASH "unknown" )
set( GIT_COMMIT_HEIGHT 0 )
set( GIT_DIRTY 0 )

if ( GIT_EXECUTABLE )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET )

    if ( NOT GIT_COMMIT_HASH )
        set( GIT_COMMIT_HASH "unknown" )
    endif()

    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-list --count HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HEIGHT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET )

    if ( NOT GIT_COMMIT_HEIGHT )
        set( GIT_COMMIT_HEIGHT 0 )
    endif()

    execute_process(
        COMMAND ${GIT_EXECUTABLE} status --porcelain
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_STATUS
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET )

    if ( GIT_STATUS )
        set( GIT_DIRTY 1 )
    endif()
endif()

set( LIBBITCOIN_VERSION_MAJOR 4 )
set( LIBBITCOIN_VERSION_MINOR 0 )
set( LIBBITCOIN_VERSION_PATCH ${GIT_COMMIT_HEIGHT} )

if ( CMAKE_SCRIPT_MODE_FILE )
    configure_file( ${CONFIGURE_INPUT} ${CONFIGURE_OUTPUT} @ONLY )
    return()
endif()

project( libbitcoin-explorer
  VERSION ${LIBBITCOIN_VERSION_MAJOR}.${LIBBITCOIN_VERSION_MINOR}.${LIBBITCOIN_VERSION_PATCH}
  DESCRIPTION "Bitcoin Command Line Tool"
  LANGUAGES C CXX )

set( CMAKE_CXX_SCAN_FOR_MODULES OFF )

set( repository_root_dir "${CMAKE_CURRENT_SOURCE_DIR}/../.." )

if ( MSVC )
  set( CMAKE_STATIC_LIBRARY_PREFIX "lib" )
  set( CMAKE_SHARED_LIBRARY_PREFIX "lib" )
  set( CMAKE_IMPORT_LIBRARY_PREFIX "lib" )

  if ( BUILD_SHARED_LIBS )
    set( CMAKE_MSVC_RUNTIME_LIBRARY
      "$<IF:$<CONFIG:Debug>,MultiThreadedDebugDLL,MultiThreadedDLL>" )
  else()
    set( CMAKE_MSVC_RUNTIME_LIBRARY
      "$<IF:$<CONFIG:Debug>,MultiThreadedDebug,MultiThreaded>" )
  endif()

  set( CMAKE_C_FLAGS_DEBUG "/Od /Ob1 /Oi /Gy /RTC1 /Zi" )
  set( CMAKE_CXX_FLAGS_DEBUG "/Od /Ob1 /Oi /Gy /RTC1 /Zi" )
  set( CMAKE_C_FLAGS_RELEASE "/O2 /Ob2 /Oi /Ot /Oy /GT /Qpar /Gy /GF /GS- /guard:cf- /Zi" )
  set( CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /Oi /Ot /Oy /GT /Qpar /Gy /GF /GS- /guard:cf- /Zi" )

  add_compile_options(
    /W4
    /permissive-
    /bigobj
    /Zc:__cplusplus
    /Zc:preprocessor
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-command-line-argument>
  )

  add_compile_definitions(
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _WIN32_WINNT=0x0A00
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Debug>:_CRTDBG_MAP_ALLOC>
    $<$<CONFIG:Release>:NDEBUG>
  )

  add_link_options(
    /ignore:4099
    $<$<CONFIG:Debug>:/DEBUG>
    $<$<CONFIG:Release>:/DEBUG>
    $<$<CONFIG:Release>:/OPT:REF>
    $<$<CONFIG:Release>:/OPT:ICF>
  )
endif()

# Link POSIX threads on BSD.
if ( CMAKE_SYSTEM_NAME MATCHES "BSD" )
  set( THREADS_PREFER_PTHREAD_FLAG ON )
  find_package( Threads REQUIRED )
  link_libraries( Threads::Threads )
endif()

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)

#------------------------------------------------------------------------------
# Project options.
#------------------------------------------------------------------------------
option( with-tests "Compile with unit tests." ON )
option( with-console "Compile with console application." ON )

#------------------------------------------------------------------------------
# Dependencies.
#------------------------------------------------------------------------------
if ( BUILD_SHARED_LIBS )
  set( libbitcoin-network_USE_STATIC_LIBS "OFF" )
else()
  set( libbitcoin-network_USE_STATIC_LIBS "ON" )
endif()

find_package( libbitcoin-network 4.0.0 REQUIRED )
set( libbitcoin_network_VERSION ${libbitcoin-network_VERSION} )

#------------------------------------------------------------------------------
# Architecture options.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Compiler options.
#------------------------------------------------------------------------------
if ( NOT MSVC )

  check_cxx_compiler_flag( "-Wall" HAS_FLAG_WALL )
  if ( !HAS_FLAG_WALL )
      message( FATAL_ERROR "Compiler does not support '-Wall'." )
  endif()

  check_cxx_compiler_flag( "-Wextra" HAS_FLAG_WEXTRA )
  if ( !HAS_FLAG_WEXTRA )
      message( FATAL_ERROR "Compiler does not support '-Wextra'." )
  endif()

  check_cxx_compiler_flag( "-Wno-reorder" HAS_FLAG_WNO-REORDER )
  if ( !HAS_FLAG_WNO-REORDER )
      message( FATAL_ERROR "Compiler does not support '-Wno-reorder'." )
  endif()

  check_cxx_compiler_flag( "-Wno-missing-field-initializers" HAS_FLAG_WNO-MISSING-FIELD-INITIALIZERS )
  if ( !HAS_FLAG_WNO-MISSING-FIELD-INITIALIZERS )
      message( FATAL_ERROR "Compiler does not support '-Wno-missing-field-initializers'." )
  endif()

  check_cxx_compiler_flag( "-Wno-missing-braces" HAS_FLAG_WNO-MISSING-BRACES )
  if ( !HAS_FLAG_WNO-MISSING-BRACES )
      message( FATAL_ERROR "Compiler does not support '-Wno-missing-braces'." )
  endif()

  check_cxx_compiler_flag( "-Wno-comment" HAS_FLAG_WNO-COMMENT )
  if ( !HAS_FLAG_WNO-COMMENT )
      message( FATAL_ERROR "Compiler does not support '-Wno-comment'." )
  endif()

  check_cxx_compiler_flag( "-Wno-deprecated-copy" HAS_FLAG_WNO-DEPRECATED-COPY )
  if ( !HAS_FLAG_WNO-DEPRECATED-COPY )
      message( FATAL_ERROR "Compiler does not support '-Wno-deprecated-copy'." )
  endif()

  if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    check_cxx_compiler_flag( "-Wno-mismatched-tags" HAS_FLAG_WNO-MISMATCHED-TAGS )
    if ( !HAS_FLAG_WNO-MISMATCHED-TAGS )
        message( FATAL_ERROR "Compiler does not support '-Wno-mismatched-tags'." )
    endif()
  endif()

  check_cxx_compiler_flag( "-fstack-protector-all" HAS_FLAG_FSTACK-PROTECTOR-ALL )
  if ( !HAS_FLAG_FSTACK-PROTECTOR-ALL )
      message( FATAL_ERROR "Compiler does not support '-fstack-protector-all'." )
  endif()

  check_cxx_compiler_flag( "-Wno-ignored-attributes" HAS_FLAG_WNO-IGNORED-ATTRIBUTES )
  if ( !HAS_FLAG_WNO-IGNORED-ATTRIBUTES )
      message( FATAL_ERROR "Compiler does not support '-Wno-ignored-attributes'." )
  endif()

  check_cxx_compiler_flag( "-Wno-long-long" HAS_FLAG_WNO-LONG-LONG )
  if ( !HAS_FLAG_WNO-LONG-LONG )
      message( FATAL_ERROR "Compiler does not support '-Wno-long-long'." )
  endif()

  if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    check_cxx_compiler_flag( "-fno-var-tracking-assignments" HAS_FLAG_FNO-VAR-TRACKING-ASSIGNMENTS )
    if ( !HAS_FLAG_FNO-VAR-TRACKING-ASSIGNMENTS )
        message( FATAL_ERROR "Compiler does not support '-fno-var-tracking-assignments'." )
    endif()
  endif()
endif()

#------------------------------------------------------------------------------
# Linker options.
#------------------------------------------------------------------------------
include(CheckLinkerFlag)

#------------------------------------------------------------------------------
# Configurable file(s).
#------------------------------------------------------------------------------

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/bitcoin/explorer/version.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/bitcoin/explorer/version.hpp
  @ONLY )

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/version.cpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp
  @ONLY )

#------------------------------------------------------------------------------
# libbitcoin-explorer library
#------------------------------------------------------------------------------
add_library( libbitcoin-explorer )
add_library( bitcoin::explorer ALIAS libbitcoin-explorer )

target_compile_features( libbitcoin-explorer
  PUBLIC
    cxx_std_20
)

if ( NOT MSVC )
  target_compile_options( libbitcoin-explorer
    PRIVATE
      -Wall
      -Wextra
      $<$<COMPILE_LANGUAGE:CXX>:-Wno-reorder>
      $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-field-initializers>
      $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-braces>
      $<$<COMPILE_LANGUAGE:CXX>:-Wno-comment>
      $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-copy>
      $<$<CXX_COMPILER_ID:Clang>:-Wno-mismatched-tags>
      $<$<COMPILE_LANGUAGE:CXX>:-fstack-protector-all>
  )
endif()

if ( MSVC )
  if ( BUILD_SHARED_LIBS )
    target_compile_definitions( libbitcoin-explorer
      PRIVATE
        BCX_DLL
        _DLL
        _WINDLL
    )
  else()
    target_compile_definitions( libbitcoin-explorer
      PUBLIC
        BCX_STATIC
      PRIVATE
        _LIB
    )
  endif()
endif()

file( GLOB_RECURSE libbitcoin_explorer_HEADERS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include/*.ipp"
)

file( GLOB_RECURSE libbitcoin_explorer_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.cpp"
)

target_sources( libbitcoin-explorer
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
    FILES
      ${libbitcoin_explorer_HEADERS}
    FILE_SET HEADERS
    BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/include"
    FILES
      "${CMAKE_CURRENT_BINARY_DIR}/include/bitcoin/explorer/version.hpp"
  PRIVATE
    ${libbitcoin_explorer_SOURCES}
)

target_include_directories( libbitcoin-explorer
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries( libbitcoin-explorer
  PUBLIC
    bitcoin::network
)

add_custom_target( libbitcoin-explorer-version.cpp
  COMMAND ${CMAKE_COMMAND}
    -DGIT_EXECUTABLE=${GIT_EXECUTABLE}
    -DCONFIGURE_INPUT=${CMAKE_CURRENT_SOURCE_DIR}/../../src/version.cpp.in
    -DCONFIGURE_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp
    -P ${CMAKE_CURRENT_LIST_FILE}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp
  VERBATIM )

add_dependencies( libbitcoin-explorer libbitcoin-explorer-version.cpp )
target_sources( libbitcoin-explorer PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/version.cpp )

set_target_properties( libbitcoin-explorer
  PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME explorer
    OUTPUT_NAME bitcoin-explorer
)

#------------------------------------------------------------------------------
# libbitcoin-explorer-test tests
#------------------------------------------------------------------------------
if ( with-tests )
  add_executable( libbitcoin-explorer-test )

  enable_testing()

  add_test( NAME libbitcoin-explorer-test
    COMMAND libbitcoin-explorer-test
    --run_test=*
    --log_level=warning
    --show_progress=no
    --detect_memory_leak=0
    --report_level=no
    --build_info=yes
  )

  if ( WIN32 AND BUILD_SHARED_LIBS )
    set_tests_properties( libbitcoin-explorer-test
      PROPERTIES
        ENVIRONMENT_MODIFICATION
          "PATH=path_list_prepend:$<JOIN:$<TARGET_RUNTIME_DLL_DIRS:libbitcoin-explorer-test>,\;>"
    )
  endif()

  target_compile_features( libbitcoin-explorer-test
    PUBLIC
      cxx_std_20
  )

  if ( NOT MSVC )
    target_compile_options( libbitcoin-explorer-test
      PRIVATE
        -Wall
        -Wextra
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-reorder>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-field-initializers>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-braces>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-comment>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-copy>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-ignored-attributes>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-mismatched-tags>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-long-long>
        $<$<CXX_COMPILER_ID:GNU>:-fno-var-tracking-assignments>
        $<$<COMPILE_LANGUAGE:CXX>:-fstack-protector-all>
    )
  endif()

  if ( MSVC )
    target_compile_definitions( libbitcoin-explorer-test
      PRIVATE
        _CONSOLE
    )
  endif()

  file( GLOB_RECURSE libbitcoin_explorer_test_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/../../test/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../test/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../test/*.ipp"
  )

  file( GLOB_RECURSE libbitcoin_explorer_test_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/../../test/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../test/*.cpp"
  )

  target_sources( libbitcoin-explorer-test
    PRIVATE
      FILE_SET HEADERS
      BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../test"
      FILES
        ${libbitcoin_explorer_test_HEADERS}
    PRIVATE
      ${libbitcoin_explorer_test_SOURCES}
  )

  target_include_directories( libbitcoin-explorer-test
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../test>
  )

  target_link_libraries( libbitcoin-explorer-test
    PRIVATE
      bitcoin::explorer
  )

  set_target_properties( libbitcoin-explorer-test
    PROPERTIES
      VERSION ${PROJECT_VERSION}
      SOVERSION ${PROJECT_VERSION_MAJOR}
  )
endif()

#------------------------------------------------------------------------------
# bitcoin-explorer executable
#------------------------------------------------------------------------------
if ( with-console )
  add_library( bitcoin-explorer-objects STATIC )

  target_compile_features( bitcoin-explorer-objects
    PUBLIC
      cxx_std_20
  )

  if ( NOT MSVC )
    target_compile_options( bitcoin-explorer-objects
      PRIVATE
        -Wall
        -Wextra
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-reorder>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-field-initializers>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-braces>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-comment>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-copy>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-ignored-attributes>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-mismatched-tags>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-long-long>
        $<$<CXX_COMPILER_ID:GNU>:-fno-var-tracking-assignments>
        $<$<COMPILE_LANGUAGE:CXX>:-fstack-protector-all>
    )
  endif()

  if ( MSVC )
    target_compile_definitions( bitcoin-explorer-objects
      PRIVATE
        _CONSOLE
    )
  endif()

  file( GLOB_RECURSE bitcoin_explorer_objects_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/../../console/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../console/*.cpp"
  )

  target_sources( bitcoin-explorer-objects
    PRIVATE
      ${bitcoin_explorer_objects_SOURCES}
  )

  target_link_libraries( bitcoin-explorer-objects
    PRIVATE
      bitcoin::explorer
  )

  file( CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/bitcoin-explorer.cpp" CONTENT "" )
  add_executable( bitcoin-explorer "${CMAKE_CURRENT_BINARY_DIR}/bitcoin-explorer.cpp" )

  if ( WIN32 )
    file( GLOB bitcoin_explorer_RESOURCES CONFIGURE_DEPENDS
      "${CMAKE_CURRENT_SOURCE_DIR}/../../builds/msvc/*.rc" )
    target_sources( bitcoin-explorer PRIVATE ${bitcoin_explorer_RESOURCES} )
    target_include_directories( bitcoin-explorer
      PRIVATE
        $<TARGET_PROPERTY:bitcoin-explorer-objects,INCLUDE_DIRECTORIES>
    )

    if ( MSVC )
      target_link_options( bitcoin-explorer PRIVATE /MANIFEST:NO )
    endif()
  endif()

  target_link_libraries( bitcoin-explorer
    PRIVATE
      $<LINK_LIBRARY:WHOLE_ARCHIVE,bitcoin-explorer-objects>
  )

  set_target_properties( bitcoin-explorer
    PROPERTIES
      VERSION ${PROJECT_VERSION}
      SOVERSION ${PROJECT_VERSION_MAJOR}
      EXPORT_NAME explorer
      OUTPUT_NAME bx
  )
endif()

#------------------------------------------------------------------------------
# Installation routine.
#------------------------------------------------------------------------------
include( GNUInstallDirs )
include( CMakePackageConfigHelpers )

install( TARGETS libbitcoin-explorer
  EXPORT libbitcoin-explorer-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET HEADERS
)

install( EXPORT libbitcoin-explorer-targets
  NAMESPACE bitcoin::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libbitcoin-explorer
  FILE libbitcoin-explorer-targets.cmake
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/libbitcoin-explorer-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/libbitcoin-explorer-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libbitcoin-explorer
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/libbitcoin-explorer-config-version.cmake"
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libbitcoin-explorer-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/libbitcoin-explorer-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libbitcoin-explorer
)
if ( with-console )
  install( TARGETS bitcoin-explorer
    EXPORT bitcoin-explorer-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET HEADERS
  )

endif()
