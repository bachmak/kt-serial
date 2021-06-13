#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
/**
 * @brief Обобщенная перегрузка для сериализации контейнеров Qt, хранящих
 * значения в паре с соответствующими ключами.
 *
 * @tparam Container тип сериализуемого контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на выходной архив
 * @param con ссылка на сериализуемый контейнер
 */
template <class Container, class Archive>
void saveKeyValueContainer(Archive& ar, const Container& con) {
    ar << makeSizeWrapper(con.size());

    for (auto it = con.constBegin(); it != con.constEnd(); ++it) {
        ar << makeKeyValueWrapper(it.key(), it.value());
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
