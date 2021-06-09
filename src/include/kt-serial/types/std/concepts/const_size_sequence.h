#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace StdConcepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации последовательных
 * контейнеров стандартной библиотеки, имеющих постоянную длину.
 *
 * @tparam Archive тип выходного архива
 * @tparam Sequence тип сериализуемого контейнера
 * @param ar ссылка на выходной архив
 * @param seq ссылка на сериализуемый контейнер
 */
template <class Archive, class Sequence>
void saveConstSizeSequence(Archive& ar, const Sequence& seq) {
    for (const auto& value : seq) {
        ar << value;
    }
}

/**
 * @brief Обобщенная перегрузка функции для десериализации последовательных
 * контейнеров стандартной библиотеки, имеющих постоянную длину.
 *
 * @tparam Archive тип входного архива
 * @tparam Sequence тип десериализуемого контейнера
 * @param ar ссылка на входной архив
 * @param seq ссылка на десериализуемый контейнер
 */
template <class Archive, class Sequence>
void loadConstSizeSequence(Archive& ar, Sequence& seq) {
    for (auto& value : seq) {
        ar >> value;
    }
}
} // namespace StdConcepts
} // namespace Details
} // namespace KtSerial
