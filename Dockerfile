FROM debian:stable
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y && apt-get install -y --no-install-recommends apt-utils

RUN apt-get install -y g++
RUN apt-get install -y wget
RUN apt-get install -y build-essential autoconf automake libtool pkg-config git

RUN wget https://raw.githubusercontent.com/libbitcoin/libbitcoin-explorer/version3/install.sh
RUN chmod +x install.sh
RUN ./install.sh --build-boost --build-zmq --disable-shared

ENTRYPOINT ["bx"]
