#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace Concepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации последовательных
 * контейнеров стандартной библиотеки, имеющих переменную длину.
 *
 * @tparam Archive тип выходного архива
 * @tparam Sequence тип сериализуемого контейнера
 * @param ar ссылка на выходной архив
 * @param seq ссылка на сериализуемый контейнер
 */
template <class Sequence, class Archive>
void saveResizableSequence(Archive& ar, const Sequence& seq) {
    ar << makeSizeWrapper(std::distance(seq.begin(), seq.end()));

    for (const auto& value : seq) {
        ar << value;
    }
}

/**
 * @brief Обобщенная перегрузка функции для десериализации последовательных
 * контейнеров стандартной библиотеки, имеющих переменную длину.
 *
 * @tparam Archive тип входного архива
 * @tparam Sequence тип десериализуемого контейнера
 * @param ar ссылка на входной архив
 * @param seq ссылка на десериализуемый контейнер
 */
template <class Sequence, class Archive>
void loadResizableSequence(Archive& ar, Sequence& seq) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    seq.resize(size);

    for (auto& value : seq) {
        ar >> value;
    }
}
} // namespace Concepts
} // namespace Details
} // namespace KtSerial
