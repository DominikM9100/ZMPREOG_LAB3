FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY main_z3_bridge.cpp /app/main_z3_bridge.cpp

WORKDIR /app

RUN g++ -std=c++17 main_z3_bridge.cpp -o bridge

CMD ["./bridge"]