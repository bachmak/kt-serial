#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
/**
 * @brief Обобщенная перегрузка для сериализации контейнеров Qt, хранящих
 * значения без связанных с ними ключей.
 *
 * @tparam Container тип сериализуемого контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на выходной архив
 * @param con ссылка на сериализуемый контейнер
 */
template <class Container, class Archive>
void saveValueOnlyContainer(Archive& ar, const Container& con) {
    ar << makeSizeWrapper(con.size());

    for (const auto& value : con) {
        ar << value;
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
