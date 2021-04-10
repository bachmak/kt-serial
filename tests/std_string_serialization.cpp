#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <string>

#include "kt-serial/archives/binary_istream_archive.h"
#include "kt-serial/archives/binary_ostream_archive.h"
#include "kt-serial/types/std/string.h"

template <class CharT> void testString(const std::basic_string<CharT>& str) {
    std::stringstream stream;
    {
        KtSerial::BinaryOstreamArchive oa(stream);
        oa << str;
    }

    std::basic_string<CharT> newStr;
    {
        KtSerial::BinaryIstreamArchive ia(stream);
        ia >> newStr;
    }

    EXPECT_EQ(str, newStr);
}

TEST(StdStringSerialization, CharString) {
    testString(std::string("  abcdefgh  "));
    testString(std::string(""));
    testString(std::string("a"));
}

TEST(StdStringSerialization, WideCharString) {
    testString(std::wstring(L" fsdfsd "));
    testString(std::wstring(L" алдкгь "));
    testString(std::wstring(L""));
    testString(std::wstring(L"Я"));
}

TEST(StdStringSerialization, Char32String) {
    testString(std::u32string(U"  ав  `ыук  "));
    testString(std::u32string(U""));
    testString(std::u32string(U" "));
}

TEST(StdStringSerialization, Char16String) {
    testString(std::u16string(u"  ав  `ыук  "));
    testString(std::u16string(u""));
    testString(std::u16string(u" "));
}