#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


typedef struct RingBuffer *RingBufferPointer;
typedef int RingBufferDataType;

RingBufferPointer getRingBufferInstance(uint32_t bufferSize);   // get initialized byteBuffer, provide buffer type and capacity

void ringBufferDelete(RingBufferPointer ringBuffer);                      // destroying the container
void ringBufferReset(RingBufferPointer ringBuffer);                       // set pointers to zero, and the data count, causing the buffer to be "empty"
bool isRingBufferFull(RingBufferPointer ringBuffer);                      // check that buffer is full
bool isRingBufferNotFull(RingBufferPointer ringBuffer);
bool isRingBufferEmpty(RingBufferPointer ringBuffer);                     // buffer empty if no data received
bool isRingBufferNotEmpty(RingBufferPointer ringBuffer);
uint32_t getRingBufferSize(RingBufferPointer ringBuffer);                 // return elements count in buffer

void ringBufferAdd(RingBufferPointer ringBuffer, RingBufferDataType value);       // add item to buffer
RingBufferDataType ringBufferGet(RingBufferPointer ringBuffer);      // get data from buffer, return item if buffer have value and NULL otherwise