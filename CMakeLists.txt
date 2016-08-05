# This project is designed to be built outside the Insight source tree.
cmake_minimum_required(VERSION 2.8)
PROJECT(tinterpcurve)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin)

#
# Project Headers
#
SET(P_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip/ainterpCurve.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip/ainterpCurveLinear.h
    #${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip/ainterpCurveCubic.h
    #${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip/ainterpCurveSpline.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ainterpCurveSplineTK.h
)

#
# Project Sources
#
SET(P_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/dip/ainterpCurveLinear.cxx
    #${CMAKE_CURRENT_SOURCE_DIR}/../../../src/dip/ainterpCurveCubic.cxx
    #${CMAKE_CURRENT_SOURCE_DIR}/../../../src/dip/ainterpCurveSpline.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/ainterpCurveSplineTK.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/myinterpcurve.cxx
)

INCLUDE_DIRECTORIES(
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip
)
LINK_DIRECTORIES(
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib
)

LINK_LIBRARIES( debug atkd optimized atk )


ADD_EXECUTABLE( ${PROJECT_NAME} main.cpp
                                ${P_HDRS}  ${P_SRCS}
)


