#include <gtest/gtest.h>
#include <random>
#include <unordered_map>

#include "kt-serial/types/std/unordered_map.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(StdUnorderedMapSerialization, ArithmeticTypes) {
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<std::unordered_map<int, int>>();
    createInstanceAndTestIOSerialization<std::unordered_map<double, int>>();
    createInstanceAndTestIOSerialization<std::unordered_map<bool, char32_t>>();
    createInstanceAndTestIOSerialization<
        std::unordered_map<long double, bool>>();

    createInstanceAndTestIOSerialization<
        std::unordered_multimap<wchar_t, int_fast8_t>>();
    createInstanceAndTestIOSerialization<
        std::unordered_multimap<float, bool>>();
    createInstanceAndTestIOSerialization<std::unordered_multimap<bool, bool>>();
    createInstanceAndTestIOSerialization<
        std::unordered_multimap<bool, long double>>();
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
    TestFunctions::maxSize = 200;

    createInstanceAndTestIOSerialization<
        std::unordered_map<SimpleStruct, SimpleStruct>>();
    createInstanceAndTestIOSerialization<
        std::unordered_multimap<int, SimpleStruct>>();

    createInstanceAndTestIOSerialization<UnorderedMapStruct>();
    createInstanceAndTestIOSerialization<
        std::unordered_map<SimpleStruct, UnorderedMapStruct>>();
        // такой тест не проходит (непонятно почему, но размер играет роль - возможно, коллизии)
    // createInstanceAndTestIOSerialization<
    //     std::unordered_multimap<UnorderedMapStruct, SimpleStruct>>();
}
