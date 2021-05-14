#pragma once

#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <type_traits>

#include "kt-serial/archives/binary_istream_archive.h"
#include "kt-serial/archives/binary_ostream_archive.h"

#include "test_helpers/random.h"
#include "test_helpers/hash.h"
#include "test_helpers/clear.h"

namespace TestFunctions {

template <class Type> void binaryIOSerialization(Type&& t) {
    std::stringstream stream;

    {
        KtSerial::BinaryOstreamArchive oa(stream);
        oa(t);
        oa << t;
        oa & t;
    }

    typename std::remove_reference<Type>::type t1, t2, t3;

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

template <class Type, class... Types>
void binaryIOSerialization(Type&& t, Types&&... ts) {
    binaryIOSerialization(std::forward<Type>(t));
    binaryIOSerialization(std::forward<Types>(ts)...);
}

template <class Type>
void createInstanceAndTestIOSerialization() {
    Type t;
    clear(t);
    binaryIOSerialization(t);
    randomize(t);
    binaryIOSerialization(t);
}

#define TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, valueType, size)       \
    {                                                                          \
        TestFunctions::binaryIOSerialization(container<valueType>(             \
            size, std::numeric_limits<valueType>::max()));                     \
        TestFunctions::binaryIOSerialization(container<valueType>(             \
            size, std::numeric_limits<valueType>::min()));                     \
        TestFunctions::binaryIOSerialization(container<valueType>(             \
            size, std::numeric_limits<valueType>::lowest()));                  \
                                                                               \
        TestFunctions::binaryIOSerialization(                                  \
            container<valueType>(1, std::numeric_limits<valueType>::max()));   \
        TestFunctions::binaryIOSerialization(                                  \
            container<valueType>(1, std::numeric_limits<valueType>::min()));   \
        TestFunctions::binaryIOSerialization(container<valueType>(             \
            1, std::numeric_limits<valueType>::lowest()));                     \
                                                                               \
        TestFunctions::binaryIOSerialization(                                  \
            container<valueType>(0, std::numeric_limits<valueType>::max()));   \
        TestFunctions::binaryIOSerialization(                                  \
            container<valueType>(0, std::numeric_limits<valueType>::min()));   \
        TestFunctions::binaryIOSerialization(container<valueType>(             \
            0, std::numeric_limits<valueType>::lowest()));                     \
    }

#define TEST_BINARY_IO_SERIALIZATION_INT_TYPES(container, size)                \
    {                                                                          \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int, size);            \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int8_t, size);         \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int16_t, size);        \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int32_t, size);        \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int64_t, size);        \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_fast8_t, size);    \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_fast16_t, size);   \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_fast32_t, size);   \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_fast64_t, size);   \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_least8_t, size);   \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_least16_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_least32_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, int_least64_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, intmax_t, size);       \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, intptr_t, size);       \
    }

#define TEST_BINARY_IO_SERIALIZATION_UINT_TYPES(container, size)               \
    {                                                                          \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, unsigned, size);       \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint8_t, size);        \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint16_t, size);       \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint32_t, size);       \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint64_t, size);       \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_fast8_t, size);   \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_fast16_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_fast32_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_fast64_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_least8_t, size);  \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_least16_t, size); \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_least32_t, size); \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint_least64_t, size); \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uintmax_t, size);      \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uintptr_t, size);      \
    }

#define TEST_BINARY_IO_SERIALIZATION_CHAR_TYPES(container, size)               \
    {                                                                          \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, char, size);           \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, wchar_t, size);        \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, char16_t, size);       \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, char32_t, size);       \
    }

#define TEST_BINARY_IO_SERIALIZATION_FLOAT_TYPES(container, size)              \
    {                                                                          \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, float, size);          \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, double, size);         \
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, long double, size);    \
    }
} // namespace TestFunctions
