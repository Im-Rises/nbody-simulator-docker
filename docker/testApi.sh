#!/bin/bash

curl -X POST -H "Content-Type: application/json" -d '{"particules": [{"index": 1, "x": 1}, {"index":2, "x": 2}]}' http://localhost:8080/api
echo -e "\n\n"
curl http://localhost:8080/all/present
echo -e "\n\n"
curl http://localhost:8080/all/future
echo -e "\n"