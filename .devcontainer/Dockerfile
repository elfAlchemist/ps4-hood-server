FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
ENV OO_PS4_TOOLCHAIN="/opt/OpenOrbis/PS4Toolchain"
ENV DOTNET_SYSTEM_GLOBALIZATION_INVARIANT=1

# Install packages needed for PS4 development (matching GitHub workflow)
RUN apt-get update && apt-get upgrade -y
RUN apt-get -y install --no-install-recommends \
    unzip \
    build-essential \
    clang-18 \
    lld-18 \
    llvm-18 \
    imagemagick \
    wget \
    curl \
    tar \
    lsb-release \
    software-properties-common \
    gnupg

RUN ln -s /usr/bin/clang-18 /usr/bin/clang && \
    ln -s /usr/bin/clang++-18 /usr/bin/clang++ && \
    ln -s /usr/bin/ld.lld-18 /usr/bin/ld.lld && \
    ln -s /usr/bin/llvm18-ar /usr/bin/llvm-ar && \
    ln -s /usr/bin/llvm18-ranlib /usr/bin/llvm-ranlib && \
    ln -s /usr/bin/llvm18-strip /usr/bin/llvm-strip

# Install additional dependencies for PS4 development
RUN wget --no-verbose http://archive.ubuntu.com/ubuntu/pool/main/o/openssl/libssl1.1_1.1.0g-2ubuntu4_amd64.deb \
    && dpkg -i libssl1.1_1.1.0g-2ubuntu4_amd64.deb \
    && rm libssl1.1_1.1.0g-2ubuntu4_amd64.deb \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain/releases/download/v0.5.3/toolchain-llvm-18.2.zip
RUN unzip toolchain-llvm-18.2.zip && \
    rm toolchain-llvm-18.2.zip && \
    tar -xzvf toolchain-llvm-18.tar.gz -C /opt && \
    rm toolchain-llvm-18.tar.gz
