#include <QtCore>
#include <gtest/gtest.h>

#include "kt-serial/types/qt/q_list.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QListSerialization, IntTypes) {
    createInstanceAndTestIOSerialization<QList<int>>();
    createInstanceAndTestIOSerialization<QList<int8_t>>();
    createInstanceAndTestIOSerialization<QList<int16_t>>();
    createInstanceAndTestIOSerialization<QList<qint32>>();
    createInstanceAndTestIOSerialization<QList<qint64>>();
    createInstanceAndTestIOSerialization<QList<quint32>>();
    createInstanceAndTestIOSerialization<QList<quint64>>();
}

TEST(QListSerialization, FloatTypes) {
    createInstanceAndTestIOSerialization<QList<float>>();
    createInstanceAndTestIOSerialization<QList<double>>();
    createInstanceAndTestIOSerialization<QList<long double>>();
}

GENERATE_STRUCT(SimpleStruct, bool, char32_t, char, long double)

TEST(StdListSerialization, UserDefinedStructs) {
    createInstanceAndTestIOSerialization<QList<SimpleStruct>>();
}
