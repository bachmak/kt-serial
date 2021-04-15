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

void randomSize(std::size_t& size, std::size_t maxSize, std::mt19937& gen) {
    std::uniform_int_distribution<std::size_t> distr(0, maxSize);
    size = distr(gen);
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

template <
    class T, std::size_t Size,
    typename std::enable_if<!std::is_same<T, bool>::value, bool>::type = true>
void randomValue(std::array<T, Size>& arr, std::mt19937& gen) {
    for (auto& value : arr) {
        randomValue(value, gen);
    }
}

template <std::size_t Size>
void randomValue(std::array<bool, Size>& arr, std::mt19937& gen) {
    for (size_t i = 0; i < arr.size(); i++) {
        bool val = arr[i];
        randomValue(val, gen);
        arr[i] = val;
    }
}

template <
    class T, class Alloc,
    typename std::enable_if<!std::is_same<T, bool>::value, bool>::type = true>
void randomValue(std::vector<T, Alloc>& vec, std::mt19937& gen) {
    size_t vecSize;
    randomSize(vecSize, maxSize, gen);
    vec.resize(vecSize);

    for (auto& value : vec) {
        randomValue(value, gen);
    }
}

template <class Alloc>
void randomValue(std::vector<bool, Alloc>& vec, std::mt19937& gen) {
    size_t vecSize;
    randomSize(vecSize, maxSize, gen);
    vec.resize(vecSize);

    for (size_t i = 0; i < vec.size(); i++) {
        bool val = vec[i];
        randomValue(val, gen);
        vec[i] = val;
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
} // namespace TestFunctions
