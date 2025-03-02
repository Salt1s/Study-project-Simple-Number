FROM ubuntu:latest

RUN apt-get update && apt-get install -y dpkg g++ build essential

COPY simple_num.deb /tmp/simple_num.deb

RUN dpkg -i /tmp/simple_num.deb || apt-get install -f
RUN chmod +x /usr/local/bin/simple_num
ENTRYPOINT ["/usr/local/bin/simple_num"]
CMD ["5"]
