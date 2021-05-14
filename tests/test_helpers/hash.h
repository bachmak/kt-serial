#pragma once

#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace TestFunctions {

template <class T> struct HasHashCodeMethod {
    template <class U>
    static auto check(int) -> decltype(std::declval<U&>.hashCode(), std::true_type{});

    template <class U>
    static std::false_type check(...);

    using checkType = decltype(check<T>(0));

    static const bool value =
        std::is_same<checkType, std::true_type>::value;
};

std::size_t pow(std::size_t x, std::size_t y);

template <class T>
typename std::enable_if<HasHashCodeMethod<T>::value, std::size_t>::type
hashCode(const T& t);

template <class T>
typename std::enable_if<!HasHashCodeMethod<T>::value, std::size_t>::type
hashCode(const T& t);

template <class Type, class... Types>
std::size_t hashCode(const Type& t, const Types&... ts);
} // namespace TestFunctions

namespace std {
template <class T, class H, class C, class A>
bool operator<(const std::unordered_set<T, H, C, A>& lhs,
               const std::unordered_set<T, H, C, A>& rhs);

template <class T, class H, class C, class A>
bool operator<(const std::unordered_multiset<T, H, C, A>& lhs,
               const std::unordered_multiset<T, H, C, A>& rhs);

template <class K, class T, class H, class C, class A>
bool operator<(const std::unordered_map<K, T, H, C, A>& lhs,
               const std::unordered_map<K, T, H, C, A>& rhs);

template <class K, class T, class H, class C, class A>
bool operator<(const std::unordered_multimap<K, T, H, C, A>& lhs,
               const std::unordered_multimap<K, T, H, C, A>& rhs);
} // namespace std

namespace boost {
template <class T, class A>
std::size_t hash_value(const std::forward_list<T, A>& t);

template <class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_set<T, H, E, A>& set);

template <class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_multiset<T, H, E, A>& set);

template <class K, class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_map<K, T, H, E, A>& map);

template <class K, class T, class H, class E, class A>
std::size_t hash_value(const std::unordered_multimap<K, T, H, E, A>& map);
} // namespace boost

#include "test_helpers/hash.hpp"
