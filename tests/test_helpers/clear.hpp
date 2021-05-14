#pragma once

#include "test_helpers/clear.h"

namespace TestFunctions {
template <class T, typename std::enable_if<std::is_arithmetic<T>::value,
                                           bool>::type>
void clear(T& t) {
    t = std::numeric_limits<T>::denorm_min();
}

template <class T> auto clear(T& t) -> decltype(t.clear(), void()) {
    t.clear();
}

template <class K, class V> void clear(std::pair<K, V>& p) {
    clear(p.first);
    clear(p.second);
}

template <class T, std::size_t Size>
void clear(std::array<T, Size>& arr) {
    for (auto& elem : arr) {
        clear(elem);
    }
}

template <class T> void clearVariadic(T& t) { clear(t); }

template <class T, class... Ts> void clearVariadic(T& t, Ts&... ts) {
    clearVariadic(t);
    clearVariadic(ts...);
}

} // namespace TestFunctions
