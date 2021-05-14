#include <gtest/gtest.h>
#include <random>
#include <utility>

#include "kt-serial/types/std/pair.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

TEST(StdPairSerialization, SimpleTypes) {
    std::pair<char, int> a;
    std::pair<bool, char32_t> b;
    std::pair<long double, bool> c;
    std::pair<float, int32_t> d;
    TestFunctions::randomizeVariadic(a, b, c, d);

    TestFunctions::binaryIOSerialization(a, b, c, d);
}

template <class T2> using StdIntKeyPair = std::pair<int, T2>;

template <class T2> using StdBoolKeyPair = std::pair<bool, T2>;

template <class T1> using StdDoubleValuePair = std::pair<T1, double>;

GENERATE_STRUCT(SimpleStruct, StdIntKeyPair<char32_t>, StdBoolKeyPair<wchar_t>,
                StdDoubleValuePair<float>, StdDoubleValuePair<bool>)

GENERATE_STRUCT(NestedStruct, StdIntKeyPair<SimpleStruct>,
                StdDoubleValuePair<SimpleStruct>, StdBoolKeyPair<SimpleStruct>,
                bool, StdBoolKeyPair<double>)

TEST(StdPairSerialization, UserDefinedStructs) {
    using TestFunctions::createInstanceAndTestIOSerialization;

    createInstanceAndTestIOSerialization<SimpleStruct>();
    createInstanceAndTestIOSerialization<NestedStruct>();
    createInstanceAndTestIOSerialization<
        std::pair<SimpleStruct, NestedStruct>>();
}
