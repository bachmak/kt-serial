#pragma once

#include <limits>
#include <type_traits>
#include <utility>

namespace TestFunctions {
template <class T, typename std::enable_if<std::is_arithmetic<T>::value,
                                           bool>::type = true>
void clear(T& t);

template <class T> auto clear(T& t) -> decltype(t.clear(), void());

template <class K, class V> void clear(std::pair<K, V>& p);

template <class T, std::size_t Size> void clear(std::array<T, Size>& arr);

template <class T> void clearVariadic(T& t);

template <class T, class... Ts> void clearVariadic(T& t, Ts&... ts);
} // namespace TestFunctions

#include "test_helpers/clear.hpp"