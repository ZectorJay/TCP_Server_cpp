FROM debian:latest

EXPOSE 22 1100

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install build-essential procps curl file git -y
RUN apt-get install manpages-dev -y
RUN apt-get install vim -y
RUN apt install ssh -y
RUN apt install mariadb-server -y
RUN apt-get install sysbench -y

RUN echo 'root:1234' | chpasswd
COPY sshd_config /etc/ssh/

COPY srcs/Client.cpp /home/
COPY srcs/Server.cpp /home/
COPY srcs/header.hpp /home/

COPY launch.sh /
RUN chmod 777 /launch.sh

WORKDIR /home/

RUN c++ Server.cpp -o server
RUN c++ Client.cpp -o client

CMD ["/launch.sh"]