#pragma once

#include <QVector>

#include "kt-serial/types/details/common.h"
#include "kt-serial/types/qt/concepts/continuous_container.h"
#include "kt-serial/types/qt/concepts/value_only_container.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации контейнера QVector, элементы
 * которого удовлетворяют условию std::is_arithmetic.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param vec сериализуемый контейнер
 */
template <class T, class Archive,
          Traits::EnableIf<std::is_arithmetic<T>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QVector<T>& vec) {
    QtConcepts::saveContinuousContainer(ar, vec);
}

/**
 * @brief Перегрузка функции для сериализации контейнера QVector, элементы
 * которого не удовлетворяют условию std::is_arithmetic.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param vec сериализуемый контейнер
 */
template <class T, class Archive,
          Traits::EnableIf<!std::is_arithmetic<T>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QVector<T>& vec) {
    QtConcepts::saveValueOnlyContainer(ar, vec);
}

/**
 * @brief Перегрузка функции для десериализации контейнера QVector, элементы
 * которого удовлетворяют условию std::is_arithmetic.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param vec десериализуемый контейнер
 */
template <class T, class Archive,
          Traits::EnableIf<std::is_arithmetic<T>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QVector<T>& vec) {
    QtConcepts::loadContinuousContainer(ar, vec);
}

/**
 * @brief Перегрузка функции для десериализации контейнера QVector, элементы
 * которого не удовлетворяют условию std::is_arithmetic.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param vec десериализуемый контейнер
 */
template <class T, class Archive,
          Traits::EnableIf<!std::is_arithmetic<T>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QVector<T>& vec) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    vec.resize(size);

    for (auto& elem : vec) {
        ar >> elem;
    }
}
} // namespace Details
} // namespace KtSerial
