#!/bin/bash

docker-compose down
docker-compose up -d --build
docker logs -f nbody-simulator-cloud_api_1