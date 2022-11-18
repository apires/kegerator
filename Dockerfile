FROM arm64v8/alpine as builder-stage

# RUN apt-get update && apt-get install -y build-essential cmake bash wget --no-install-recommends
# RUN apt-get install -y qt6-base-dev --no-install-recommends
# RUN apt-get install -y qt6-multimedia-dev --no-install-recommends
# RUN apt-get install -y libunwind-dev musl-dev ninja-build musl-tools --no-install-recommends
# RUN apt-get install -y libgoogle-glog-dev vim --no-install-recommends
RUN apk add alpine-sdk qt6-qtmultimedia-dev musl musl-utils libunwind-dev glog-dev samurai
RUN apk add cmake taglib-dev mesa-dev mesa-gles

WORKDIR /build
COPY . /usr/src/kegerator.qt
RUN cmake -GNinja /usr/src/kegerator.qt
RUN ninja -j4

FROM scratch AS export-stage
COPY --from=builder-stage /build/kegerator_qt /

# RUN set -ex;              \
#     cd /build;  \
#     cmake /usrc/src/kegerator.qt; make; make install
