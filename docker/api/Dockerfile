FROM node:14.16-alpine

WORKDIR /src

COPY . .

RUN yarn global add nodemon

RUN yarn install

CMD ["npm", "run", "start"]
