#include <QtCore>
#include <gtest/gtest.h>

#include "kt-serial/types/qt/q_linked_list.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QLinkedListSerialization, IntTypes) {
    createInstanceAndTestIOSerialization<QLinkedList<int>>();
    createInstanceAndTestIOSerialization<QLinkedList<int8_t>>();
    createInstanceAndTestIOSerialization<QLinkedList<int16_t>>();
    createInstanceAndTestIOSerialization<QLinkedList<qint32>>();
    createInstanceAndTestIOSerialization<QLinkedList<qint64>>();
    createInstanceAndTestIOSerialization<QLinkedList<quint32>>();
    createInstanceAndTestIOSerialization<QLinkedList<quint64>>();
}

TEST(QLinkedListSerialization, FloatTypes) {
    createInstanceAndTestIOSerialization<QLinkedList<float>>();
    createInstanceAndTestIOSerialization<QLinkedList<double>>();
    createInstanceAndTestIOSerialization<QLinkedList<long double>>();
}

GENERATE_STRUCT(SimpleStruct, bool, char32_t, char, long double)

TEST(StdListSerialization, UserDefinedStructs) {
    createInstanceAndTestIOSerialization<QLinkedList<SimpleStruct>>();
}
