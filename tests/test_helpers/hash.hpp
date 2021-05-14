#pragma once

#include "test_helpers/hash.h"
#include <boost/functional/hash.hpp>

namespace TestFunctions {

std::size_t pow(std::size_t x, std::size_t y) {
    if (y == 1) {
        return x;
    }
    if (y == 0) {
        return 1;
    }
    return x * pow(x, y - 1);
}

template <class T>
typename std::enable_if<HasHashCodeMethod<T>::value, std::size_t>::type
hashCode(const T& t) {
    return t.hashCode();
}

template <class T>
typename std::enable_if<!HasHashCodeMethod<T>::value, std::size_t>::type
hashCode(const T& t) {
    return boost::hash_value(t);
}

template <class Type, class... Types>
std::size_t hashCode(const Type& t, const Types&... ts) {
    std::size_t p = sizeof...(Types) + 1;
    return hashCode(t) * pow(997u, p) + hashCode(ts...);
}
} // namespace TestFunctions

namespace std {
template <class T, class H, class C, class A>
bool operator<(const std::unordered_set<T, H, C, A>& lhs,
               const std::unordered_set<T, H, C, A>& rhs) {
    return std::vector<T>(lhs.begin(), lhs.end()) <
           std::vector<T>(rhs.begin(), rhs.end());
}
template <class T, class H, class C, class A>
bool operator<(const std::unordered_multiset<T, H, C, A>& lhs,
               const std::unordered_multiset<T, H, C, A>& rhs) {
    return std::vector<T>(lhs.begin(), lhs.end()) <
           std::vector<T>(rhs.begin(), rhs.end());
}

template <class K, class T, class H, class C, class A>
bool operator<(const std::unordered_map<K, T, H, C, A>& lhs,
               const std::unordered_map<K, T, H, C, A>& rhs) {
    return std::map<K, T>(lhs.begin(), lhs.end()) <
           std::map<K, T>(rhs.begin(), rhs.end());
}
template <class K, class T, class H, class C, class A>
bool operator<(const std::unordered_multimap<K, T, H, C, A>& lhs,
               const std::unordered_multimap<K, T, H, C, A>& rhs) {
    return std::multimap<K, T>(lhs.begin(), lhs.end()) <
           std::multimap<K, T>(rhs.begin(), rhs.end());
}
} // namespace std

namespace boost {
template <class T, class A>
std::size_t hash_value(const std::forward_list<T, A>& t) {
    std::vector<T> temp(t.begin(), t.end());
    return boost::hash_value(temp);
}

template <class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_set<T, H, E, A>& set) {
    std::vector<T> temp(set.begin(), set.end());
    return boost::hash_value(temp);
}

template <class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_multiset<T, H, E, A>& set) {
    std::vector<T> temp(set.begin(), set.end());
    return boost::hash_value(temp);
}

template <class K, class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_map<K, T, H, E, A>& map) {
    return boost::hash_value(std::map<K, T>(map.begin(), map.end()));
}

template <class K, class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_multimap<K, T, H, E, A>& map) {
    return boost::hash_value(std::multimap<K, T>(map.begin(), map.end()));
}
} // namespace boost