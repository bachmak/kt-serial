#pragma once

#include "random.h"

namespace TestFunctions {

std::size_t randomSize(std::size_t maxValue) {
    std::uniform_int_distribution<std::size_t> distr(0, maxValue);
    return distr(gen);
}

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value &&
                                               std::is_signed<T>::value,
                                           bool>::type>
void randomize(T& t) {
    std::uniform_int_distribution<long long> distr(
        std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    t = static_cast<T>(distr(gen));
}

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value &&
                                               !std::is_signed<T>::value,
                                           bool>::type>
void randomize(T& t) {
    std::uniform_int_distribution<unsigned long long> distr(
        std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    t = static_cast<T>(distr(gen));
}

template <class T, typename std::enable_if<std::is_floating_point<T>::value,
                                           bool>::type>
void randomize(T& t) {
    std::uniform_real_distribution<long double> distr(
        std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    t = static_cast<T>(distr(gen));
}

template <class T, typename std::enable_if<std::is_same<T, bool>::value,
                                           bool>::type>
void randomize(T& t) {
    std::uniform_int_distribution<int> distr(0, 1);
    t = static_cast<bool>(distr(gen));
}

template <class T>
auto randomize(T& t)
    -> decltype(t.randomize()) {
    t.randomize();
}

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type> 
auto randomize(T& arr)
    -> decltype(arr.fill(std::declval<typename T::value_type>())) {
    for (auto&& item : arr) {
        bool val;
        randomize(val);
        item = val;
    }
}

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type>
auto randomize(T& arr)
    -> decltype(arr.fill(std::declval<typename T::value_type>())) {
    for (auto& value : arr) {
        randomize(value);
    }
}

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type> 
auto randomize(T& seq)
    -> decltype(seq.resize(std::declval<std::size_t>())) {
    seq.clear();
    seq.resize(randomSize());
    for (auto&& item : seq) {
        bool val;
        randomize(val);
        item = val;
    }
}

void randomize(QString& s) {
    s.clear();
    s.resize(randomSize());
    for (auto& value : s) {
        randomize(value.unicode());
    }
}

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type> 
auto randomize(T& seq)
    -> decltype(seq.resize(std::declval<std::size_t>())) {
    seq.clear();
    seq.resize(randomSize());
    for (auto& value : seq) {
        randomize(value);
    }
}

template <class T>
auto randomize(T& set)
    -> decltype(set.insert(std::declval<typename T::value_type>()), void()) {
    set.clear();
    size_t size = randomSize();

    for (size_t i = 0; i < size; i++) {
        typename T::value_type value;
        randomize(value);
        set.insert(std::move(value));
    }
}

template <class T1, class T2>
void randomize(std::pair<T1, T2>& p) {
    randomize(p.first);
    randomize(p.second);
}

template <class T1, class T2>
void randomize(std::pair<const T1, T2>& p) {
    randomize(*const_cast<T1*>(&p.first));
    randomize(p.second);
}

template <class Type> void randomizeVariadic(Type& t) {
    randomize(t);
}

template <class Type, class... Types>
void randomizeVariadic(Type& t, Types&... ts) {
    randomizeVariadic(t);
    randomizeVariadic(ts...);
}
} // namespace TestFunctions
