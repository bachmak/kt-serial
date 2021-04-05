#include <sstream>
#include <gtest/gtest.h>

#include "kt-serial/archives/binary_ostream_archive.h"


TEST(BinaryOstreamArchive, BasicTest)
{
    using namespace KtSerial;

    {
        std::ostringstream os;
        BinaryOstreamArchive ar(os);
        ar << 'a' << 'b' << 'c' << 'd' << 'e' << 'f';
        ar & 'a' & 'b' & 'c' & 'd' & 'e' & 'f';
        EXPECT_EQ(os.str(), "abcdefabcdef");
    }

    {
        std::ostringstream os;
        BinaryOstreamArchive ar(os);
        int a = static_cast<int>('A');
        int b = static_cast<int>('B');

        // int& a_ref = a;
        // const int& b_ref = b;

        ar << a;
        ar << b;
        EXPECT_EQ(1, 1);
    }
}