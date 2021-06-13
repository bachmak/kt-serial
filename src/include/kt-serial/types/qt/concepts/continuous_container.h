#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации контейнеров, хранящих
 * данные непрерывно (строки и векторы с элементами базовых типов).
 *
 * @tparam Container тип сериализуемого контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на выходной архив
 * @param ссылка на сериализуемый контейнер
 */
template <class Container, class Archive>
void saveContinuousContainer(Archive& ar, const Container& con) {
    ar << makeSizeWrapper(con.size())
       << makeDataWrapper(con.data(), static_cast<SizeType>(con.size()));
}

/**
 * @brief Обобщенная перегрузка функции для десериализации контейнеров, хранящих
 * данные непрерывно (строки и векторы с элементами базовых типов).
 *
 * @tparam Container тип десериализуемого контейнера
 * @tparam Archive тип входного архива
 * @param ar ссылка на входной архив
 * @param ссылка на десериализуемый контейнер
 */
template <class Container, class Archive>
void loadContinuousContainer(Archive& ar, Container& con) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    con.resize(size);
    ar >> makeDataWrapper(con.data(), static_cast<SizeType>(size));
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
