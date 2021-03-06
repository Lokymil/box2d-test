# Box2D Tests

This repository aim to be a sandbox to try things with Box2d physic engine.

## Installation

You need to install:

- g++
- Box2D
- SDL2
- OpenGL

## Run

### From a single file

To run a test from a single file, use the following command:

```
make single SRCDIR=[source folder where to find .cpp file] MAIN=[file name without .cpp extension]
```

For instance:

```
make single SRCDIR=dirty MAIN=1.inConsole
```

### From a set of files

To run a test with multiple files, use the collowing command:

```
make SRCDIR=[source folder where to find .cpp & .h files]
```

For instance:

```
make SRCDIR=jump
```

## Contributing

To add a new scenario, copy `base` folder; rename it with your scenario (eg.: `jump`, `shooting`) and rename window name un `graphics/Screen.cpp` accordingly.  
Then you can do whatever you want as long as you follow `base` architecture.

In case a technical implementation can improve other scenaris, you may add it to `base` scenario in order to have it in future implementation.
