#pragma once

#include <map>

#include "kt-serial/types/std/concepts/map.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::map.
 * 
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param map сериализуемый контейнер
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar,
                            const std::map<Key, T, Compare, Alloc>& map) {
    Concepts::saveMap(ar, map);
}

/**
 * @brief Перегрузка функции для сериализации контейнера std::multimap.
 * 
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param map сериализуемый контейнер
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar,
                            const std::multimap<Key, T, Compare, Alloc>& map) {
    Concepts::saveMap(ar, map);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::map.
 * 
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param map десериализуемый контейнер
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar,
                            std::map<Key, T, Compare, Alloc>& map) {
    Concepts::loadMap(ar, map);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::multimap.
 * 
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Compare компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param map десериализуемый контейнер
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar,
                            std::multimap<Key, T, Compare, Alloc>& map) {
    Concepts::loadMap(ar, map);
}
} // namespace KtSerial
