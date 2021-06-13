#include <gtest/gtest.h>
#include <QtCore>

#include "kt-serial/types/qt/q_multi_hash.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QMultiHashSerialization, ArithmeticTypes) {
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<QMultiHash<int, int>>();
    createInstanceAndTestIOSerialization<QMultiHash<double, int>>();
    createInstanceAndTestIOSerialization<
        QMultiHash<double, bool>>();
	
	createInstanceAndTestIOSerialization<QMultiHash<quint32, wchar_t>>();
	createInstanceAndTestIOSerialization<QMultiHash<bool, bool>>();
	createInstanceAndTestIOSerialization<QMultiHash<bool, long double>>();
}

