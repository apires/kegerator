FROM arm64v8/alpine as builder-stage

RUN apk add alpine-sdk qt6-qtmultimedia-dev musl musl-utils libunwind-dev glog-dev samurai cmake

WORKDIR /build
COPY . /usr/src/kegerator.qt
RUN cmake -GNinja /usr/src/kegerator.qt
RUN ninja -j4

FROM scratch AS export-stage
COPY --from=builder-stage /build/kegerator_qt /