FROM debian:bookworm-slim

# Build arguments for user configuration
ARG USERNAME
ARG USER_UID
ARG USER_GID
ARG USER_HOME

# In the m4 docs is an implementation of a stack that is used by
# the
RUN \
    apt-get update && \
    echo 'path-include /usr/share/doc/m4/*' >>/etc/dpkg/dpkg.cfg.d/docker && \
    apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        indent \
        inotify-tools \
        lib32gcc-12-dev \
        lib32readline-dev \
        libc6-dev \
        libc6-dev-i386 \
        libreadline-dev \
        m4 \
        sudo && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    rm -rf /var/cache/apt/* && \
    rm -rf /var/cache/debconf/*.dat-old && \
    rm -rf /var/lib/dpkg/*-old && \
    rm -rf /usr/share/man/* && \
    rm -rf /usr/share/locale/*

RUN ln -s /usr/include/x86_64-linux-gnu/asm /usr/include/asm

# Set default values in case they're not provided

ENV USERNAME=${USERNAME:-user}
ENV USER_UID=${USER_UID:-1000}
ENV USER_GID=${USER_GID:-1000}
ENV USER_HOME=${USER_HOME:-/home/$USERNAME}

# Create user and group with specified IDs and
# set up sudo access without password.

RUN groupadd --gid $USER_GID $USERNAME && \
    useradd --uid $USER_UID --gid $USER_GID -m \
        --home-dir $USER_HOME \
        --shell /bin/bash \
        --groups sudo \
        $USERNAME && \
    echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN echo "PS1='(\u@\h:\w)\$ '" >> $USER_HOME/.bashrc

# Switch to the new user
USER $USERNAME
WORKDIR $USER_HOME

# Set default command
CMD ["/bin/bash"]
