#include <gtest/gtest.h>
#include <random>
#include <unordered_map>

#include "kt-serial/types/std/unordered_map.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/unordered_specific.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(StdUnorderedMapSerialization, ArithmeticTypes) {
    std::mt19937 gen;
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<std::unordered_map<int, int>>(gen);
    createInstanceAndTestIOSerialization<std::unordered_map<double, int>>(gen);
    createInstanceAndTestIOSerialization<std::unordered_map<bool, char32_t>>(
        gen);
    createInstanceAndTestIOSerialization<std::unordered_map<long double, bool>>(
        gen);

    createInstanceAndTestIOSerialization<
        std::unordered_multimap<wchar_t, int_fast8_t>>(gen);
    createInstanceAndTestIOSerialization<std::unordered_multimap<float, bool>>(
        gen);
    createInstanceAndTestIOSerialization<std::unordered_multimap<bool, bool>>(
        gen);
    createInstanceAndTestIOSerialization<
        std::unordered_multimap<bool, long double>>(gen);
}

template <class Key>
using StdDoubleValUnorderedMap = std::unordered_map<Key, double>;

template <class Val> using StdIntKeyUnorderedMap = std::unordered_map<int, Val>;

template <class Key>
using StdCharValUnorderedMultimap = std::unordered_multimap<Key, wchar_t>;

template <class Val>
using StdBoolKeyUnorderedMultimap = std::unordered_multimap<bool, Val>;

GENERATE_STRUCT(SimpleStruct, bool, bool, long double, float, char32_t,
                unsigned)

GENERATE_STRUCT(UnorderedMapStruct, StdDoubleValUnorderedMap<SimpleStruct>,
                StdIntKeyUnorderedMap<bool>,
                StdCharValUnorderedMultimap<SimpleStruct>,
                StdBoolKeyUnorderedMultimap<bool>)

TEST(StdUnorderedMapSerialization, UserDefinedStructs) {
    std::mt19937 gen;
    TestFunctions::maxSize = 200;

    createInstanceAndTestIOSerialization<
        std::unordered_map<SimpleStruct, SimpleStruct>>(gen);
    createInstanceAndTestIOSerialization<
        std::unordered_multimap<int, SimpleStruct>>(gen);

    createInstanceAndTestIOSerialization<UnorderedMapStruct>(gen);
    createInstanceAndTestIOSerialization<
        std::unordered_map<SimpleStruct, UnorderedMapStruct>>(gen);
    createInstanceAndTestIOSerialization<
        std::unordered_multimap<UnorderedMapStruct, SimpleStruct>>(gen);
}
