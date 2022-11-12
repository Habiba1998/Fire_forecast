FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive # ignore user input required
# Install required build dependencies
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install g++ cmake git
COPY . .
WORKDIR .
# Run cmake configure & build process
RUN mkdir ./build
RUN cmake -B /build -S . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /build
EXPOSE 8080
# Launch built application
CMD ["./build/server_task"]