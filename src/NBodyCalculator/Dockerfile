FROM alpine:3.12

RUN apk update
RUN apk upgrade
RUN apk add cmake
RUN apk add make
RUN apk add gcc
RUN apk add g++
RUN apk add curl-dev
RUN apk add curl
RUN apk add glm-dev

WORKDIR /nbody

COPY . .

RUN chmod +x ./setup.sh

ENV NB_PARTICULES=10

CMD [ "0", "http://api:9000" ]

ENTRYPOINT ["./setup.sh"]