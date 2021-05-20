#pragma once

#include <unordered_map>

#include "kt-serial/types/std/concepts/unordered_map.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации контейнера std::unordered_map.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param map сериализуемый контейнер
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar, const std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::saveUnorderedMap(ar, map);
}

/**
 * @brief Перегрузка функции для сериализации контейнера
 * std::unordered_multimap.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param map сериализуемый контейнер
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar,
    const std::unordered_multimap<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::saveUnorderedMap(ar, map);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::unordered_map.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param map десериализуемый контейнер
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar, std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::loadUnorderedMap(ar, map);
}

/**
 * @brief Перегрузка функции для десериализации контейнера
 * std::unordered_multimap.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Hash хэш-функция
 * @tparam KeyEqual компаратор
 * @tparam Alloc аллокатор
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param map десериализуемый контейнер
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar, std::unordered_multimap<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::loadUnorderedMap(ar, map);
}
} // namespace Details
} // namespace KtSerial
