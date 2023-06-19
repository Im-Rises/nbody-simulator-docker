FROM matimoreyra/opencv

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y mesa-utils
RUN apt-get install -y cmake
RUN apt-get install -y make
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y build-essential
RUN apt-get install -y libglfw3-dev
RUN apt-get install -y libcurl4-openssl-dev
RUN apt-get install -y curl
RUN apt-get install -y xvfb
RUN apt-get install -y libglm-dev

WORKDIR /nbody

COPY . .

ENV NB_PARTICULES=${NB_PARTICULES}
ENV TIME_SIMULATION=${TIME_SIMULATION}

CMD ["bash", "./run-opengl.sh", "${NB_PARTICULES}", "${TIME_SIMULATION}"]
