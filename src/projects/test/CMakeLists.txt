project(test)

#C++标准 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#全局moc
set(CMAKE_AUTOMOC ON)

#使用rcc处理qrc
set(IMAGE_RCCS ${CMAKE_SOURCE_DIR}/src/resource/${PROJECT_NAME}/resource.qrc)
qt5_add_resources(IMAGE_RCC_SRCS ${IMAGE_RCCS})

#ui文件
file(GLOB uis "${CMAKE_SOURCE_DIR}/src/ui/${PROJECT_NAME}/*.ui")

#uic
QT5_WRAP_UI(UI_FILES
  ${uis}
)

set(UI_SRC
	${uis}
)
set(MAIN_SRC
	main.cpp
)

set(SRCS
	${MAIN_SRC}
)

#筛选显示
source_group(main FILES ${MAIN_SRC})

#包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_SOURCE_DIR}/external
					${CMAKE_SOURCE_DIR}/src/projects
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

#链接静态库
link_libraries(
	client_win
)

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

#可执行文件
add_executable(${PROJECT_NAME} ${SRCS} ${UI_FILES} ${IMAGE_RCC_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${output_dir}/bin/${CMAKE_CFG_INTDIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_ENVIRONMENT "Path=$(Path);${CMAKE_PREFIX_PATH}/bin")

#链接库
target_link_libraries(${PROJECT_NAME}
  ${Qt5Core_LIBRARIES}
  ${Qt5Gui_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  client_win
  core
)