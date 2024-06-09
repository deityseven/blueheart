project(core)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#全局moc
set(CMAKE_AUTOMOC ON)

set(INCLUDE_DIR include)
set(SOURCEC_DIR src)

set(TRANSMITCENTER_SRC
    ${INCLUDE_DIR}/transmitcenter/transmitcenter.h
    ${INCLUDE_DIR}/transmitcenter/serializable.h
    ${SOURCEC_DIR}/transmitcenter/transmitcenter.cpp
    ${SOURCEC_DIR}/transmitcenter/serializable.cpp
)

set(JSON_SRC
    ${INCLUDE_DIR}/json/json.hpp
)

set(PUGIXML_SRC
    ${INCLUDE_DIR}/pugixml/pugiconfig.hpp
    ${INCLUDE_DIR}/pugixml/pugixml.hpp
    ${SOURCEC_DIR}/pugixml/pugixml.cpp
)

set(HTTP_SRC
    ${INCLUDE_DIR}/http/httplib.h
    ${INCLUDE_DIR}/http/httpclientbase.h
    ${INCLUDE_DIR}/http/httpserverbase.h
    ${INCLUDE_DIR}/http/httpserverhandel.h
    ${SOURCEC_DIR}/http/httpclientbase.cpp
    ${SOURCEC_DIR}/http/httpserverbase.cpp
)

set(UTIL_SRC
    ${INCLUDE_DIR}/util/file_util.h
    ${INCLUDE_DIR}/util/platform_util.h
    ${INCLUDE_DIR}/util/random_number.h
    ${INCLUDE_DIR}/util/random_util.hpp
    ${INCLUDE_DIR}/util/string_util.h
    ${INCLUDE_DIR}/util/platform_define.h
    ${INCLUDE_DIR}/util/threadpool.hpp
    ${SOURCEC_DIR}/util/file_util.cpp
    ${SOURCEC_DIR}/util/platform_util.cpp
    ${SOURCEC_DIR}/util/random_number.cpp
    ${SOURCEC_DIR}/util/string_util.cpp
)

#筛选显示
source_group(json FILES ${MESSAGE_SRC})
source_group(transmitcenter FILES ${TRANSMITCENTER_SRC})
source_group(pugixml FILES ${PUGIXML_SRC})
source_group(http FILES ${HTTP_SRC})
source_group(util FILES ${UTIL_SRC})

set(SRCS 
	${TRANSMITCENTER_SRC}
	${JSON_SRC}
	${PUGIXML_SRC}
	${HTTP_SRC}
	${UTIL_SRC}
)

message(${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
)

#库目录
link_directories(
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

#指定编译字符集
if(MSVC)
add_compile_options(/utf-8)
endif(MSVC)

#预编译宏
#add_definitions(XXXX)

if(WIN32)
#链接库
link_libraries( 
)
endif(WIN32)

if(UNIX)
#链接库
link_libraries( 
) 
endif(UNIX)

#共享库
add_library(${PROJECT_NAME} STATIC ${SRCS} ${UI_FILES} ${IMAGE_RCC_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${output_dir}/bin/${CMAKE_CFG_INTDIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "Path=$(Path);${CMAKE_PREFIX_PATH}/bin")

#链接库
target_link_libraries(${PROJECT_NAME}
  ${Qt5Core_LIBRARIES}
)
