FROM ubuntu:22.04

# 避免弹出交互式配置
ARG DEBIAN_FRONTEND=noninteractive 
# 设置容器时区
ENV TZ=Asia/Shanghai
# 设置shell为bash，否则默认为sh，-c：表示后面的命令是字符串
SHELL ["/bin/bash", "-c"]

# 清理apt缓存（Debian和Ubuntu），减小镜像体积
RUN apt-get clean && \
    apt-get autoclean

# 更新源列表并安装ca-certificates以确保SSL证书可以被验证
# RUN apt-get update && apt-get install -y ca-certificates && update-ca-certificates

# 使用不需要 HTTPS 的源进行更新和安装ca-certificates
RUN sed -i 's|https://|http://|g' /etc/apt/sources.list && \
    apt-get update && apt-get install -y ca-certificates && update-ca-certificates

# 复制当前目录下文件到镜像/etc/apt/目录下
# 这是一个软件源的配置文件，用于替换默认的软件源
COPY apt/sources.list /etc/apt/

# 安装环境依赖
RUN apt-get update  && apt-get upgrade -y  && \
    apt-get install -y \
    htop \
    apt-utils \
    curl \
    cmake \
    git \
    openssh-server \
    build-essential \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    libboost-all-dev \
    net-tools \
    vim \
    stress 

# libc-ares-dev: c-ares是一个C语言库，用于实现DNS解析和异步DNS请求
# libssl-dev: OpenSSL是一个开源的加密库，用于实现SSL和TLS协议
RUN apt-get install -y libc-ares-dev  libssl-dev gcc g++ make gdb

# 可视化相关库
RUN apt-get install -y  \
    libx11-xcb1 \
    libfreetype6 \
    libdbus-1-3 \
    libfontconfig1 \
    libxkbcommon0   \
    libxkbcommon-x11-0

# 安装protobuf
COPY install/protobuf /tmp/install/protobuf
RUN /tmp/install/protobuf/install_protobuf.sh

# 安装abseil
COPY install/abseil /tmp/install/abseil
RUN /tmp/install/abseil/install_abseil.sh

# 安装grpc
COPY install/grpc /tmp/install/grpc
RUN /tmp/install/grpc/install_grpc.sh
