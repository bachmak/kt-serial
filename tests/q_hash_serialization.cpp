#include <gtest/gtest.h>
#include <QtCore>

#include "kt-serial/types/qt/q_hash.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QHashSerialization, ArithmeticTypes) {
    TestFunctions::maxSize = 10000;

    createInstanceAndTestIOSerialization<QHash<int, int>>();
    createInstanceAndTestIOSerialization<QHash<double, int>>();
    createInstanceAndTestIOSerialization<
        QHash<double, bool>>();
	// не проходит аналогичный тест с ключами типа long double
	
	createInstanceAndTestIOSerialization<QHash<quint32, wchar_t>>();
	createInstanceAndTestIOSerialization<QHash<bool, bool>>();
	createInstanceAndTestIOSerialization<QHash<bool, long double>>();
}

