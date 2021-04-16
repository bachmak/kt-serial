#include <gtest/gtest.h>
#include <list>
#include <random>

#include "kt-serial/types/std/list.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

const std::size_t maxSize = 100;

TEST(StdListSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_INT_TYPES(std::list, maxSize);
}

TEST(StdListSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_UINT_TYPES(std::list, maxSize);
}

TEST(StdListSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_CHAR_TYPES(std::list, maxSize);
}

TEST(StdListSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_FLOAT_TYPES(std::list, maxSize);
}

TEST(StdListSerialization, Bool) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::list, bool, maxSize);
    TestFunctions::binaryIOSerialization(std::list<bool>({0, 1, 0, 1, 1, 0}));
}

GENERATE_STRUCT(SimpleStruct, bool, char32_t, char, long double)

GENERATE_STRUCT(ListStruct, std::list<uint_least32_t>,
                std::list<std::list<double>>, std::list<SimpleStruct>)

GENERATE_STRUCT(AnotherStruct, bool, bool, float, int16_t,
                std::list<ListStruct>, std::list<std::list<bool>>)

TEST(StdListSerialization, UserDefinedStructs) {
    std::mt19937 gen;
    {
        std::list<SimpleStruct> lss;
        TestFunctions::binaryIOSerialization(lss);
        TestFunctions::randomize(lss, gen);
    }
    {
        ListStruct ls;
        TestFunctions::binaryIOSerialization(ls);
        ls.randomize(gen);
        TestFunctions::binaryIOSerialization(ls);
    }
    {
        AnotherStruct as;
        TestFunctions::binaryIOSerialization(as);
        as.randomize(gen);
        TestFunctions::binaryIOSerialization(as);
    }
}
