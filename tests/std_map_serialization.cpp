#include <gtest/gtest.h>
#include <map>
#include <random>

#include "kt-serial/types/std/map.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(StdMapSerialization, ArithmeticTypes) {
	TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<std::map<int, int>>();
    createInstanceAndTestIOSerialization<std::map<int, double>>();
    createInstanceAndTestIOSerialization<std::map<bool, char16_t>>();
    createInstanceAndTestIOSerialization<std::map<int_fast64_t, bool>>();
    createInstanceAndTestIOSerialization<std::map<long double, bool>>();

    createInstanceAndTestIOSerialization<std::multimap<int, int>>();
    createInstanceAndTestIOSerialization<std::multimap<unsigned, double>>();
    createInstanceAndTestIOSerialization<std::multimap<uint8_t, int8_t>>();
    createInstanceAndTestIOSerialization<std::multimap<bool, char16_t>>();
    createInstanceAndTestIOSerialization<std::multimap<char32_t, bool>>();
    createInstanceAndTestIOSerialization<std::multimap<long double, bool>>();
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
    TestFunctions::maxSize = 100;

    createInstanceAndTestIOSerialization<std::map<int, SimpleStruct>>();
    createInstanceAndTestIOSerialization<std::multimap<SimpleStruct, bool>>();
    createInstanceAndTestIOSerialization<std::multimap<bool, SimpleStruct>>();
    createInstanceAndTestIOSerialization<NestedStruct>();
    createInstanceAndTestIOSerialization<DoubleNestedStruct>();
    createInstanceAndTestIOSerialization<std::map<DoubleNestedStruct, bool>>();
}
