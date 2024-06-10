project(client_win)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#全局moc
set(CMAKE_AUTOMOC ON)

set(MESSAGE_SRC
    message/message.h
    message/message.cpp
    message/signinrequest.h
    message/signinrequest.cpp
    message/signinresponse.h
    message/signinresponse.cpp
    message/checknumberrequest.h
    message/checknumberrequest.cpp
    message/checknumberresponse.h
    message/checknumberresponse.cpp
    message/loginrequest.h
    message/loginrequest.cpp
    message/loginresponse.h
    message/loginresponse.cpp
)

set(CLIENT_WIN_SRC
    #usecartime.h
    #usecartime.cpp
)

set(HTTPCLIENT_SRC
    httpclient/httpclient.h
    httpclient/httpclient.cpp
)

#筛选显示
source_group(message FILES ${MESSAGE_SRC})
source_group(httpclient FILES ${HTTPCLIENT_SRC})

set(SRCS 
	${MESSAGE_SRC}
	${CLIENT_WIN_SRC}
	${HTTPCLIENT_SRC}
)

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/src/projects/core/include
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
  core
)
