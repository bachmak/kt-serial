#pragma once

#include <random>
#include <type_traits>

#include <QtCore>

namespace TestFunctions {
std::mt19937 gen;
std::size_t maxSize = 100;

std::size_t randomSize(std::size_t maxValue = maxSize);

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value &&
                                               std::is_signed<T>::value,
                                           bool>::type = true>
void randomize(T& t);

template <class T, typename std::enable_if<std::is_integral<T>::value &&
                                               !std::is_same<T, bool>::value &&
                                               !std::is_signed<T>::value,
                                           bool>::type = true>
void randomize(T& t);

template <class T, typename std::enable_if<std::is_floating_point<T>::value,
                                           bool>::type = true>
void randomize(T& t); 

template <class T, typename std::enable_if<std::is_same<T, bool>::value,
                                           bool>::type = true>
void randomize(T& t); 

template <class T>
auto randomize(T& t)
    -> decltype(t.randomize());

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& arr)
    -> decltype(arr.fill(std::declval<typename T::value_type>()));

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& arr)
    -> decltype(arr.fill(std::declval<typename T::value_type>()));

template <class T, typename std::enable_if<
                       std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& seq)
    -> decltype(seq.resize(std::declval<std::size_t>()));

template <class T, typename std::enable_if<
                       !std::is_same<typename T::value_type, bool>::value,
                       bool>::type = true>
auto randomize(T& seq)
    -> decltype(seq.resize(std::declval<std::size_t>())); 

template <class T>
auto randomize(T& set)
    -> decltype(set.insert(std::declval<typename T::value_type>()), void()); 

template <class T1, class T2>
void randomize(std::pair<T1, T2>& p); 

template <class T1, class T2>
void randomize(std::pair<const T1, T2>& p); 

void randomize(QString& s);

template <class K, class V>
void randomize(QHash<K, V>& h);

template <class T>
void randomize(QLinkedList<T>& ll);

template <class T>
void randomize(QList<T>& l);

template <class K, class V>
void randomize(QMap<K, V>& m);

template <class K, class V>
void randomize(QMultiHash<K, V>& mh);

template <class K, class V>
void randomize(QMultiMap<K, V>& mm);

template <class T>
void randomize(QSet<T>& s);

template <class T>
void randomize(QVector<T>& v);

template <class Type> void randomizeVariadic(Type& t);

template <class Type, class... Types>
void randomizeVariadic(Type& t, Types&... ts); 
} // namespace TestFunctions

#include "random.hpp"
