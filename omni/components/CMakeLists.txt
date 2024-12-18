# Copyright (c) 2024 LuckkMaker
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_library(omni-components INTERFACE)

# omni cherryusb component
omni_lib_src_ifdef(CONFIG_COMPONENT_CHERRYUSB omni-components
    cherryusb/usb_device.c
)

omni_lib_inc_ifdef(CONFIG_COMPONENT_CHERRYUSB omni-components
    cherryusb
)

# omni console (letter shell) component
omni_lib_src_ifdef(CONFIG_COMPONENT_CONSOLE omni-components
    console/console.c
)

omni_lib_inc_ifdef(CONFIG_COMPONENT_CONSOLE omni-components
    console
)

# omni command component
omni_lib_src_ifdef(CONFIG_COMPONENT_COMMAND omni-components
    command/command.c
)

omni_lib_inc_ifdef(CONFIG_COMPONENT_COMMAND omni-components
    command
)

target_include_directories(omni-components INTERFACE
    .
    include
)