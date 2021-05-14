#include <gtest/gtest.h>
#include <random>
#include <unordered_set>

#include "kt-serial/types/std/unordered_set.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(StdUnorderedSetSerialization, ArithmeticTypes) {
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<std::unordered_set<int>>();
    createInstanceAndTestIOSerialization<std::unordered_set<double>>();
    createInstanceAndTestIOSerialization<std::unordered_set<bool>>();

    createInstanceAndTestIOSerialization<std::unordered_multiset<char32_t>>();
    createInstanceAndTestIOSerialization<
        std::unordered_multiset<uint_fast16_t>>();
    createInstanceAndTestIOSerialization<std::unordered_multiset<bool>>();
}

GENERATE_STRUCT(SimpleStruct, int, char32_t, bool, double, long double)

GENERATE_STRUCT(NestedStruct, std::unordered_set<SimpleStruct>,
                std::unordered_multiset<SimpleStruct>)

GENERATE_STRUCT(UnorderedSetStruct, std::unordered_multiset<int>,
                std::unordered_multiset<bool>)

GENERATE_STRUCT(AnotherStruct, std::unordered_set<double>,
                std::unordered_set<char32_t>)

TEST(StdUnorderedSetSerialization, UserDefinedStructs) {
    TestFunctions::maxSize = 10000;
    createInstanceAndTestIOSerialization<std::unordered_set<SimpleStruct>>();
    createInstanceAndTestIOSerialization<
        std::unordered_multiset<SimpleStruct>>();

    createInstanceAndTestIOSerialization<NestedStruct>();
    createInstanceAndTestIOSerialization<UnorderedSetStruct>();
    createInstanceAndTestIOSerialization<AnotherStruct>();
}
