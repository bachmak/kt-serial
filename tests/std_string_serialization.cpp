#include <gtest/gtest.h>

#include <string>

#include "kt-serial/types/std/string.h"
#include "test_helpers/test_functions.h"

TEST(StdStringSerialization, CharString) {
    TestFunctions::binaryIOSerialization(std::string("  abcdefgh  "));
    TestFunctions::binaryIOSerialization(std::string(""));
    TestFunctions::binaryIOSerialization(std::string("a"));
}

TEST(StdStringSerialization, WideCharString) {
    TestFunctions::binaryIOSerialization(std::wstring(L" fsdfsd "));
    TestFunctions::binaryIOSerialization(std::wstring(L" алдкгь "));
    TestFunctions::binaryIOSerialization(std::wstring(L""));
    TestFunctions::binaryIOSerialization(std::wstring(L"Я"));
}

TEST(StdStringSerialization, Char32String) {
    TestFunctions::binaryIOSerialization(std::u32string(U"  ав  `ыук  "));
    TestFunctions::binaryIOSerialization(std::u32string(U""));
    TestFunctions::binaryIOSerialization(std::u32string(U" "));
}

TEST(StdStringSerialization, Char16String) {
    TestFunctions::binaryIOSerialization(std::u16string(u"  ав  `ыук  "));
    TestFunctions::binaryIOSerialization(std::u16string(u""));
    TestFunctions::binaryIOSerialization(std::u16string(u" "));
}