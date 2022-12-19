# Kegerator

Figured I'd start to learn CPP inspired by AK building SerenityOS on youtube.

We have a kegerator at work that we'd like to play interesting sound events when somebody pours a beer.

This project will run on a RaspberryPI w/ a touchscreen and allow people to select random audio clips that we have on
memory, and also will respond to button presses in the GPIO input to trigger specific or random clips.

## Structure:

- /gpio
    - Code for interacting with GPIO, including a fake one that gets triggered by writing a pin name to a socket in /tmp
    - Supports libgpiod (ish?)
- /qemu
    - QEMU definitions for possible target hardware that could run this stuff, need to setup a way to build into
      these emulators now
    - pi3 configuration has pi/raspberry user/pass combo
    - You need mtools and 7zip CLI
- /player
    - Code for playing the audio tracks
- /ui

    - Guess?

- Dockerfile.buildroot
    - Creates an alpine docker image that CLion will use to build the linux version of kegerator.js

## Requirements:

- glog
    - (should we use this since we already dependd on QT?)

Assets are licensed from Noun Project.
