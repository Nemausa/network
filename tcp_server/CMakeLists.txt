cmake_minimum_required(VERSION 2.8.12)

string(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} ) 
project(${CURRENT_FOLDER})

file(GLOB ${PROJECT_NAME}_SRC
	"../implementation/depends/src/*.cpp"
	"../implementation/config/src/*.cpp"
	"src/*.cpp"
)

list (SORT ${PROJECT_NAME}_SRC)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )

# target_link_libraries(${PROJECT_NAME} spdlog)
target_link_libraries(${PROJECT_NAME} glog)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(status " Windows")
	target_link_libraries(${PROJECT_NAME} ws2_32)
	target_link_libraries(${PROJECT_NAME} iphlpapi)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib  # 动态库安装路径
	ARCHIVE DESTINATION lib  # 静态库安装路径
	RUNTIME DESTINATION bin  # 可执行文件安装路径
	PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)