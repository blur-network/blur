FROM ubuntu:18.04

RUN apt update
RUN apt install -y build-essential cmake pkg-config libboost-all-dev libssl-dev libsodium-dev libunwind-dev binutils-dev rapidjson-dev liblzma-dev libexpat1-dev libgtest-dev libreadline-dev git wget curl

ARG FILENAME=aocc-compiler-2.1.0_1_amd64.deb
RUN wget https://www.dropbox.com/sh/xv2jdrs0uc6z2b9/AACAPqZJTjVbLlXhBNRR2N1Ja/${FILENAME}

RUN dpkg -i aocc-compiler-2.1.0_1_amd64.deb && rm -f aocc-compiler-2.1.0_1_amd64.deb

RUN git clone https://github.com/blur-network/blur.git

RUN /bin/bash -c "source /opt/AMD/aocc-compiler-2.1.0/setenv_AOCC.sh" \
&& export CC=/opt/AMD/aocc-compiler-2.1.0/bin/clang \
&& export CXX=/opt/AMD/aocc-compiler-2.1.0/bin/clang++ \
&& cd blur && make -j6 release-static

RUN ls *
