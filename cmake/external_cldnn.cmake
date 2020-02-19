# ******************************************************************************
# Copyright 2017-2020 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ******************************************************************************

# Enable ExternalProject CMake module
include(ExternalProject)

#------------------------------------------------------------------------------
# Download and install GoogleTest ...
#------------------------------------------------------------------------------

set(CLDNN_GIT_REPO_URL https://github.com/opencv/dldt.git)
set(CLDNN_GIT_LABEL 2020.1)
set(CLDNN_SUBDIR inference-engine/thirdparty/clDNN)

ExternalProject_Add(
    ext_cldnn
    PREFIX cldnn
    GIT_REPOSITORY ${CLDNN_GIT_REPO_URL}
    GIT_TAG ${CLDNN_GIT_LABEL}
    # Disable install step
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    SOURCE_SUBDIR ${CLDNN_SUBDIR}
    CMAKE_GENERATOR ${CMAKE_GENERATOR}
    CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
    CMAKE_GENERATOR_TOOLSET ${CMAKE_GENERATOR_TOOLSET}
    CMAKE_ARGS
                ${NGRAPH_FORWARD_CMAKE_ARGS}
                -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                # -DCLDNN__OUTPUT_DIR=out/Debug
                -DCLDNN__INCLUDE_TESTS=OFF
                -DCLDNN__INCLUDE_CORE_INTERNAL_TESTS=OFF
                -DCLDNN__INCLUDE_TUTORIAL=OFF
    EXCLUDE_FROM_ALL TRUE
    )

#------------------------------------------------------------------------------

add_library(libcldnn INTERFACE)
if (CLDNN_ROOT_DIR)
    find_package(CLDNN REQUIRED)
    target_include_directories(libcldnn SYSTEM INTERFACE ${CLDNN_INCLUDE_DIRS})
    target_link_libraries(libcldnn INTERFACE ${CLDNN_LIBRARIES})
    install(
        FILES
            ${CLDNN_LIBRARIES}
        DESTINATION
            ${NGRAPH_INSTALL_LIB}
        OPTIONAL
        )
else()
    ExternalProject_Get_Property(ext_cldnn SOURCE_DIR BINARY_DIR)
    set(CLDNN_OUT_DIR ${SOURCE_DIR}/${CLDNN_SUBDIR}/build/out/Linux64/${CMAKE_BUILD_TYPE})
    set(CLDNN_LIB ${CMAKE_STATIC_LIBRARY_PREFIX}clDNN64${CMAKE_STATIC_LIBRARY_SUFFIX})
    ExternalProject_Add_Step(
        ext_cldnn
        CopyCLDNN
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CLDNN_OUT_DIR}/${CLDNN_LIB} ${NGRAPH_LIBRARY_OUTPUT_DIRECTORY}/${CLDNN_LIB}
        COMMENT "Copy cldnn runtime libraries to ngraph build directory."
        DEPENDEES install
        )
    add_dependencies(libcldnn ext_cldnn)
    target_include_directories(libcldnn SYSTEM INTERFACE ${SOURCE_DIR}/${CLDNN_SUBDIR}/api)
    target_link_libraries(libcldnn INTERFACE ${NGRAPH_LIBRARY_OUTPUT_DIRECTORY}/${CLDNN_LIB})
    install(
        FILES
            ${NGRAPH_LIBRARY_OUTPUT_DIRECTORY}/${CLDNN_LIB}
        DESTINATION
            ${NGRAPH_INSTALL_LIB}
        OPTIONAL
        )
endif()
