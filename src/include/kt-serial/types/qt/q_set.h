#pragma once

#include <QSet>

#include "kt-serial/types/details/common.h"
#include "kt-serial/types/qt/concepts/value_only_container.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации контейнера QSet.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на архив
 * @param set сериализуемый контейнер
 */
template <class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QSet<T>& set) {
    QtConcepts::saveValueOnlyContainer(ar, set);
}

/**
 * @brief Перегрузка функции для десериализации контейнера QSet.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive тип входного архива
 * @param ar ссылка на архив
 * @param set десериализуемый контейнер
 */
template <class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QSet<T>& set) {
    SizeType size;
    ar >> makeSizeWrapper(size);

    set.clear();
    set.reserve(size);

    for (SizeType i = 0; i < size; ++i) {
        T elem;
        ar >> elem;
        set.insert(elem);
    }
}
} // namespace Details
} // namespace KtSerial
