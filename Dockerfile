FROM ubuntu:16.04

RUN apt-get update && apt-get -y install nasm vim binutils
RUN mkdir /nasm

CMD ["bash"]
