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

set(WIDGET_SRC
    ${INCLUDE_DIR}/widget/widgetinit.h
)

set(PUGIXML_SRC
    ${INCLUDE_DIR}/pugixml/pugiconfig.hpp
    ${INCLUDE_DIR}/pugixml/pugixml.hpp
    ${SOURCEC_DIR}/pugixml/pugixml.cpp
)

set(HTTP_SRC
    ${INCLUDE_DIR}/http/httplib.h
    ${INCLUDE_DIR}/http/httpclientbase.h
    ${SOURCEC_DIR}/http/httpclientbase.cpp
    ${INCLUDE_DIR}/http/httpserverbase.h
    ${SOURCEC_DIR}/http/httpserverbase.cpp
    ${INCLUDE_DIR}/http/httpserverhandel.h
    ${INCLUDE_DIR}/http/httpclient.h
    ${SOURCEC_DIR}/http/httpclient.cpp
)

set(UTIL_SRC
    ${INCLUDE_DIR}/util/file_util.h
    ${INCLUDE_DIR}/util/platform_util.h
    ${INCLUDE_DIR}/util/random_number.h
    ${INCLUDE_DIR}/util/random_util.hpp
    ${INCLUDE_DIR}/util/string_util.h
    ${INCLUDE_DIR}/util/platform_define.h
    ${INCLUDE_DIR}/util/mysqlserverconfig.h
    ${INCLUDE_DIR}/util/emailsenderconfig.h
    ${INCLUDE_DIR}/util/threadpool.hpp
    ${SOURCEC_DIR}/util/file_util.cpp
    ${SOURCEC_DIR}/util/platform_util.cpp
    ${SOURCEC_DIR}/util/random_number.cpp
    ${SOURCEC_DIR}/util/string_util.cpp
    ${SOURCEC_DIR}/util/mysqlserverconfig.cpp
    ${SOURCEC_DIR}/util/emailsenderconfig.cpp
)

set(CONFIGFILE_SRC
    ${INCLUDE_DIR}/configfile/config_file.h
    ${SOURCEC_DIR}/configfile/config_file.cpp
)

set(PARSER_SRC
    ${SOURCEC_DIR}/configfile/parser_builder/parser/config_file_content_parser.h
    ${SOURCEC_DIR}/configfile/parser_builder/parser/config_file_content_parser_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/parser/config_file_content_parser_handle_builder.h
    ${SOURCEC_DIR}/configfile/parser_builder/parser/ini_parser_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/parser/json_parser_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/parser/xml_parser_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/parser/config_file_content_parser.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/parser/config_file_content_parser_handle.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/parser/config_file_content_parser_handle_builder.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/parser/ini_parser_handle.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/parser/json_parser_handle.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/parser/xml_parser_handle.cpp
)

set(BUILDER_SRC
    ${SOURCEC_DIR}/configfile/parser_builder/builder/config_file_content_builder.h
    ${SOURCEC_DIR}/configfile/parser_builder/builder/config_file_content_builder_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/builder/config_file_content_builder_handle_builder.h
    ${SOURCEC_DIR}/configfile/parser_builder/builder/ini_builder_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/builder/json_builder_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/builder/xml_builder_handle.h
    ${SOURCEC_DIR}/configfile/parser_builder/builder/config_file_content_builder.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/builder/config_file_content_builder_handle.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/builder/config_file_content_builder_handle_builder.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/builder/ini_builder_handle.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/builder/json_builder_handle.cpp
    ${SOURCEC_DIR}/configfile/parser_builder/builder/xml_builder_handle.cpp
)

set(EXECUTABLEPROGRAM_SRC
    ${INCLUDE_DIR}/executableprogram/executableprogram.h
    ${SOURCEC_DIR}/executableprogram/executableprogram.cpp
    ${INCLUDE_DIR}/executableprogram/emailsenderprogram.h
    ${SOURCEC_DIR}/executableprogram/emailsenderprogram.cpp
    ${INCLUDE_DIR}/executableprogram/mysqlprogram.h
    ${SOURCEC_DIR}/executableprogram/mysqlprogram.cpp
)

#筛选显示
source_group(json FILES ${MESSAGE_SRC})
source_group(transmitcenter FILES ${TRANSMITCENTER_SRC})
source_group(pugixml FILES ${PUGIXML_SRC})
source_group(http FILES ${HTTP_SRC})
source_group(util FILES ${UTIL_SRC})
source_group(widget FILES ${WIDGET_SRC})
source_group(configfile FILES ${CONFIGFILE_SRC})
source_group(configfile/parser FILES ${PARSER_SRC})
source_group(configfile/builder FILES ${BUILDER_SRC})
source_group(executableprogram FILES ${EXECUTABLEPROGRAM_SRC})

set(SRCS 
	${TRANSMITCENTER_SRC}
	${JSON_SRC}
	${PUGIXML_SRC}
	${HTTP_SRC}
	${UTIL_SRC}
	${WIDGET_SRC}
	${CONFIGFILE_SRC}
	${PARSER_SRC}
	${BUILDER_SRC}
	${EXECUTABLEPROGRAM_SRC}
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

if(UNIX)
set(UNIX_L
    pthread
) 
endif(UNIX)

if(WIN32)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
set(MingW_L
	ws2_32
)
endif()
endif(WIN32)

#链接库
target_link_libraries(${PROJECT_NAME}
  ${Qt5Core_LIBRARIES}
  ${UNIX_L}
  ${MingW_L}
)
