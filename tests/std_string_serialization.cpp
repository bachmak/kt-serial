#include <gtest/gtest.h>

#include <string>
#include <random>

#include "kt-serial/types/std/string.h"
#include "test_helpers/test_functions.h"

const std::size_t maxSize = 1000;
const std::size_t iterCount = 100;

TEST(StdStringSerialization, CharString) {
    TestFunctions::binaryIOSerialization(std::string("  abcdefgh  "));
    TestFunctions::binaryIOSerialization(std::string(""));
    TestFunctions::binaryIOSerialization(std::string("a"));

    std::mt19937 gen;
    for (size_t i = 0; i < iterCount; i++) {
		TestFunctions::createInstanceAndTestIOSerialization<std::string>(gen);
    }
}

TEST(StdStringSerialization, WideCharString) {
    TestFunctions::binaryIOSerialization(std::wstring(L" fsdfsd "));
    TestFunctions::binaryIOSerialization(std::wstring(L" алдкгь "));
    TestFunctions::binaryIOSerialization(std::wstring(L""));
    TestFunctions::binaryIOSerialization(std::wstring(L"Я"));

	std::mt19937 gen;
    for (size_t i = 0; i < iterCount; i++) {
		TestFunctions::createInstanceAndTestIOSerialization<std::wstring>(gen);
    }
}

TEST(StdStringSerialization, Char32String) {
    TestFunctions::binaryIOSerialization(std::u32string(U"  ав  `ыук  "));
    TestFunctions::binaryIOSerialization(std::u32string(U""));
    TestFunctions::binaryIOSerialization(std::u32string(U" "));

    std::mt19937 gen;
    for (size_t i = 0; i < iterCount; i++) {
		TestFunctions::createInstanceAndTestIOSerialization<std::u32string>(gen);
    }
}

TEST(StdStringSerialization, Char16String) {
    TestFunctions::binaryIOSerialization(std::u16string(u"  ав  `ыук  "));
    TestFunctions::binaryIOSerialization(std::u16string(u""));
    TestFunctions::binaryIOSerialization(std::u16string(u" "));

	std::mt19937 gen;
    for (size_t i = 0; i < iterCount; i++) {
		TestFunctions::createInstanceAndTestIOSerialization<std::u16string>(gen);
    }
}