import re
import os

# 读取omni_kconfig.h文件
with open('omni_kconfig.h', 'r') as file:
    kconfig_content = file.read()

# 提取宏定义并转换为CMake变量
cmake_variables = []
for match in re.finditer(r'#define (\w+) (\S+)', kconfig_content):
    macro = match.group(1)
    value = match.group(2)
    cmake_variables.append(f'set({macro} {value})')

# 检查omni_kconfig.cmake文件是否存在，若不存在则创建
cmake_file_path = 'omni_kconfig.cmake'
with open(cmake_file_path, 'w') as file:
    file.write('\n'.join(cmake_variables))
    print("Finish converting kconfig to cmake")