#include <QtCore>
#include <gtest/gtest.h>

#include "kt-serial/types/qt/q_set.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

using TestFunctions::createInstanceAndTestIOSerialization;

TEST(QSetSerialization, ArithmeticTypes) {
    QSet<int> a;
    QSet<double> b;
    QSet<bool> c;

    TestFunctions::binaryIOSerialization(a, b, c);
    TestFunctions::randomizeVariadic(a, b, c);
    TestFunctions::binaryIOSerialization(a, b, c);
}

TEST(QSetSerialization, NestedContainers) {
	createInstanceAndTestIOSerialization<QSet<QSet<double>>>();
}

