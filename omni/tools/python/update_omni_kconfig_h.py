import re

# Read omni_kconfig.h file
with open('omni_kconfig.h', 'r') as file:
    kconfig_content = file.read()

    # Replace #define "#value" with #define value
    processed_content = re.sub(r'#define (\w+) "#(.*?)"', r'#define \1 \2', kconfig_content)

# Write back to omni_kconfig.h file only if content has changed
if processed_content != kconfig_content:
    with open('omni_kconfig.h', 'w') as file:
        file.write(processed_content)
    print('Updated omni kconfig header file in omni_kconfig.h')
else:
    print('No changes to omni kconfig header file in omni_kconfig.h')