#!/bin/bash

cd zadanie1
docker build -t zadanie1_adapter .
cd ..

cd zadanie2
docker build -t zadanie2_decorator .
cd ..

cd zadanie3
docker build -t zadanie3_bridge .
cd ..
