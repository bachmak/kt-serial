#include <QtCore>
#include <gtest/gtest.h>

#include "kt-serial/types/qt/q_multi_map.h"
#include "kt-serial/types/qt/q_string.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QMultiMapSerialization, ArithmeticTypes) {
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<QMultiMap<int, int>>();
    createInstanceAndTestIOSerialization<QMultiMap<int, double>>();
    createInstanceAndTestIOSerialization<QMultiMap<quint64, quint64>>();
    createInstanceAndTestIOSerialization<QMultiMap<int, bool>>();
    createInstanceAndTestIOSerialization<QMultiMap<quint64, long double>>();
}

GENERATE_STRUCT(SimpleStruct, bool, double, wchar_t, int, bool, bool,
                long double)

TEST(QMultiMapSerialization, UserDefinedStructs) {
    TestFunctions::maxSize = 100;

    createInstanceAndTestIOSerialization<QMultiMap<int, SimpleStruct>>();
    createInstanceAndTestIOSerialization<QMultiMap<SimpleStruct, bool>>();
}

TEST(QMultiMapSerialization, NestedContainers) {
    createInstanceAndTestIOSerialization<
        QMultiMap<SimpleStruct, QMultiMap<SimpleStruct, double>>>();
}
