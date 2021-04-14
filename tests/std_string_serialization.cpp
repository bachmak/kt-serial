#include <gtest/gtest.h>

#include <string>

#include "kt-serial/types/std/string.h"
#include "test_helpers/test_functions.h"

TEST(StdStringSerialization, CharString) {
    testBinaryIOSerialization(std::string("  abcdefgh  "));
    testBinaryIOSerialization(std::string(""));
    testBinaryIOSerialization(std::string("a"));
}

TEST(StdStringSerialization, WideCharString) {
    testBinaryIOSerialization(std::wstring(L" fsdfsd "));
    testBinaryIOSerialization(std::wstring(L" алдкгь "));
    testBinaryIOSerialization(std::wstring(L""));
    testBinaryIOSerialization(std::wstring(L"Я"));
}

TEST(StdStringSerialization, Char32String) {
    testBinaryIOSerialization(std::u32string(U"  ав  `ыук  "));
    testBinaryIOSerialization(std::u32string(U""));
    testBinaryIOSerialization(std::u32string(U" "));
}

TEST(StdStringSerialization, Char16String) {
    testBinaryIOSerialization(std::u16string(u"  ав  `ыук  "));
    testBinaryIOSerialization(std::u16string(u""));
    testBinaryIOSerialization(std::u16string(u" "));
}