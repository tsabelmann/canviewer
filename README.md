# canviewer

## What is canviewer?

canviewer is can-bus analysis software. It allows the receiving of can-bus messages and the display in a hierarchical fashion. It uses *.json files to apply conversions to selected can-bus messages have a specific ID.

## Program Requirements

- Debian / Ubuntu Operating System

## Required Software

Building canviewer from source requires the following dependencies:

- Git
- GCC or G++
- CMake
- PkgConfig
- Boost
- GTKmm
- SocketCAN

## Installing Dependencies on Debian / Ubuntu

```
sudo apt-get install build-essential git cmake pkg-config libboost-all-dev libgtkmm-3.0-dev libsocketcan-dev
```

## Building Instructions

### Building canviewer

```
cd toonz
mkdir build
cd build
cmake ..
make
```

### Running canviewer

```
cd build
./canviewer
```

