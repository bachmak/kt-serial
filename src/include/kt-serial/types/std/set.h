#pragma once

#include <set>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/set.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::set.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::set<Key, Compare, Alloc>& set) {
    Concepts::saveSet(ar, set);
}

/**
 * @brief Перегрузка функции для сериализации контейнера std::multiset.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::multiset<Key, Compare, Alloc>& set) {
    Concepts::saveSet(ar, set);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::set.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @param ar ссылка на архив
 * @param set десериализуемый контейнер
 */
template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::set<Key, Compare, Alloc>& set) {
    Concepts::loadSet(ar, set);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::multiset.
 * 
 * @tparam Key тип элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @param ar ссылка на архив
 * @param set десериализуемый контейнер
 */
template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::multiset<Key, Compare, Alloc>& set) {
    Concepts::loadSet(ar, set);
}
} // namespace KtSerial
