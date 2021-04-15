#include <gtest/gtest.h>
#include <random>
#include <type_traits>
#include <vector>

#include "kt-serial/types/std/vector.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

const std::size_t maxSize = 100;

TEST(StdVectorSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int_fast8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int_fast16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int_fast32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, int_fast64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, intmax_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, intptr_t, maxSize);
}

TEST(StdVectorSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint_fast8_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint_fast16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint_fast32_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uint_fast64_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uintmax_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, uintptr_t, maxSize);
}

TEST(StdVectorSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, char, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, wchar_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, char16_t, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, char32_t, maxSize);
}

TEST(StdVectorSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, float, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, double, maxSize);
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, long double, maxSize);
}

TEST(StdVectorSerialization, Bool) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::vector, bool, maxSize);
    TestFunctions::binaryIOSerialization(
        std::vector<bool>({1, 1, 1, 0, 0, 1, 0, 0}));
    TestFunctions::binaryIOSerialization(
        std::vector<bool>({0, 0, 1, 0, 0, 0, 1, 1}));
}

GENERATE_STRUCT(BoolStruct, bool, bool, bool, bool, bool, bool)

GENERATE_STRUCT(SimpleStruct, int, unsigned, char, float, double, bool)

GENERATE_STRUCT(VectorStruct, std::vector<int>, std::vector<uint>,
                std::vector<SimpleStruct>, std::vector<bool>, char, double)

TEST(StdVectorSerialization, UserDefinedStructs) {
    std::mt19937 gen;
    {
        BoolStruct bs;
        bs.fillRandom(gen);
        TestFunctions::binaryIOSerialization(bs);
    }

    {
        SimpleStruct ss;
        ss.fillRandom(gen);
        TestFunctions::binaryIOSerialization(ss);
    }

    {
        VectorStruct vs;
        vs.fillRandom(gen);
        TestFunctions::binaryIOSerialization(vs);
    }

    {
        std::vector<VectorStruct> vec;
        TestFunctions::randomValue(vec, gen);
        TestFunctions::binaryIOSerialization(vec);
    }
}