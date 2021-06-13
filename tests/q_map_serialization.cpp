#include <QtCore>
#include <gtest/gtest.h>

#include "kt-serial/types/qt/q_map.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QMapSerialization, ArithmeticTypes) {
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<QMap<int, int>>();
    createInstanceAndTestIOSerialization<QMap<int, double>>();
    createInstanceAndTestIOSerialization<QMap<bool, char16_t>>();
    createInstanceAndTestIOSerialization<QMap<int_fast64_t, bool>>();
    createInstanceAndTestIOSerialization<QMap<long double, bool>>();
}

GENERATE_STRUCT(SimpleStruct, bool, double, wchar_t, int, bool, bool,
                long double)

TEST(QMapSerialization, UserDefinedStructs) {
	TestFunctions::maxSize = 100;

	createInstanceAndTestIOSerialization<QMap<int, SimpleStruct>>();
	createInstanceAndTestIOSerialization<QMap<SimpleStruct, bool>>();
}

TEST(QMapSerialization, NestedContainers) {
	createInstanceAndTestIOSerialization<QMap<SimpleStruct, QMap<SimpleStruct, double>>>();
}
