#pragma once

#include <boost/functional/hash.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <random>
#include <sstream>
#include <type_traits>

#include "kt-serial/archives/binary_istream_archive.h"
#include "kt-serial/archives/binary_ostream_archive.h"

namespace TestFunctions {
std::size_t maxSize = 100;

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

std::size_t randomSize(std::size_t max, std::mt19937& gen) {
    std::uniform_int_distribution<std::size_t> distr(0, max);
    return distr(gen);
}

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value &&
                                               std::is_signed<T>::value,
                                           bool>::type = true>
void randomize(T& t, std::mt19937& gen) {
    std::uniform_int_distribution<long long> distr(
        std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    t = static_cast<T>(distr(gen));
}

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value &&
                                               !std::is_signed<T>::value,
                                           bool>::type = true>
void randomize(T& t, std::mt19937& gen) {
    std::uniform_int_distribution<unsigned long long> distr(
        std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    t = static_cast<T>(distr(gen));
}

template <class T, typename std::enable_if<std::is_floating_point<T>::value,
                                           bool>::type = true>
void randomize(T& t, std::mt19937& gen) {
    std::uniform_real_distribution<long double> distr(
        std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    t = static_cast<T>(distr(gen));
}

template <class T, typename std::enable_if<std::is_same<T, bool>::value,
                                           bool>::type = true>
void randomize(T& t, std::mt19937& gen) {
    std::uniform_int_distribution<int> distr(0, 1);
    t = static_cast<bool>(distr(gen));
}

template <class T>
auto randomize(T& t, std::mt19937& gen)
    -> decltype(t.randomize(std::declval<std::mt19937&>())) {
    t.randomize(gen);
}

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& arr, std::mt19937& gen)
    -> decltype(arr.fill(std::declval<typename T::value_type>())) {
    for (auto&& item : arr) {
        bool val;
        randomize(val, gen);
        item = val;
    }
}

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& arr, std::mt19937& gen)
    -> decltype(arr.fill(std::declval<typename T::value_type>())) {
    for (auto& value : arr) {
        randomize(value, gen);
    }
}

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& seq, std::mt19937& gen)
    -> decltype(seq.resize(std::declval<std::size_t>())) {
    seq.clear();
    seq.resize(randomSize(maxSize, gen));
    for (auto&& item : seq) {
        bool val;
        randomize(val, gen);
        item = val;
    }
}

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& seq, std::mt19937& gen)
    -> decltype(seq.resize(std::declval<std::size_t>())) {
    seq.clear();
    seq.resize(randomSize(maxSize, gen));
    for (auto& value : seq) {
        randomize(value, gen);
    }
}

template <class T>
auto randomize(T& set, std::mt19937& gen)
    -> decltype(set.insert(std::declval<typename T::value_type>()), void()) {
    set.clear();
    size_t size = randomSize(maxSize, gen);

    for (size_t i = 0; i < size; i++) {
        typename T::value_type value;
        randomize(value, gen);
        set.insert(std::move(value));
    }
}

template <class T1, class T2>
void randomize(std::pair<T1, T2>& p, std::mt19937& gen) {
    randomize(p.first, gen);
    randomize(p.second, gen);
}

template <class T1, class T2>
void randomize(std::pair<const T1, T2>& p, std::mt19937& gen) {
    randomize(*const_cast<T1*>(&p.first), gen);
    randomize(p.second, gen);
}

template <class Type> void randomizeVariadic(std::mt19937& gen, Type& t) {
    randomize(t, gen);
}

template <class Type, class... Types>
void randomizeVariadic(std::mt19937& gen, Type& t, Types&... ts) {
    randomizeVariadic(gen, t);
    randomizeVariadic(gen, ts...);
}

std::size_t pow(std::size_t x, std::size_t y) {
    if (y == 1) {
        return x;
    }
    if (y == 0) {
        return 1;
    }
    return x * pow(x, y - 1);
}

template <class T> std::size_t hashCode(const T& t) {
    return boost::hash_value(t);
}

template <class Type, class... Types>
std::size_t hashCode(const Type& t, const Types&... ts) {
    std::size_t p = sizeof...(Types) + 1;
    return hashCode(t) * pow(997u, p) + hashCode(ts...);
}

template <class Type>
void createInstanceAndTestIOSerialization(std::mt19937& gen) {
    Type t;
    binaryIOSerialization(t);
    randomize(t, gen);
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
