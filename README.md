# RingBuffer

[![tests](https://github.com/ximtech/RingBuffer/actions/workflows/cmake-ci.yml/badge.svg)](https://github.com/ximtech/RingBuffer/actions/workflows/cmake-ci.yml)
[![codecov](https://codecov.io/gh/ximtech/RingBuffer/branch/main/graph/badge.svg?token=OQSZTRV1I4)](https://codecov.io/gh/ximtech/RingBuffer)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b4678f8151b841018c23254b415d08ad)](https://www.codacy.com/gh/ximtech/RingBuffer/dashboard)

**STM32** lightweight implementation of Ring buffer.\
Simple data structure that implements the FIFO (First-In-First-Out) ordering. 
This simply means that the first item added to your queue is the first one out.\
More info about, see [wiki](https://en.wikipedia.org/wiki/Circular_buffer)

### Applications
- SPI buffering data stream
- Scheduling pool
- Event pool

### Features
- Specifically designed for embedded applications
- Single on init memory allocation, no memory leaks
- Simple implementation
- Constant time operations O1
- Fast array cleanup

### Trade-offs
- No data structure enlargement after initialization

### Add as CPM project dependency
How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)
```cmake
CPMAddPackage(
        NAME RingBuffer
        GITHUB_REPOSITORY ximtech/RingBuffer
        GIT_TAG origin/main)

target_link_libraries(${PROJECT_NAME} RingBuffer)
```
```cmake
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
# For Clion STM32 plugin generated Cmake use 
target_link_libraries(${PROJECT_NAME}.elf RingBuffer)
```

### Usage
Example of usage:
```C
RingBufferPointer ringBuffer = getRingBufferInstance(4);
ringBufferAdd(ringBuffer, 1);
ringBufferAdd(ringBuffer, 2);
ringBufferAdd(ringBuffer, 3);

printf("Size: %d\n", getRingBufferSize(ringBuffer)); // 3
printf("Is not full: %s\n", isRingBufferNotFull(ringBuffer) ? "Yes" : "No"); // Yes
printf("Is empty: %s\n", isRingBufferEmpty(ringBuffer) ? "Yes" : "No"); // No
printf("Is not empty: %s\n", isRingBufferNotEmpty(ringBuffer) ? "Yes" : "No"); // Yes

while (isRingBufferNotEmpty(ringBuffer)) {
    printf("%d ", ringBufferGet(ringBuffer)); // 1 2 3
}
printf("\n");

printf("Is empty: %s\n", isRingBufferEmpty(ringBuffer) ? "Yes" : "No"); // Yes

// add more elements than buffer size
ringBufferAdd(ringBuffer, 1);
ringBufferAdd(ringBuffer, 2);
ringBufferAdd(ringBuffer, 3);
ringBufferAdd(ringBuffer, 4);
ringBufferAdd(ringBuffer, 5);

while (isRingBufferNotEmpty(ringBuffer)) {
    printf("%d ", ringBufferGet(ringBuffer)); // 2 3 4 5
}

ringBufferDelete(ringBuffer);
```
