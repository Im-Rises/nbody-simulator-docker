#!/bin/bash

docker-compose down
docker-compose up -d --build
docker logs -f nbody-simulator-docker_api_1