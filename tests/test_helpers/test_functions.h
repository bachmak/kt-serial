#pragma once

#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <random>
#include <sstream>
#include <type_traits>

#include "kt-serial/archives/binary_istream_archive.h"
#include "kt-serial/archives/binary_ostream_archive.h"

namespace TestFunctions {
const std::size_t maxSize = 100;

template <class Type> void binaryIOSerialization(const Type& t) {
    std::stringstream stream;

    {
        KtSerial::BinaryOstreamArchive oa(stream);
        oa(t);
        oa << t;
        oa& t;
    }

    Type t1, t2, t3;

    {
        KtSerial::BinaryIstreamArchive ia(stream);
        ia(t1);
        ia >> t2;
        ia& t3;
    }

    EXPECT_EQ(t1, t);
    EXPECT_EQ(t2, t);
    EXPECT_EQ(t3, t);
}

std::size_t randomSize(std::size_t maxSize, std::mt19937& gen) {
    std::uniform_int_distribution<std::size_t> distr(0, maxSize);
    return distr(gen);
}

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value,
                                           bool>::type = true>
void randomValue(T& t, std::mt19937& gen) {
    std::uniform_int_distribution<T> distr(std::numeric_limits<T>::min(),
                                           std::numeric_limits<T>::max());
    t = distr(gen);
}

template <class T, typename std::enable_if<std::is_floating_point<T>::value,
                                           bool>::type = true>
void randomValue(T& t, std::mt19937& gen) {
    std::uniform_real_distribution<T> distr(std::numeric_limits<T>::min(),
                                            std::numeric_limits<T>::max());
    t = distr(gen);
}

template <class T, typename std::enable_if<std::is_same<T, bool>::value,
                                           bool>::type = true>
void randomValue(T& t, std::mt19937& gen) {
    std::uniform_int_distribution<int> distr(0, 1);
    t = static_cast<bool>(distr(gen));
}

template <class T>
auto randomValue(T& t, std::mt19937& gen)
    -> decltype(t.fillRandom(std::declval<std::mt19937&>())) {
    t.fillRandom(gen);
}

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomValue(T& arr, std::mt19937& gen)
    -> decltype(arr.fill(std::declval<typename T::value_type>())) {
    for (auto&& item : arr) {
        bool val;
        randomValue(val, gen);
        item = val;
    }
}

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomValue(T& arr, std::mt19937& gen)
    -> decltype(arr.fill(std::declval<typename T::value_type>())) {
    for (auto& value : arr) {
        randomValue(value, gen);
    }
}

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomValue(T& seq, std::mt19937& gen)
    -> decltype(seq.resize(std::declval<std::size_t>())) {
    seq.clear();
    seq.resize(randomSize(maxSize, gen));
    for (auto&& item : seq) {
        bool val;
        randomValue(val, gen);
        item = val;
    }
}

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomValue(T& seq, std::mt19937& gen)
    -> decltype(seq.resize(std::declval<std::size_t>())) {
    seq.clear();
    seq.resize(randomSize(maxSize, gen));
    for (auto& value : seq) {
        randomValue(value, gen);
    }
}

template <class Type> void fillWithRandomValues(std::mt19937& gen, Type& t) {
    randomValue(t, gen);
}

template <class Type, class... Types>
void fillWithRandomValues(std::mt19937& gen, Type& t, Types&... ts) {
    fillWithRandomValues(gen, t);
    fillWithRandomValues(gen, ts...);
}

template <class FwdIt>
typename std::enable_if<
    std::numeric_limits<
        typename std::iterator_traits<FwdIt>::value_type>::is_integer &&
    !std::is_same<typename std::iterator_traits<FwdIt>::value_type,
                  bool>::value>::type
fillWithRandomValues(FwdIt begin, FwdIt end) {
    using Type = typename std::iterator_traits<FwdIt>::value_type;
    std::mt19937 gen;
    std::uniform_int_distribution<Type> distr(std::numeric_limits<Type>::min(),
                                              std::numeric_limits<Type>::max());

    while (begin != end) {
        *begin++ = distr(gen);
    }
}

template <class FwdIt>
typename std::enable_if<std::numeric_limits<
    typename std::iterator_traits<FwdIt>::value_type>::is_iec559>::type
fillWithRandomValues(FwdIt begin, FwdIt end) {
    using Type = typename std::iterator_traits<FwdIt>::value_type;
    std::mt19937 gen;
    std::uniform_real_distribution<Type> distr(
        std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max());

    while (begin != end) {
        *begin++ = distr(gen);
    }
}

template <class FwdIt>
typename std::enable_if<std::is_same<
    typename std::iterator_traits<FwdIt>::value_type, bool>::value>::type
fillWithRandomValues(FwdIt begin, FwdIt end) {
    std::mt19937 gen;
    std::uniform_int_distribution<int> distr(0, 1);

    while (begin != end) {
        *begin++ = static_cast<bool>(distr(gen));
    }
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
        TEST_BINARY_IO_SERIALIZATION_MIN_MAX(container, uint, size);           \
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
