#pragma once

#include <sstream>
#include <gtest/gtest.h>

#include "kt-serial/archives/binary_ostream_archive.h"
#include "kt-serial/archives/binary_istream_archive.h"

template <class Type>
void testBinaryIOSerialization(const Type& t) {
    std::stringstream stream;

    {
        KtSerial::BinaryOstreamArchive oa(stream);
        oa(t);
        oa << t;
        oa & t;
    }

    Type t1, t2, t3;

    {
        KtSerial::BinaryIstreamArchive ia(stream);
        ia(t1);
        ia >> t2;
        ia & t3;
    }

    EXPECT_EQ(t1, t);
    EXPECT_EQ(t2, t);
    EXPECT_EQ(t3, t);
}
