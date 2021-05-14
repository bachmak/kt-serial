#include <forward_list>
#include <gtest/gtest.h>
#include <random>

#include "kt-serial/types/std/forward_list.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::maxSize;

TEST(StdForwardListSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_INT_TYPES(std::forward_list, maxSize);
}

TEST(StdForwardListSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_UINT_TYPES(std::forward_list, maxSize);
}

TEST(StdForwardListSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_CHAR_TYPES(std::forward_list, maxSize);
}

TEST(StdForwardListSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_FLOAT_TYPES(std::forward_list, maxSize);
}

TEST(StdForwardListSerialization, Bool) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(std::forward_list, bool, maxSize);
    TestFunctions::binaryIOSerialization(
        std::forward_list<bool>({0, 1, 0, 1, 1, 0}));
}

GENERATE_STRUCT(SimpleStruct, char16_t, bool, long long int, long double, bool)

GENERATE_STRUCT(FwdListStruct, std::forward_list<bool>,
                std::forward_list<SimpleStruct>,
                std::forward_list<std::forward_list<double>>)

GENERATE_STRUCT(AnotherStruct, float, long double, double, float,
                std::forward_list<std::forward_list<bool>>,
                std::forward_list<std::forward_list<SimpleStruct>>)

TEST(StdForwardListSerialization, UserDefinedStructs) {
    using TestFunctions::createInstanceAndTestIOSerialization;

    createInstanceAndTestIOSerialization<std::forward_list<SimpleStruct>>();
    createInstanceAndTestIOSerialization<FwdListStruct>();
    createInstanceAndTestIOSerialization<AnotherStruct>();
}