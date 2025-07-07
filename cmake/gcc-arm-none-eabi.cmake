




# ARM GCC工具链配置文件
# 适用于MSPM0G3507 (Cortex-M0+)

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# ARM工具链前缀设置
set(TOOLCHAIN_PREFIX                arm-none-eabi-)

# 编译器设置
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

# 可执行文件后缀
set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

# 设置编译目标类型
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU特定标志 - MSPM0G3507 (Cortex-M0+)
set(TARGET_FLAGS "-mcpu=cortex-m0plus -mthumb")

# 编译器标志
set(CMAKE_C_FLAGS "${TARGET_FLAGS} -Wall -Wextra -fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS "${TARGET_FLAGS} -Wall -Wextra -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${TARGET_FLAGS} -x assembler-with-cpp")

# 警告控制 - 针对TI驱动库的兼容性优化
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-unused-variable")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pedantic")  # 禁用pedantic警告以兼容TI驱动库
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic")

# Debug模式标志
set(CMAKE_C_FLAGS_DEBUG "-Og -g3 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g3 -ggdb")
set(CMAKE_ASM_FLAGS_DEBUG "-g3 -ggdb")

# Release模式标志
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")
set(CMAKE_ASM_FLAGS_RELEASE "")

# C++特定标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

# 链接器脚本
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/cmake/mspm0g3507.ld")

# 链接器标志
set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS} -T${LINKER_SCRIPT} -Wl,--gc-sections -Wl,--print-memory-usage -Wl,-Map=${CMAKE_PROJECT_NAME}.map")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u _printf_float")  # 支持printf浮点数
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-warn-rwx-segments")

# Debug和Release链接器标志
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-Wl,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-Wl,--print-memory-usage -Wl,--strip-debug")

# 禁用编译器检查
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)