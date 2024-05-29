FROM pruizca/42img:latest
RUN yes | unminimize
RUN apt install -y man-db
RUN apt install -y gcc-multilib
CMD ping google.com
