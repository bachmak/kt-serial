#include "kt-serial/archives/binary_ostream_archive.h"
#include "kt-serial/types/std/vector.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(StdVectorSerialization, ArithmeticVector) {
    std::ostringstream os;
    KtSerial::BinaryOstreamArchive oa(os);

    oa << std::vector<int>(10, 1);
}