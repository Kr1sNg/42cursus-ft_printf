# 1. Base image
FROM debian:bookworm

# 2. Install build tools
RUN apt-get update && apt-get install -y \
    build-essential \
	vim \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# 3. Set working directory inside container
WORKDIR /app

# 4. Copy project files into container
COPY . .


## to build image
# docker build -t c_project .

## To get inside the bash of Docker
# docker run -it --rm c_project:latest bash

## Volume mounts help us do not need to rebuild everytime
# docker run -it --rm -v $(pwd):/app c_project:latest bash