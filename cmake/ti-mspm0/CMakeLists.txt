# TI MSPM0 DriverLib CMake配置 - 最小化版本
cmake_minimum_required(VERSION 3.22)

# 启用C和汇编语言支持
enable_language(C ASM)

# MSPM0编译宏定义
set(MSPM0_Defines_Syms 
    __MSPM0G3507__
    DeviceFamily_MSPM0G350X
    $<$<CONFIG:Debug>:DEBUG>
)

# MSPM0包含目录 - 设置正确的包含路径
set(MSPM0_Include_Dirs
    ${CMAKE_SOURCE_DIR}/code/Driver
    ${CMAKE_SOURCE_DIR}/code/Driver/ti
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/devices
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/devices/msp
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/devices/msp/m0p
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/devices/msp/peripherals
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib/m0p
    ${CMAKE_SOURCE_DIR}/code/Driver/CMSIS/Core/Include
)

# 只编译我们实际需要的DriverLib模块
set(MSPM0_DriverLib_Src
    # 基础模块
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib/dl_common.c
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib/dl_uart.c
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib/dl_timer.c
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib/dl_vref.c
    
    # M0P特定源文件
    ${CMAKE_SOURCE_DIR}/code/Driver/ti/driverlib/m0p/dl_interrupt.c
)

# 创建TI MSPM0 DriverLib静态库
add_library(ti_mspm0_driverlib STATIC)

# 添加源文件到库
target_sources(ti_mspm0_driverlib PRIVATE ${MSPM0_DriverLib_Src})

# 设置包含目录
target_include_directories(ti_mspm0_driverlib PUBLIC ${MSPM0_Include_Dirs})

# 设置编译定义
target_compile_definitions(ti_mspm0_driverlib PUBLIC ${MSPM0_Defines_Syms})

# 设置编译选项 - 抑制TI DriverLib的警告
target_compile_options(ti_mspm0_driverlib PRIVATE
    -Wall
    -Wextra
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-pedantic
    -Wno-enum-int-mismatch
)

# 输出配置信息
message(STATUS "TI MSPM0 DriverLib配置完成 (最小化版本)")
message(STATUS "包含目录: ${MSPM0_Include_Dirs}")
message(STATUS "编译定义: ${MSPM0_Defines_Syms}")

# 创建接口库用于链接
add_library(ti_mspm0_interface INTERFACE)
target_link_libraries(ti_mspm0_interface INTERFACE ti_mspm0_driverlib)
target_include_directories(ti_mspm0_interface INTERFACE ${MSPM0_Include_Dirs})
target_compile_definitions(ti_mspm0_interface INTERFACE ${MSPM0_Defines_Syms})