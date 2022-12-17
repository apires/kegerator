FROM arm64v8/alpine:3.16.3 as builder-stage

RUN apk add alpine-sdk qt6-qtmultimedia-dev musl musl-utils libunwind-dev glog-dev samurai cmake libgpiod-dev
RUN apk add gdb

#WORKDIR /build
#COPY . /usr/src/kegerator.qt
#RUN cmake -GNinja /usr/src/kegerator.qt
#RUN ninja -j4

#FROM scratch AS export-stage
#COPY --from=builder-stage /build/kegerator_qt /
#COPY --from=builder-stage /build/gpio/KegeratorGPIOTest /

#FROM arm64v8/alpine:3.16.3

