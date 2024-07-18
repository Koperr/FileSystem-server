FROM ubuntu:latest

WORKDIR /app

COPY . .

COPY libs/libhttpserver /tmp/libhttpserver


RUN chmod +x scripts/*.sh
RUN apt-get update && apt-get install -y \
    build-essential \
    libcurl4-openssl-dev \
    git \
    ####
    autoconf \
    automake \
    libtool \ 
    pkg-config \ 
    ####
    curl \
    cmake \
    nlohmann-json3-dev \
    libmicrohttpd-dev

RUN scripts/installHttpServer.sh

ENV LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"
ENV CXXFLAGS="-I/usr/include"

EXPOSE 8080

CMD ["sh", "-c", "scripts/setupDocker.sh"]

