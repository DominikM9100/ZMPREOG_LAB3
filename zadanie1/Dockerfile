FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY main_z1_adapter.cpp /app/main_z1_adapter.cpp

WORKDIR /app

RUN g++ -std=c++17 main_z1_adapter.cpp -o adapter

CMD ["./adapter"]