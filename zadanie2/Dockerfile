FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY main_z2_decorator.cpp /app/main_z2_decorator.cpp

WORKDIR /app

RUN g++ -std=c++17 main_z2_decorator.cpp -o decorator

CMD ["./decorator"]