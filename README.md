# POSIX C SOCKET CHAT APP

<p align="center">
    <img src="misc/saturn_app_input.gif" width="600">
</p>

## HIGH-LEVEL ARCHITECTURE

- version 1 (naive client per thread)
<p align="center">
    <img src="misc/architecture.jpg" width="600">
</p>

- version 2 (polling blocking functions wiht epoll and nonblocking sockets)

## DEPENDENCIES
### CLIENT
- SDL2 (windowing & rendering)

## PLATFORM
- Both Server and Client are built and tested on Linux 
- Uses POSIX threads
- Uses POSIX sockets 

## CLIENT
- SDL2 Window
- C-Posix-Sockets
- Posix-pthreads

## SERVER
- C-Posix-Sockets
- Posix-pthreads
- Hosted on a VPS 

## SOURCES
- [Beej's Guide To Posix Sockets](https://beej.us/guide/bgnet/html/)
