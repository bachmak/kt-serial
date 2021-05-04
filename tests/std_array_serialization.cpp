#include <array>
#include <gtest/gtest.h>
#include <random>
#include <type_traits>

#include "kt-serial/types/std/array.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

const std::size_t size = 1000;

template <class Type, std::size_t Size>
void testStdArrayBinaryIOSerializationMinMax(std::array<Type, Size>& arr) {
    arr.fill(std::numeric_limits<Type>::max());
    TestFunctions::binaryIOSerialization(arr);

    arr.fill(std::numeric_limits<Type>::min());
    TestFunctions::binaryIOSerialization(arr);

    arr.fill(std::numeric_limits<Type>::lowest());
    TestFunctions::binaryIOSerialization(arr);
}

template <class Type, std::size_t Size>
void testStdArrayBinaryIOSerialization() {
    std::array<Type, Size> arr;
    testStdArrayBinaryIOSerializationMinMax(arr);

    std::array<Type, 0> empty;
    testStdArrayBinaryIOSerializationMinMax(empty);

    std::array<Type, 1> single;
    testStdArrayBinaryIOSerializationMinMax(single);
}

TEST(StdArraySerialization, IntTypes) {
    testStdArrayBinaryIOSerialization<int, size>();
    testStdArrayBinaryIOSerialization<int8_t, size>();
    testStdArrayBinaryIOSerialization<int16_t, size>();
    testStdArrayBinaryIOSerialization<int32_t, size>();
    testStdArrayBinaryIOSerialization<int64_t, size>();
    testStdArrayBinaryIOSerialization<int_fast8_t, size>();
    testStdArrayBinaryIOSerialization<int_fast16_t, size>();
    testStdArrayBinaryIOSerialization<int_fast32_t, size>();
    testStdArrayBinaryIOSerialization<int_fast64_t, size>();
    testStdArrayBinaryIOSerialization<intmax_t, size>();
    testStdArrayBinaryIOSerialization<intptr_t, size>();
}

TEST(StdArraySerialization, UintTypes) {
    testStdArrayBinaryIOSerialization<unsigned, size>();
    testStdArrayBinaryIOSerialization<uint8_t, size>();
    testStdArrayBinaryIOSerialization<uint16_t, size>();
    testStdArrayBinaryIOSerialization<uint32_t, size>();
    testStdArrayBinaryIOSerialization<uint64_t, size>();
    testStdArrayBinaryIOSerialization<uint_fast8_t, size>();
    testStdArrayBinaryIOSerialization<uint_fast16_t, size>();
    testStdArrayBinaryIOSerialization<uint_fast32_t, size>();
    testStdArrayBinaryIOSerialization<uint_fast64_t, size>();
    testStdArrayBinaryIOSerialization<uintmax_t, size>();
    testStdArrayBinaryIOSerialization<uintptr_t, size>();
}

TEST(StdArraySerialization, CharTypes) {
    testStdArrayBinaryIOSerialization<char, size>();
    testStdArrayBinaryIOSerialization<wchar_t, size>();
    testStdArrayBinaryIOSerialization<char16_t, size>();
    testStdArrayBinaryIOSerialization<char32_t, size>();
}

TEST(StdArraySerialization, FloatTypes) {
    testStdArrayBinaryIOSerialization<float, size>();
    testStdArrayBinaryIOSerialization<double, size>();
    testStdArrayBinaryIOSerialization<long double, size>();
}

TEST(StdArraySerialization, Bool) {
    testStdArrayBinaryIOSerialization<bool, size>();
    TestFunctions::binaryIOSerialization(
        std::array<bool, 6>({1, 0, 0, 1, 1, 0}));
}

template <class T> using StdArray100 = std::array<T, 100>;

template <class T> using StdArray23 = std::array<T, 23>;

template <class T> using StdArray199 = std::array<T, 199>;

GENERATE_STRUCT(SimpleStruct, int_fast64_t, uint16_t, wchar_t, bool, bool,
                long double)

GENERATE_STRUCT(ArrayStruct, StdArray100<SimpleStruct>, StdArray199<wchar_t>,
                StdArray23<bool>, StdArray199<StdArray23<long double>>, bool,
                long double)

GENERATE_STRUCT(DoubleNested, StdArray23<ArrayStruct>, bool, long double)

TEST(StdArraySerialization, UserDefinedStructs) {
    std::mt19937 gen;

    {
        SimpleStruct ss;
        TestFunctions::binaryIOSerialization(ss);
        ss.randomize(gen);
        TestFunctions::binaryIOSerialization(ss);
    }

    {
        ArrayStruct as;
        TestFunctions::binaryIOSerialization(as);
        as.randomize(gen);
        TestFunctions::binaryIOSerialization(as);
    }

    {

        DoubleNested dn;
        // сериализация неинициализированной структуры DoubleNested некорректна
        // (возможно, из-за несравниваемых значений полей - например, NaN)
        dn.randomize(gen);
        TestFunctions::binaryIOSerialization(dn);
    }
}
