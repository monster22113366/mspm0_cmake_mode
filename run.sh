#!/bin/bash

# 转换 ELF 文件为二进制和 HEX 文件
elf_file="bin/mspm0_scheduler_mode.elf"
bin_file="bin/mspm0_scheduler_mode.bin"
hex_file="bin/mspm0_scheduler_mode.hex"


# 定义颜色代码
COLOR_RED="\033[1;31m"
COLOR_GREEN="\033[1;32m"
COLOR_YELLOW="\033[1;33m"
COLOR_BLUE="\033[1;34m"
COLOR_BOLD_GREEN="\033[1;32m"
COLOR_RESET="\033[0m"

# 记录编译开始时间
start_time=$(date +%s)

# 检查 build 文件夹是否存在，如果不存在则创建
if [ ! -d "build" ]; then
    mkdir build
    echo -e "${COLOR_BLUE}已创建 build 目录${COLOR_RESET}"
fi

# 进入 build 目录
cd build || {
    echo -e "${COLOR_RED}无法进入 build 目录！${COLOR_RESET}"
    exit 1
}

# 删除 build 目录下的所有文件
rm -rf * || {
    echo -e "${COLOR_RED}清理 build 目录失败！${COLOR_RESET}"
    exit 1
}

# 执行 CMake 和 Ninja 构建
echo -e "${COLOR_BLUE}正在生成构建系统...${COLOR_RESET}"
cmake -G Ninja .. || {
    echo -e "${COLOR_RED}CMake 配置失败！${COLOR_RESET}"
    exit 1
}
echo -e "${COLOR_BLUE}开始编译项目...${COLOR_RESET}"
ninja -j 10 || {
    echo -e "${COLOR_RED}编译失败！${COLOR_RESET}"
    exit 1
}


# if [ ! -f "$elf_file" ]; then
#     echo -e "${COLOR_RED}错误：未找到 ELF 文件 $elf_file！${COLOR_RESET}"
#     exit 1
# fi

# echo -e "${COLOR_BLUE}正在生成二进制文件...${COLOR_RESET}"
# arm-none-eabi-objcopy -O binary "$elf_file" "$bin_file" || {
#     echo -e "${COLOR_RED}错误：无法生成二进制文件 $bin_file！${COLOR_RESET}"
#     exit 1
# }

# echo -e "${COLOR_BLUE}正在生成 HEX 文件...${COLOR_RESET}"
# arm-none-eabi-objcopy -O ihex "$elf_file" "$hex_file" || {
#     echo -e "${COLOR_RED}错误：无法生成 HEX 文件 $hex_file！${COLOR_RESET}"
#     exit 1
# }

# 函数：打印内存使用进度条
print_memory_bar() {
    local used=$1
    local total=$2
    local label=$3
    
    # 转换为字节（输入单位为 KB）
    total_bytes=$((total * 1024))
    
    # 计算使用百分比
    if [ $total_bytes -eq 0 ]; then
        echo "错误：总大小不能为零！"
        return
    fi
    
    percent=$((used * 100 / total_bytes))
    ((percent > 100)) && percent=100

    # 根据百分比选择颜色
    if [ $percent -ge 90 ]; then
        color=$COLOR_RED
    elif [ $percent -ge 80 ]; then
        color=$COLOR_YELLOW
    else
        color=$COLOR_GREEN
    fi

    # 构建进度条
    bar_length=30
    filled=$((percent * bar_length / 100))
    empty=$((bar_length - filled))
    bar=$(printf "%${filled}s" | tr ' ' '█')
    space=$(printf "%${empty}s")

    # 转换使用量为 KB 并格式化输出
    used_kb=$(awk "BEGIN {printf \"%.2f\", $used/1024}")
    echo -e "${label}: ${color}${bar}${space}${COLOR_RESET} ${used_kb}KB/${total}KB (${percent}%)"
}

# 获取内存使用数据

size_info=$(arm-none-eabi-size "$elf_file" | tail -n1)
text=$(awk '{print $1}' <<< $size_info)
data=$(awk '{print $2}' <<< $size_info)
bss=$(awk '{print $3}' <<< $size_info)

# 计算内存使用量（单位：字节）
rom_used=$((text + data))      # Flash 使用量 = text + data
ram_used=$((data + bss))       # RAM 使用量 = data + bss
ccmram_used=$(arm-none-eabi-objdump -h "$elf_file" | awk '/.ccmram/ {print "0x"$3}' | xargs printf '%d')

# 设置芯片内存参数（根据实际芯片修改以下数值）
FLASH_SIZE=128   # KB
RAM_SIZE=12     # KB
CCMRAM_SIZE=64   # KB



# 返回上一级目录
cd .. || {
    echo -e "${COLOR_RED}无法返回上一级目录！${COLOR_RESET}"
    exit 1
}

# 运行 OpenOCD 进行烧录
echo -e "${COLOR_BLUE}正在启动 OpenOCD 烧录...${COLOR_RESET}"
openocd -f openocd.cfg || {
    echo -e "${COLOR_RED}OpenOCD 烧录失败！${COLOR_RESET}"
    exit 1
}

# 计算编译耗时
end_time=$(date +%s)
duration=$((end_time - start_time))



# 打印成功信息
echo -e "\n${COLOR_GREEN}编译和烧录成功！！！${COLOR_RESET}"
echo -e "${COLOR_GREEN}总耗时：${duration}秒${COLOR_RESET}"

# 显示内存使用情况
echo -e "\n${COLOR_BOLD_GREEN}内存使用分析：${COLOR_RESET}"
print_memory_bar $rom_used $FLASH_SIZE "FLASH"
print_memory_bar $ram_used $RAM_SIZE "RAM"
[ $CCMRAM_SIZE -gt 0 ] && print_memory_bar $ccmram_used $CCMRAM_SIZE "CCMRAM"