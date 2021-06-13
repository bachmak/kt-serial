#pragma once

#include <QList>

#include "kt-serial/types/details/common.h"
#include "kt-serial/types/qt/concepts/value_only_container.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации контейнера QList.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param lst сериализуемый контейнер
 */
template <class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QList<T>& lst) {
    QtConcepts::saveValueOnlyContainer(ar, lst);
}

/**
 * @brief Перегрузка функции для десериализации контейнера QList.
 *
 * @tparam T тип элементов контейнера
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param lst десериализуемый контейнер
 */
template <class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QList<T>& lst) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    lst.reserve(size);

    for (SizeType i = 0; i < size; ++i) {
        T elem;
        ar >> elem;
        lst.append(elem);
    }
}
} // namespace Details
} // namespace KtSerial
