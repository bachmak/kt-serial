#include <gtest/gtest.h>
#include <random>
#include <vector>

#include "kt-serial/types/std/vector.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::maxSize;

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

GENERATE_STRUCT(VectorStruct, std::vector<int>, std::vector<unsigned>,
                std::vector<SimpleStruct>, std::vector<bool>, char, double)

TEST(StdVectorSerialization, UserDefinedStructs) {
    using TestFunctions::createInstanceAndTestIOSerialization;

    createInstanceAndTestIOSerialization<std::vector<BoolStruct>>();
    createInstanceAndTestIOSerialization<std::vector<SimpleStruct>>();
    createInstanceAndTestIOSerialization<VectorStruct>();
    createInstanceAndTestIOSerialization<std::vector<VectorStruct>>();
}