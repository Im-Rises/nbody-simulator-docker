FROM node:14.16-alpine

RUN yarn global add nodemon
WORKDIR /src
ADD package*.json ./

COPY . .

RUN chmod +x ./setup.sh

ENTRYPOINT ["./setup.sh"]