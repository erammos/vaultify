FROM debian:bookworm

# Install dependencies
RUN apt-get update; \
    apt-get install -y \
        git gnupg2 wget ca-certificates apt-transport-https \
        autoconf automake cmake dpkg-dev file make patch libc6-dev meson ruby pkg-config \
        libssl-dev libsqlite3-dev libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev \ 
        libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev

# Install LLVM
RUN echo "deb https://apt.llvm.org/bookworm llvm-toolchain-bookworm-18 main" \
        > /etc/apt/sources.list.d/llvm.list && \
    wget -qO /etc/apt/trusted.gpg.d/llvm.asc \
        https://apt.llvm.org/llvm-snapshot.gpg.key && \
    apt-get -qq update && \
    apt-get install -qqy -t llvm-toolchain-bookworm-18 clang-18 clang-tidy-18 clang-format-18 lld-18 libc++-18-dev libc++abi-18-dev && \
    for f in /usr/lib/llvm-*/bin/*; do ln -sf "$f" /usr/bin; done && \
    ln -sf clang /usr/bin/cc && \
    ln -sf clang /usr/bin/c89 && \
    ln -sf clang /usr/bin/c99 && \
    ln -sf clang++ /usr/bin/c++ && \
    ln -sf clang++ /usr/bin/g++ && \
    rm -rf /var/lib/apt/lists/*

