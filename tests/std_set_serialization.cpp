#include <gtest/gtest.h>
#include <random>
#include <set>

#include "kt-serial/types/std/set.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

GENERATE_STRUCT(SimpleStruct, bool, int_fast64_t, double_t, long double)

TEST(StdSetSerialization, UserDefinedStructs) {
    std::mt19937 gen;
    {
        std::set<SimpleStruct> sss;
        TestFunctions::binaryIOSerialization(sss);
        TestFunctions::randomize(sss, gen);
        TestFunctions::binaryIOSerialization(sss);
    }
}