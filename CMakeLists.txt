# Copyright (c) 2015-2020, CNRS
# Authors: Justin Carpentier <jcarpent@laas.fr>, Guilhem Saurel

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# Project properties
SET(PROJECT_ORG loco-3d)
SET(PROJECT_NAME multicontact-api)
SET(PROJECT_DESCRIPTION "API to define and store Contact phases and Contact Sequences")
SET(PROJECT_URL "https://github.com/${PROJECT_ORG}/${PROJECT_NAME}")

# Project options
OPTION(SUFFIX_SO_VERSION "Suffix library name with its version" ON)

# Project configuration
IF(NOT INSTALL_PYTHON_INTERFACE_ONLY)
  SET(PROJECT_USE_CMAKE_EXPORT TRUE)
ENDIF(NOT INSTALL_PYTHON_INTERFACE_ONLY)
SET(CUSTOM_HEADER_DIR "${PROJECT_NAME}")
SET(CMAKE_CXX_STANDARD 11)
SET(CXX_DISABLE_WERROR TRUE)
SET(DOXYGEN_USE_MATHJAX YES)

# JRL-cmakemodule setup
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/python.cmake)
INCLUDE(cmake/ide.cmake)

# Project definition
COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})
CHECK_MINIMAL_CXX_STANDARD(11 ENFORCE)

# Project dependencies
ADD_PROJECT_DEPENDENCY(pinocchio REQUIRED)
ADD_PROJECT_DEPENDENCY(curves 0.5.1 REQUIRED)
ADD_PROJECT_DEPENDENCY(Boost REQUIRED COMPONENTS serialization)
IF(NOT CURVES_WITH_PINOCCHIO_SUPPORT)
  MESSAGE(FATAL_ERROR "you need to use a curves version compiled with pinocchio support")
ENDIF(NOT CURVES_WITH_PINOCCHIO_SUPPORT)
IF(BUILD_TESTING)
  FIND_PACKAGE(Boost REQUIRED COMPONENTS unit_test_framework)
ENDIF(BUILD_TESTING)

IF(BUILD_PYTHON_INTERFACE)
  FINDPYTHON()
  SEARCH_FOR_BOOST_PYTHON(REQUIRED)
  STRING(REGEX REPLACE "-" "_" PY_NAME ${CUSTOM_HEADER_DIR})
  ADD_PROJECT_DEPENDENCY(eigenpy REQUIRED COMPONENTS "eigenpy${PYTHON_COMPONENT}")
  STRING(REGEX REPLACE "-" "_" PY_NAME ${PROJECT_NAME})
  SET(${PY_NAME}_INSTALL_DIR ${PYTHON_SITELIB}/${PY_NAME})
ENDIF(BUILD_PYTHON_INTERFACE)

# Main Library
SET(${PROJECT_NAME}_GEOMETRY_HEADERS
  include/${PROJECT_NAME}/geometry/curve-map.hpp
  include/${PROJECT_NAME}/geometry/ellipsoid.hpp
  include/${PROJECT_NAME}/geometry/fwd.hpp
  include/${PROJECT_NAME}/geometry/linear-cone.hpp
  include/${PROJECT_NAME}/geometry/second-order-cone.hpp
  )

SET(${PROJECT_NAME}_SERIALIZATION_HEADERS
  include/${PROJECT_NAME}/serialization/aligned-vector.hpp
  include/${PROJECT_NAME}/serialization/archive.hpp
  include/${PROJECT_NAME}/serialization/eigen-matrix.hpp
  include/${PROJECT_NAME}/serialization/spatial.hpp
  )

SET(${PROJECT_NAME}_SCENARIO_HEADERS
  include/${PROJECT_NAME}/scenario/contact-model.hpp
  include/${PROJECT_NAME}/scenario/contact-patch.hpp
  include/${PROJECT_NAME}/scenario/contact-phase.hpp
  include/${PROJECT_NAME}/scenario/contact-sequence.hpp
  include/${PROJECT_NAME}/scenario/fwd.hpp
  )


SET(${PROJECT_NAME}_PYTHON_HEADERS
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/geometry/ellipsoid.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/geometry/expose-geometry.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/geometry/linear-cone.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/geometry/second-order-cone.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/serialization/archive.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/scenario/contact-model.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/scenario/contact-patch.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/scenario/contact-phase.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/scenario/contact-sequence.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/scenario/expose-scenario.hpp
  ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/bindings/python/utils/printable.hpp
  )

SET(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_GEOMETRY_HEADERS}
  ${${PROJECT_NAME}_SERIALIZATION_HEADERS}
  ${${PROJECT_NAME}_SCENARIO_HEADERS}
  ${${PROJECT_NAME}_PYTHON_HEADERS}
  )

ADD_HEADER_GROUP(${${PROJECT_NAME}_HEADERS})

ADD_LIBRARY(${PROJECT_NAME} INTERFACE)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} INTERFACE $<INSTALL_INTERFACE:include>)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} INTERFACE pinocchio::pinocchio curves::curves)

IF(NOT INSTALL_PYTHON_INTERFACE_ONLY)
  INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${TARGETS_EXPORT_NAME} DESTINATION lib)
ENDIF(NOT INSTALL_PYTHON_INTERFACE_ONLY)

ADD_SUBDIRECTORY(bindings)
IF(BUILD_TESTING)
  ADD_SUBDIRECTORY(unittest)
ENDIF(BUILD_TESTING)

PKG_CONFIG_APPEND_BOOST_LIBS(serialization)
