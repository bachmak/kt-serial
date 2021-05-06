#pragma once

#include <unordered_set>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/unordered_set.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::unordered_set.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar, const std::unordered_set<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::saveUnorderedSet(ar, set);
}

/**
 * @brief Перегрузка функции для сериализации контейнера std::unordered_multiset.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar,
    const std::unordered_multiset<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::saveUnorderedSet(ar, set);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::unordered_set.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar, std::unordered_set<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::loadUnorderedSet(ar, set);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::unordered_multiset.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar,
    std::unordered_multiset<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::loadUnorderedSet(ar, set);
}
} // namespace KtSerial

