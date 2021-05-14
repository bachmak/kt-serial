#include <gtest/gtest.h>
#include <random>
#include <set>

#include "kt-serial/types/std/set.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

TEST(StdSetSerialization, ArithmeticTypes) {
    std::set<int> a;
    std::multiset<char32_t> b;
    std::set<double> c;
    std::set<bool> d;
    std::multiset<bool> e;

    TestFunctions::binaryIOSerialization(a, b, c, d, e);
    TestFunctions::randomizeVariadic(a, b, c, d, e);
    TestFunctions::binaryIOSerialization(a, b, c, d, e);
}

GENERATE_STRUCT(SimpleStruct, bool, int_fast64_t, double_t, long double)
GENERATE_STRUCT(NestedStruct, std::set<SimpleStruct>,
                std::multiset<SimpleStruct>, std::set<int_fast32_t>)
TEST(StdSetSerialization, UserDefinedStructs) {
    using TestFunctions::createInstanceAndTestIOSerialization;
    
    createInstanceAndTestIOSerialization<std::set<SimpleStruct>>();
    createInstanceAndTestIOSerialization<NestedStruct>();
    createInstanceAndTestIOSerialization<std::set<NestedStruct>>();
    createInstanceAndTestIOSerialization<std::multiset<NestedStruct>>();
}