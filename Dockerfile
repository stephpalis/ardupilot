FROM ubuntu:16.04
WORKDIR /ardupilot

RUN useradd -U -d /ardupilot ardupilot
RUN usermod -G users,sudo ardupilot

RUN echo ardupilot:password | chpasswd

RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install --no-install-recommends -y \
    lsb-release \
    sudo \
    software-properties-common \
    python-software-properties && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ENV USER=ardupilot
ADD . /ardupilot
RUN chown -R ardupilot:ardupilot /ardupilot
RUN /ardupilot/Tools/environment_install/install-prereqs-ubuntu.sh -y
RUN apt-get install gcc-arm-none-eabi -y
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

USER ardupilot
ENV CCACHE_MAXSIZE=1G
ENV PATH=/usr/lib/ccache:/ardupilot/Tools:${PATH}