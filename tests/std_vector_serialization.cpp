#include <gtest/gtest.h>
#include <random>
#include <vector>

#include "kt-serial/types/std/vector.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

const std::size_t maxSize = 100;

TEST(StdVectorSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_INT_TYPES(std::vector, maxSize);
}

TEST(StdVectorSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_UINT_TYPES(std::vector, maxSize);
}

TEST(StdVectorSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_CHAR_TYPES(std::vector, maxSize);
}

TEST(StdVectorSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_FLOAT_TYPES(std::vector, maxSize);
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
        TestFunctions::binaryIOSerialization(bs);
        bs.randomize(gen);
        TestFunctions::binaryIOSerialization(bs);
    }

    {
        SimpleStruct ss;
        ss.randomize(gen);
        TestFunctions::binaryIOSerialization(ss);
    }

    {
        VectorStruct vs;
        TestFunctions::binaryIOSerialization(vs);
        vs.randomize(gen);
        TestFunctions::binaryIOSerialization(vs);
    }

    {
        std::vector<VectorStruct> vec;
        TestFunctions::binaryIOSerialization(vec);
        TestFunctions::randomize(vec, gen);
        TestFunctions::binaryIOSerialization(vec);
    }
}