#include <deque>
#include <gtest/gtest.h>
#include <random>

#include "kt-serial/types/std/deque.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::maxSize;

TEST(StdDequeSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_INT_TYPES(std::deque, maxSize);
}

TEST(StdDequeSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_UINT_TYPES(std::deque, maxSize);
}

TEST(StdDequeSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_CHAR_TYPES(std::deque, maxSize);
}

TEST(StdDequeSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_FLOAT_TYPES(std::deque, maxSize);
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
    using TestFunctions::createInstanceAndTestIOSerialization;

    std::mt19937 gen;

    createInstanceAndTestIOSerialization<std::deque<SimpleStruct>>(gen);
    createInstanceAndTestIOSerialization<std::deque<std::deque<SimpleStruct>>>(
        gen);
    createInstanceAndTestIOSerialization<DequeStruct>(gen);
    createInstanceAndTestIOSerialization<std::deque<DequeStruct>>(gen);
    createInstanceAndTestIOSerialization<std::deque<CharStruct>>(gen);
}