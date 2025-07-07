# MSPM0构建配置文件
# 包含构建相关的配置和选项

# 构建选项
option(ENABLE_DEBUG_PRINT "Enable debug print output" ON)
option(ENABLE_ASSERT "Enable assert macros" ON)
option(ENABLE_OPTIMIZATION "Enable compiler optimization" OFF)

# 目标设备配置
set(TARGET_DEVICE "MSPM0G3507" CACHE STRING "Target device name")
set(TARGET_BOARD "LAUNCHPAD" CACHE STRING "Target board name")

# 编译定义
if(ENABLE_DEBUG_PRINT)
    add_compile_definitions(DEBUG_PRINT_ENABLED)
endif()

if(ENABLE_ASSERT)
    add_compile_definitions(ASSERT_ENABLED)
endif()

# 优化设置
if(ENABLE_OPTIMIZATION)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O1")
else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
endif()

# 警告设置 - 针对用户代码的严格警告
set(USER_WARNING_FLAGS "-Wall -Wextra -Wshadow -Wundef -Wno-unused-parameter")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USER_WARNING_FLAGS}")

# 针对TI DriverLib的宽松警告设置
set(DRIVERLIB_WARNING_FLAGS "-Wall -Wno-pedantic -Wno-unused-parameter -Wno-unused-variable")

# 调试信息
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")

# 输出目录设置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

message(STATUS "Build configuration:")
message(STATUS "  Target Device: ${TARGET_DEVICE}")
message(STATUS "  Target Board: ${TARGET_BOARD}")
message(STATUS "  Debug Print: ${ENABLE_DEBUG_PRINT}")
message(STATUS "  Assert: ${ENABLE_ASSERT}")
message(STATUS "  Optimization: ${ENABLE_OPTIMIZATION}")