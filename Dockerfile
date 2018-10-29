FROM gcc:latest
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -o myapp main.cpp
CMD ["./myapp","127.0.0.1"]


