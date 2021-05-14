#include <gtest/gtest.h>

#include <random>
#include <string>

#include "kt-serial/types/std/string.h"
#include "test_helpers/test_functions.h"

const std::size_t iterCount = 100;

TEST(StdStringSerialization, CharString) {
    TestFunctions::maxSize = 1000;

    TestFunctions::binaryIOSerialization(std::string("  abcdefgh  "));
    TestFunctions::binaryIOSerialization(std::string(""));
    TestFunctions::binaryIOSerialization(std::string("a"));

    for (size_t i = 0; i < iterCount; i++) {
        TestFunctions::createInstanceAndTestIOSerialization<std::string>();
    }
}

TEST(StdStringSerialization, WideCharString) {
    TestFunctions::binaryIOSerialization(std::wstring(L" fsdfsd "));
    TestFunctions::binaryIOSerialization(std::wstring(L" алдкгь "));
    TestFunctions::binaryIOSerialization(std::wstring(L""));
    TestFunctions::binaryIOSerialization(std::wstring(L"Я"));

    for (size_t i = 0; i < iterCount; i++) {
        TestFunctions::createInstanceAndTestIOSerialization<std::wstring>();
    }
}

TEST(StdStringSerialization, Char32String) {
    TestFunctions::binaryIOSerialization(std::u32string(U"  ав  `ыук  "));
    TestFunctions::binaryIOSerialization(std::u32string(U""));
    TestFunctions::binaryIOSerialization(std::u32string(U" "));

    for (size_t i = 0; i < iterCount; i++) {
        TestFunctions::createInstanceAndTestIOSerialization<std::u32string>();
    }
}

TEST(StdStringSerialization, Char16String) {
    TestFunctions::binaryIOSerialization(std::u16string(u"  ав  `ыук  "));
    TestFunctions::binaryIOSerialization(std::u16string(u""));
    TestFunctions::binaryIOSerialization(std::u16string(u" "));

    for (size_t i = 0; i < iterCount; i++) {
        TestFunctions::createInstanceAndTestIOSerialization<std::u16string>();
    }
}