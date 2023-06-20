#!/bin/bash

start_time=$(date +%s)  # Enregistre le temps de départ en secondes depuis l'époque Unix

docker container stop $(docker container ls -q)
docker-compose down
docker-compose up -d #--build
docker logs -f nbody-simulator-docker_opengl_1

end_time=$(date +%s)    # Enregistre le temps d'arrêt en secondes depuis l'époque Unix

duration=$((end_time - start_time))  # Calcule la durée en secondes

echo "Le chronomètre a fonctionné pendant $duration secondes."
