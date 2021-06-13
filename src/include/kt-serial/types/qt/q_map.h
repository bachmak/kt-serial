#pragma once

#include <QMap>

#include "kt-serial/types/qt/concepts/key_value_container.h"
#include "kt-serial/types/qt/concepts/map.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации контейнера QMap.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param map сериализуемый контейнер
 */
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMap<Key, T>& map) {
    QtConcepts::saveKeyValueContainer(ar, map);
}

/**
 * @brief Перегрузка функции для десериализации контейнера QMap.
 *
 * @tparam Key тип ключа элементов контейнера
 * @tparam T тип значения элементов контейнера
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param map десериализуемый контейнер
 */
template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMap<Key, T>& map) {
    QtConcepts::loadMap(ar, map);
}
} // namespace Details
} // namespace KtSerial
