#include <gtest/gtest.h>
#include <map>
#include <random>

#include "kt-serial/types/std/map.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(StdMapSerialization, ArithmeticTypes) {
    std::mt19937 gen;
	TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<std::map<int, int>>(gen);
    createInstanceAndTestIOSerialization<std::map<int, double>>(gen);
    createInstanceAndTestIOSerialization<std::map<bool, char16_t>>(gen);
    createInstanceAndTestIOSerialization<std::map<int_fast64_t, bool>>(gen);
    createInstanceAndTestIOSerialization<std::map<long double, bool>>(gen);

    createInstanceAndTestIOSerialization<std::multimap<int, int>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<unsigned, double>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<uint8_t, int8_t>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<bool, char16_t>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<char32_t, bool>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<long double, bool>>(gen);
}

template <class T> using StdIntKeyMap = std::map<int, T>;

template <class Key> using StdDoubleValueMap = std::map<Key, double>;

template <class T> using StdLongDoubleKeyMap = std::map<long double, T>;

template <class T> using StdIntKeyMultimap = std::multimap<int, T>;

template <class Key> using StdDoubleValueMultimap = std::multimap<Key, double>;

template <class T>
using StdLongDoubleKeyMultimap = std::multimap<long double, T>;

GENERATE_STRUCT(SimpleStruct, bool, double, wchar_t, int, bool, bool,
                long double)
GENERATE_STRUCT(NestedStruct, StdIntKeyMap<SimpleStruct>,
                StdDoubleValueMap<SimpleStruct>,
                StdLongDoubleKeyMap<SimpleStruct>, StdIntKeyMultimap<char32_t>)
GENERATE_STRUCT(DoubleNestedStruct, StdDoubleValueMultimap<NestedStruct>,
                StdIntKeyMultimap<bool>, double, StdIntKeyMap<SimpleStruct>)

TEST(StdMapSerialization, UserDefinedStructs) {
    std::mt19937 gen;
    TestFunctions::maxSize = 100;

    createInstanceAndTestIOSerialization<std::map<int, SimpleStruct>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<SimpleStruct, bool>>(gen);
    createInstanceAndTestIOSerialization<std::multimap<bool, SimpleStruct>>(gen);
    createInstanceAndTestIOSerialization<NestedStruct>(gen);
    createInstanceAndTestIOSerialization<DoubleNestedStruct>(gen);
    createInstanceAndTestIOSerialization<std::map<DoubleNestedStruct, bool>>(gen);
}
