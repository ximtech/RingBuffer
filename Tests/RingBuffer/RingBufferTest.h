#pragma once

#include "BaseTestTemplate.h"
#include "RingBuffer.h"

#define RING_BUFFER_INITIAL_CAPACITY 10

static void *ringBufferSetup(const MunitParameter params[], void *userData) {
    RingBuffer ringBuffer = getRingBufferInstance(RING_BUFFER_INITIAL_CAPACITY);
    assert_not_null(ringBuffer);
    return ringBuffer;
}

static MunitResult testRingBufferAddElements(const MunitParameter params[], void *ringBuffer) {
    (RingBuffer) ringBuffer;

    for (uint8_t i = 0; i < RING_BUFFER_INITIAL_CAPACITY; i++) {
        ringBufferAdd(ringBuffer, i);
        assert_int(getRingBufferSize(ringBuffer), ==, i + 1);
    }
    assert_true(isRingBufferFull(ringBuffer));
    assert_true(isRingBufferNotEmpty(ringBuffer));
    assert_false(isRingBufferEmpty(ringBuffer));

    ringBufferAdd(ringBuffer, 23);  // add more than buffer capacity
    assert_true(isRingBufferFull(ringBuffer));
    assert_int(getRingBufferSize(ringBuffer), ==, RING_BUFFER_INITIAL_CAPACITY);
    for (int i = 0; i < RING_BUFFER_INITIAL_CAPACITY - 1; i++) {
        ringBufferGet(ringBuffer);  // scroll till the end
    }
    assert_int(ringBufferGet(ringBuffer), ==, 23);

    return MUNIT_OK;
}

static MunitResult testRingBufferGetElements(const MunitParameter params[], void *ringBuffer) {
    (RingBuffer) ringBuffer;
    for (uint8_t i = 0; i < RING_BUFFER_INITIAL_CAPACITY; i++) {
        ringBufferAdd(ringBuffer, i);
    }
    assert_true(isRingBufferFull(ringBuffer));

    int counter = 0;
    while (isRingBufferNotEmpty(ringBuffer)) {
        assert_uint8(ringBufferGet(ringBuffer), ==, counter);
        assert_int(getRingBufferSize(ringBuffer), ==, RING_BUFFER_INITIAL_CAPACITY - counter - 1);
        counter++;
    }
    assert_true(isRingBufferEmpty(ringBuffer));

    assert_int(ringBufferGet(NULL), ==, 0);     // NULL buffer
    assert_int(ringBufferGet(ringBuffer), ==, 0);   // empty buffer
    assert_int(getRingBufferSize(NULL), ==, 0);   // NULL buffer size
    assert_true(isRingBufferEmpty(NULL));
    return MUNIT_OK;
}

static MunitResult testRingBufferReset(const MunitParameter params[], void *ringBuffer) {
    (RingBuffer) ringBuffer;
    ringBufferAdd(ringBuffer, 1);
    ringBufferAdd(ringBuffer, 2);
    ringBufferAdd(ringBuffer, 3);
    assert_int(getRingBufferSize(ringBuffer), ==, 3);

    ringBufferReset(ringBuffer);
    assert_true(isRingBufferEmpty(ringBuffer));
    assert_int(getRingBufferSize(ringBuffer), ==, 0);

    return MUNIT_OK;
}

static MunitResult testRingBufferHalfWord(const MunitParameter params[], void *ringBuffer) {
    (RingBuffer) ringBuffer;

    for (uint8_t i = 0; i < RING_BUFFER_INITIAL_CAPACITY; i++) {
        ringBufferAdd(ringBuffer, 1000 + i);
        assert_int(getRingBufferSize(ringBuffer), ==, i + 1);
    }
    assert_true(isRingBufferFull(ringBuffer));

    int valueCounter = 1000;
    int sizeCounter = 0;
    while (isRingBufferNotEmpty(ringBuffer)) {
        assert_int(ringBufferGet(ringBuffer), ==, valueCounter);
        assert_int(getRingBufferSize(ringBuffer), ==, RING_BUFFER_INITIAL_CAPACITY - sizeCounter - 1);
        valueCounter++;
        sizeCounter++;
    }
    assert_true(isRingBufferEmpty(ringBuffer));
    return MUNIT_OK;
}

static MunitResult testRingBufferNotFull(const MunitParameter params[], void *ringBuffer) {
    (RingBuffer) ringBuffer;
    ringBufferAdd(ringBuffer, 1);
    ringBufferAdd(ringBuffer, 2);
    ringBufferAdd(ringBuffer, 3);
    ringBufferAdd(ringBuffer, 4);
    assert_true(isRingBufferNotFull(ringBuffer));

    uint32_t freeSpace = (RING_BUFFER_INITIAL_CAPACITY - getRingBufferSize(ringBuffer));
    for (int i = 0; i < freeSpace; i++) {
        ringBufferAdd(ringBuffer, i);
    }
    assert_false(isRingBufferNotFull(ringBuffer));
    return MUNIT_OK;
}

static void ringBufferTearDown(void *ringBuffer) {
    (RingBuffer) ringBuffer;
    ringBufferDelete(ringBuffer);
    ringBuffer = NULL;
    munit_assert_ptr_null(ringBuffer);
}

static MunitTest ringBufferTests[] = {
        {.name =  "Test ringBufferAddByte() - should correctly add byte to buffer", .test = testRingBufferAddElements, .setup = ringBufferSetup, .tear_down = ringBufferTearDown},
        {.name =  "Test ringBufferGetByte() - should correctly get byte from buffer", .test = testRingBufferGetElements, .setup = ringBufferSetup, .tear_down = ringBufferTearDown},
        {.name =  "Test ringBufferReset() - should clean ring buffer", .test = testRingBufferReset, .setup = ringBufferSetup, .tear_down = ringBufferTearDown},
        {.name =  "Test 16 bit buffer - should correctly add and get half word data", .test = testRingBufferHalfWord, .setup = ringBufferSetup, .tear_down = ringBufferTearDown},
        {.name =  "Test isRingBufferNotFull() - should correctly check buffer capacity", .test = testRingBufferNotFull, .setup = ringBufferSetup, .tear_down = ringBufferTearDown},
        END_OF_TESTS
};

static const MunitSuite ringBufferTestSuite = {
        .prefix = "Ring Buffer: ",
        .tests = ringBufferTests,
        .suites = NULL,
        .iterations = 1,
        .options = MUNIT_SUITE_OPTION_NONE
};