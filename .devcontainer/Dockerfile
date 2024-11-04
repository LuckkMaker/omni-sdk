# Use the ubuntu image as the base image
FROM ubuntu:22.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Set arm-none-eabi-gcc toolchain version
ARG TARGETPLATFORM
ARG BUILDPLATFORM
ARG TOOLS_PATH=/opt/gcc-arm-none-eabi
ARG ARM_VERSION=13.2.rel1

# Replace APT sources
RUN set -eux \
    && sed -i 's/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list \
    && apt-get update \
    && apt-get install -y apt-transport-https ca-certificates \
    && sed -i 's/http/https/g' /etc/apt/sources.list \
    && apt-get -yq clean \
    && rm -rf /var/lib/apt/lists/* \
    && exit 0

# Install packages
RUN set -eux \
    && apt-get update && apt-get install -y \
    build-essential git wget curl unzip tar xz-utils python3 openocd \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && exit 0

# Install cmake
RUN set -eux \
    && wget https://github.com/Kitware/CMake/releases/download/v3.28.5/cmake-3.28.5-linux-x86_64.sh -q -O /tmp/cmake-install.sh \
    # && wget https://cmake.org/files/v3.28/cmake-3.28.5-linux-x86_64.sh -q -O /tmp/cmake-install.sh \
    && chmod u+x /tmp/cmake-install.sh \
    && mkdir /opt/cmake-3.28.5 \
    && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-3.28.5 \
    && ln -s /opt/cmake-3.28.5/bin/* /usr/local/bin \
    && cmake --version \
    && rm /tmp/cmake-install.sh

# Install ARM Toolchain
RUN if [ "$TARGETPLATFORM" = "linux/amd64" ]; then export ARM_ARCH=x86_64; \
    else export ARM_ARCH=aarch64; \
    fi \
    && echo "Downloading ARM GNU GCC for Platform: $ARM_ARCH" \
    && mkdir -p ${TOOLS_PATH} \
    && curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-${ARM_ARCH}-arm-none-eabi.tar.xz" \
    && tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C ${TOOLS_PATH} \
    && rm gcc-arm-none-eabi.tar.xz \
    && rm ${TOOLS_PATH}/*.txt \
    && rm -rf ${TOOLS_PATH}/share/doc \
    && ln -s ${TOOLS_PATH}/bin/* /usr/local/bin \
    && echo "export PATH=\$PATH:${TOOLS_PATH}/bin" >> /etc/profile \
    && arm-none-eabi-gcc --version

# Install python pip
RUN set -eux \
    && python3 --version \
    && curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py \
    && python3 get-pip.py \
    && rm get-pip.py \
    && python3 -m pip install -U pip \
    && pip3 --version \
    && pip3 install --upgrade pip setuptools wheel \
    && pip3 --version \
    && exit 0

# # Install python packages
RUN set -eux \
    && pip3 --version \
    && pip3 install --upgrade pip setuptools wheel \
    && pip3 --version \
    && pip3 install kconfiglib \
    && exit 0

# Set OMNI_BASE environment variable
ENV OMNI_BASE=/workspace/omni

# Set the working directory
WORKDIR /workspace

# Set the default shell to bash
CMD ["/bin/bash"]