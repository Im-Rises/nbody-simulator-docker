FROM node:14.16-alpine

RUN yarn global add nodemon
WORKDIR /src
ADD package*.json ./
RUN yarn install --ignore-platform
RUN ls ./node_modules/express

COPY . .

CMD ["node", "index.js"]