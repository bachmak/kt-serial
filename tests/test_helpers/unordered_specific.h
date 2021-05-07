#pragma once

#include <boost/functional/hash.hpp>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    return hash_value(temp);
}

template <class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_set<T, H, E, A>& set) {
    std::vector<T> temp(set.begin(), set.end());
    return hash_value(temp);
}

template <class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_multiset<T, H, E, A>& set) {
    std::vector<T> temp(set.begin(), set.end());
    return hash_value(temp);
}

template <class K, class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_map<K, T, H, E, A>& map) {
    return hash_value(std::map<K, T>(map.begin(), map.end()));
}

template <class K, class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_multimap<K, T, H, E, A>& map) {
    return hash_value(std::multimap<K, T>(map.begin(), map.end()));
}
} // namespace boost
