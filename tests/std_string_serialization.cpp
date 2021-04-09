#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <sstream>
#include <algorithm>

#include "kt-serial/archives/binary_ostream_archive.h"
#include "kt-serial/types/std/string.h"

template <class CharT>
bool hasSubstring(const std::basic_string<CharT>& str, const std::basic_string<CharT>& sub)
{
    auto it = std::search(str.begin(), str.end(), sub.begin(), sub.end());
    return it != str.end();
}

template <class CharT>
KtSerial::SizeType getSize(const std::basic_ostringstream<CharT>& os)
{
    auto str = os.str();
    const KtSerial::SizeType* size_ptr;
    size_ptr = reinterpret_cast<const KtSerial::SizeType*>(str.data());
    return *size_ptr;
}

template<class CharT>
void testString(const std::basic_string<CharT>& str)
{
    std::basic_ostringstream<CharT> os;
    KtSerial::BasicBinaryOstreamArchive<CharT> oa(os);
    oa << str;
    EXPECT_EQ(getSize(os), str.size());
    EXPECT_TRUE(hasSubstring(os.str(), str));
}

TEST(StdStringSerialization, CharString)
{
    testString(std::string("  abcdefgh  "));
    testString(std::string(""));
    testString(std::string("a"));
}

TEST(StdStringSerialization, WideCharString)
{
    testString(std::wstring(L" fsdfsd "));
    testString(std::wstring(L" алдкгь "));
    testString(std::wstring(L""));
    testString(std::wstring(L"Я"));
}

TEST(StdStringSerialization, Char32String)
{
    testString(std::u32string(U"  ав  `ыук  "));
    testString(std::u32string(U""));
    testString(std::u32string(U" "));
}

TEST(StdStringSerialization, Char16String)
{
    testString(std::u16string(u"  ав  `ыук  "));
    testString(std::u16string(u""));
    testString(std::u16string(u" "));
}