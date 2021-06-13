#include <QtCore>
#include <gtest/gtest.h>
#include <vector>

#include "kt-serial/types/qt/q_vector.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::maxSize;

TEST(QVectorSerialization, IntTypes) {
    TEST_BINARY_IO_SERIALIZATION_INT_TYPES(QVector, maxSize);
}

TEST(QVectorSerialization, UintTypes) {
    TEST_BINARY_IO_SERIALIZATION_UINT_TYPES(QVector, maxSize);
}

TEST(QVectorSerialization, CharTypes) {
    TEST_BINARY_IO_SERIALIZATION_CHAR_TYPES(QVector, maxSize);
}

TEST(QVectorSerialization, FloatTypes) {
    TEST_BINARY_IO_SERIALIZATION_FLOAT_TYPES(QVector, maxSize);
}

TEST(QVectorSerialization, Bool) {
    TEST_BINARY_IO_SERIALIZATION_MIN_MAX(QVector, bool, maxSize);
    TestFunctions::binaryIOSerialization(
        QVector<bool>({1, 1, 1, 0, 0, 1, 0, 0}));
    TestFunctions::binaryIOSerialization(
        QVector<bool>({0, 0, 1, 0, 0, 0, 1, 1}));
}

GENERATE_STRUCT(BoolStruct, bool, bool, bool, bool, bool, bool)

GENERATE_STRUCT(SimpleStruct, int, unsigned, char, float, double, bool)

TEST(QVectorSerialization, UserDefinedStructs) {
    using TestFunctions::createInstanceAndTestIOSerialization;

    createInstanceAndTestIOSerialization<QVector<BoolStruct>>();
    createInstanceAndTestIOSerialization<QVector<SimpleStruct>>();
    createInstanceAndTestIOSerialization<QVector<QVector<SimpleStruct>>>();
}
