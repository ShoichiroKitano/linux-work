FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y vim gcc git man
RUN apt-get install -y nasm
RUN apt-get install -y freebsd-buildutils
WORKDIR /work_home

CMD ["bash"]
