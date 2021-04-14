#include "kt-serial/archives/binary_istream_archive.h"
#include "kt-serial/archives/binary_ostream_archive.h"
#include "kt-serial/types/std/vector.h"
#include "test_helpers/struct_generator.h"
#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <tuple>

template <class T> void testVector(const std::vector<T>& vec) {
    std::stringstream stream;

    {
        KtSerial::BinaryOstreamArchive oa(stream);
        oa << vec;
    }

    std::vector<T> newVec;

    {
        KtSerial::BinaryIstreamArchive ia(stream);
        ia >> newVec;
    }

    EXPECT_EQ(newVec, vec);
}

#define TEST_VECTOR(typeName, value)                                           \
    {                                                                          \
        testVector(std::vector<typeName>(1000, value));                        \
        testVector(std::vector<typeName>(0, value));                           \
        testVector(std::vector<typeName>({value}));                            \
    }

#define TEST_VECTOR_MIN_MAX(typeName)                                          \
    {                                                                          \
        TEST_VECTOR(typeName, std::numeric_limits<typeName>::min());           \
        TEST_VECTOR(typeName, std::numeric_limits<typeName>::max());           \
        TEST_VECTOR(typeName, std::numeric_limits<typeName>::lowest());        \
    }

TEST(StdVectorSerialization, IntTypes) {
    TEST_VECTOR_MIN_MAX(int);
    TEST_VECTOR_MIN_MAX(int8_t);
    TEST_VECTOR_MIN_MAX(int16_t);
    TEST_VECTOR_MIN_MAX(int32_t);
    TEST_VECTOR_MIN_MAX(int64_t);
    TEST_VECTOR_MIN_MAX(int_fast8_t);
    TEST_VECTOR_MIN_MAX(int_fast16_t);
    TEST_VECTOR_MIN_MAX(int_fast32_t);
    TEST_VECTOR_MIN_MAX(int_fast64_t);
    TEST_VECTOR_MIN_MAX(intmax_t);
    TEST_VECTOR_MIN_MAX(intptr_t);
}

TEST(StdVectorSerialization, UintTypes) {
    TEST_VECTOR_MIN_MAX(uint);
    TEST_VECTOR_MIN_MAX(uint8_t);
    TEST_VECTOR_MIN_MAX(uint16_t);
    TEST_VECTOR_MIN_MAX(uint32_t);
    TEST_VECTOR_MIN_MAX(uint64_t);
    TEST_VECTOR_MIN_MAX(uint_fast8_t);
    TEST_VECTOR_MIN_MAX(uint_fast16_t);
    TEST_VECTOR_MIN_MAX(uint_fast32_t);
    TEST_VECTOR_MIN_MAX(uint_fast64_t);
    TEST_VECTOR_MIN_MAX(uintmax_t);
    TEST_VECTOR_MIN_MAX(uintptr_t);
}

TEST(StdVectorSerialization, CharTypes) {
    TEST_VECTOR_MIN_MAX(char);
    TEST_VECTOR_MIN_MAX(wchar_t);
    TEST_VECTOR_MIN_MAX(char16_t);
    TEST_VECTOR_MIN_MAX(char32_t);
}

TEST(StdVectorSerialization, FloatTypes) {
    TEST_VECTOR_MIN_MAX(float);
    TEST_VECTOR_MIN_MAX(double);
    TEST_VECTOR_MIN_MAX(long double);
}

TEST(StdVectorSerialization, Bool) {
    TEST_VECTOR(bool, 1);
    TEST_VECTOR(bool, 0);
    testVector(std::vector<bool>({1, 1, 1, 0, 0, 1, 0, 0}));
    testVector(std::vector<bool>({0, 0, 1, 0, 0, 0, 1, 1}));
}

GENERATE_STRUCT(BoolStruct, bool, bool, bool, bool, bool, bool)

GENERATE_STRUCT(SimpleStruct, int, unsigned, char, float, double, bool)

GENERATE_STRUCT(VectorStruct, std::vector<int>, std::vector<uint>,
                std::vector<SimpleStruct>, std::vector<bool>, char, double)

TEST(StdVectorSerialization, UserDefinedStructs) {
    SimpleStruct ss{1, 2u, 'c', 2.28f, 2.71, true};
    testVector(std::vector<SimpleStruct>(10, ss));
    testVector(std::vector<VectorStruct>(10, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                              {0u, 3u, 7u, 19u, 143u},
                                              {10, ss},
                                              {1, 0, 0, 1, 0, 0, 1},
                                              'j',
                                              3123.3}));
    testVector(std::vector<BoolStruct>(10, {1, 0, 0, 1, 0, 1}));
}