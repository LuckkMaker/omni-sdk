import os
import sys

# 获取命令行参数
if len(sys.argv) != 3:
    print("Usage: clear_old_kconfig.py <config_file_path> <config_old_file_path>")
    sys.exit(1)

config_file_path = sys.argv[1]
config_old_file_path = sys.argv[2]

# Function to clear the content of a file
def create_or_clear_file(path):
    try:
        # Create or clear the configuration file
        with open(path, 'w') as file:
            file.write('')
        print(f"Cleared old Kconfig file {path}")
    except OSError as e:
        print(f"An error occurred while creating or clearing file {path}: {e}")

# Create or clear the configuration file
create_or_clear_file(config_file_path)