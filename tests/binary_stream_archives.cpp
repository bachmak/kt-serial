#include <gtest/gtest.h>
#include <sstream>

#include "kt-serial/archives/output_archive.h"
#include "kt-serial/archives/input_archive.h"

TEST(BinaryStreamArchives, ArithmeticTypes) {
    using namespace KtSerial;

    {
        std::ostringstream os;
        OutputArchive ar(os);
        ar << 'a' << 'b' << 'c' << 'd' << 'e' << 'f';
        ar & 'a' & 'b' & 'c' & 'd' & 'e' & 'f';
        EXPECT_EQ(os.str(), "abcdefabcdef");
    }

    {
        std::istringstream is("abcdef");
        InputArchive ar(is);
        char a, b, c, d, e, f;
        ar >> a >> b >> c >> d >> e >> f;
        EXPECT_EQ(a, 'a');
        EXPECT_EQ(b, 'b');
        EXPECT_EQ(c, 'c');
        EXPECT_EQ(d, 'd');
        EXPECT_EQ(e, 'e');
        EXPECT_EQ(f, 'f');
    }

    {
        std::istringstream is("abcdef");
        InputArchive ar(is);
        char a, b, c, d, e, f;
        ar & a & b & c & d & e & f;
        EXPECT_EQ(a, 'a');
        EXPECT_EQ(b, 'b');
        EXPECT_EQ(c, 'c');
        EXPECT_EQ(d, 'd');
        EXPECT_EQ(e, 'e');
        EXPECT_EQ(f, 'f');
    }
}
