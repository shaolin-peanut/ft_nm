FROM pruizca/42img:latest
RUN yes | unminimize
RUN apt install -y man-db
CMD ping google.com
