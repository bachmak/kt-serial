#include <gtest/gtest.h>

#include <random>
#include <QString>

#include "kt-serial/types/qt/q_string.h"
#include "test_helpers/test_functions.h"

const std::size_t iterCount = 100;

TEST(QStringSerialization, ASCIICharacters) {
	TestFunctions::maxSize = 1000;

	TestFunctions::binaryIOSerialization(QString("  abcdefgh  "));
	TestFunctions::binaryIOSerialization(QString(""));
	TestFunctions::binaryIOSerialization(QString("a"));

	for (size_t i = 0; i < iterCount; i++) {
		TestFunctions::createInstanceAndTestIOSerialization<QString>();
	}
}


TEST(QStringSerialization, UTF8Characters) {
	TestFunctions::binaryIOSerialization(QString("  абвгдеёжзий  "));
	TestFunctions::binaryIOSerialization(QString(" ffrr ааывлод      "));
	TestFunctions::binaryIOSerialization(QString("Я"));
}
