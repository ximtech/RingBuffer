#include "RingBuffer.h"

struct RingBuffer {
    uint32_t head;
    uint32_t tail;
    uint32_t maxSize;
    RingBufferDataType *dataBuffer;
    bool isFull;
};

static void advanceBufferPointer(RingBufferPointer ringBuffer);
static void retreatBufferPointer(RingBufferPointer ringBuffer);


RingBufferPointer getRingBufferInstance(uint32_t bufferSize) {
    if (bufferSize < 1) return NULL;

    RingBufferPointer instance = malloc(sizeof(struct RingBuffer));
    if (instance != NULL) {
        RingBufferDataType *buffer = malloc(sizeof(RingBufferDataType) * bufferSize);
        if (buffer == NULL) return NULL;
        instance->dataBuffer = buffer;
        instance->maxSize = bufferSize;
        memset(instance->dataBuffer, 0, instance->maxSize);
        ringBufferReset(instance);
    }
    return instance;
}

void ringBufferReset(RingBufferPointer ringBuffer) {
    if (ringBuffer != NULL) {
        ringBuffer->head = 0;
        ringBuffer->tail = 0;
        ringBuffer->isFull = false;
    }
}

void ringBufferDelete(RingBufferPointer ringBuffer) {
    if (ringBuffer != NULL) {
        free(ringBuffer->dataBuffer);
        free(ringBuffer);
    }
}

bool isRingBufferFull(RingBufferPointer ringBuffer) {
    return (ringBuffer != NULL) ? ringBuffer->isFull : true;
}

bool isRingBufferNotFull(RingBufferPointer ringBuffer) {
    return !isRingBufferFull(ringBuffer);
}

bool isRingBufferEmpty(RingBufferPointer ringBuffer) {
    if (ringBuffer != NULL) {
        return !ringBuffer->isFull && (ringBuffer->head == ringBuffer->tail);
    }
    return true;
}

bool isRingBufferNotEmpty(RingBufferPointer ringBuffer) {
    return !isRingBufferEmpty(ringBuffer);
}

uint32_t getRingBufferSize(RingBufferPointer ringBuffer) {
    if (ringBuffer != NULL) {
        uint32_t bufferSize = ringBuffer->maxSize;

        if (!ringBuffer->isFull) {
            if (ringBuffer->head >= ringBuffer->tail) {
                bufferSize = (ringBuffer->head) - (ringBuffer->tail);
            } else {
                bufferSize = (ringBuffer->maxSize + ringBuffer->head - ringBuffer->tail);
            }
        }
        return bufferSize;
    }
    return 0;
}

void ringBufferAdd(RingBufferPointer ringBuffer, RingBufferDataType value) {
    if (ringBuffer != NULL && ringBuffer->dataBuffer != NULL) {
        ringBuffer->dataBuffer[ringBuffer->head] = value;
        advanceBufferPointer(ringBuffer);
    }
}

RingBufferDataType ringBufferGet(RingBufferPointer ringBuffer) {
    if (ringBuffer != NULL && ringBuffer->dataBuffer != NULL) {
        if (isRingBufferNotEmpty(ringBuffer)) {
            RingBufferDataType data = ringBuffer->dataBuffer[ringBuffer->tail];
            retreatBufferPointer(ringBuffer);
            return data;
        }
        return (RingBufferDataType) 0;
    }
    return (RingBufferDataType) 0;
}

static void advanceBufferPointer(RingBufferPointer ringBuffer) {
    if (ringBuffer->isFull) {
        ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->maxSize;
    }
    ringBuffer->head = (ringBuffer->head + 1) % ringBuffer->maxSize;
    ringBuffer->isFull = (ringBuffer->head == ringBuffer->tail);
}

static void retreatBufferPointer(RingBufferPointer ringBuffer) {
    ringBuffer->isFull = false;
    ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->maxSize;
}