#pragma once

#include <QMultiHash>

#include "kt-serial/types/qt/concepts/hash.h"
#include "kt-serial/types/qt/concepts/key_value_container.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации контейнера QMultiHash.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param hash сериализуемый контейнер
 */
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMultiHash<Key, T>& hash) {
    QtConcepts::saveKeyValueContainer(ar, hash);
}

/**
 * @brief Перегрузка функции для десериализации контейнера QMultiHash.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param hash десериализуемый контейнер
 */
template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMultiHash<Key, T>& hash) {
    QtConcepts::loadHash(ar, hash);
}
} // namespace Details
} // namespace KtSerial
