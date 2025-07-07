cmake_minimum_required(VERSION 3.22)

# 项目基本设置
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# 构建类型设置
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# 项目名称设置
set(CMAKE_PROJECT_NAME mspm0_scheduler_mode)

# 包含工具链配置
include("cmake/gcc-arm-none-eabi.cmake")

# 包含构建配置
include("cmake/build-config.cmake")

# 启用编译命令导出（用于clangd等工具）
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# 核心项目设置
project(${CMAKE_PROJECT_NAME})
message("构建类型: " ${CMAKE_BUILD_TYPE})

# 启用C和汇编语言支持
enable_language(C ASM)

# 创建可执行文件目标
add_executable(${CMAKE_PROJECT_NAME})

# 添加TI MSPM0库
add_subdirectory(cmake/ti-mspm0)

# 添加源文件
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # User层源文件 (包含硬件初始化)
    code/User/Src/main.c
    code/User/Src/hardware_init.c
    code/User/Src/mspm0g3507_it.c
    
    # 启动文件 (位于cmake目录)
    cmake/startup_mspm0g3507.c

    # 系统调用存根
    cmake/syscalls.c
    
    # App层源文件
    code/App/Src/scheduler.c
    code/App/Src/appled.c
    code/App/Src/appuart.c


    # Components层源文件

)

# 添加包含目录
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # User层头文件
    code/User/Inc

    # App层头文件
    code/App/Inc

    # Components层头文件
)

# 添加编译宏定义
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # MSPM0G3507芯片定义
    __MSPM0G3507__
    DeviceFamily_MSPM0G350X
    
    # 调试模式定义
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Debug>:USE_FULL_ASSERT>
)

# 链接库
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    ti_mspm0_driverlib
    m  # 数学库
)

# 设置链接器属性
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${CMAKE_PROJECT_NAME}.map"
)

# 添加后处理命令生成bin和hex文件
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> bin/${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> bin/${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMENT "生成二进制和HEX文件，显示内存使用情况"
)