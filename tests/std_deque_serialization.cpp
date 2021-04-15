#include <deque>
#include <gtest/gtest.h>
#include <random>

#include "kt-serial/types/std/deque.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

const std::size_t maxSize = 100;

TEST(StdDequeSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int_fast8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int_fast16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int_fast32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, int_fast64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, intmax_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, intptr_t, maxSize);
}

TEST(StdDequeSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint_fast8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint_fast16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint_fast32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uint_fast64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uintmax_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, uintptr_t, maxSize);
}

TEST(StdDequeSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, char, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, wchar_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, char16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, char32_t, maxSize);
}

TEST(StdDequeSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, float, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, double, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, long double, maxSize);
}

TEST(StdDequeSerialization, Bool) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::deque, bool, maxSize);
    TestFunctions::binaryIOSerialization(
        std::deque<bool>({1, 0, 0, 0, 1, 1, 0, 1}));
}

GENERATE_STRUCT(SimpleStruct, int_least32_t, char32_t, bool, bool, long double)

GENERATE_STRUCT(DequeStruct, std::deque<SimpleStruct>, std::deque<bool>,
                std::deque<std::deque<bool>>, bool, bool, wchar_t)

GENERATE_STRUCT(CharStruct, char, wchar_t, char16_t, char32_t, char)

TEST(StdDequeSerialization, UserDefinedStructs) {
    std::mt19937 gen;
    {
        std::deque<SimpleStruct> dss;
        TestFunctions::randomValue(dss, gen);
        TestFunctions::binaryIOSerialization(dss);
    }
    {
        std::deque<std::deque<SimpleStruct>> ddss;
        TestFunctions::randomValue(ddss, gen);
        TestFunctions::binaryIOSerialization(ddss);
    }
    {
        DequeStruct ds;
        ds.fillRandom(gen);
        TestFunctions::binaryIOSerialization(ds);
    }
    {
        std::deque<DequeStruct> dds;
        TestFunctions::randomValue(dds, gen);
        TestFunctions::binaryIOSerialization(dds);
    }
    {
        std::deque<CharStruct> dcs;
        TestFunctions::randomValue(dcs, gen);
        TestFunctions::binaryIOSerialization(dcs);
    }
}