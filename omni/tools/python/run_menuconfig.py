import subprocess
import os

# 指定工作目录
working_directory = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))

# 打印工作目录以进行调试
print(f"Working directory: {working_directory}")

# 运行 menuconfig 命令
subprocess.run(['menuconfig'], shell=True, cwd=working_directory)