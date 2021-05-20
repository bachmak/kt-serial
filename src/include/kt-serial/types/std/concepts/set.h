#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace Concepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации ассоциативных
 * контейнеров стандартной библиотеки, реализующих структуру типа множество
 * (set, multiset).
 *
 * @tparam Archive тип выходного архива
 * @tparam Set тип сериализуемого контейнера (std::set или std::multiset)
 * @param ar ссылка на выходной архив
 * @param seq ссылка на сериализуемый контейнер
 */
template <class Archive, class Set> void saveSet(Archive& ar, const Set& set) {
    ar << makeSizeWrapper(set.size());

    for (const auto& elem : set) {
        ar << elem;
    }
}

/**
 * @brief Обобщенная перегрузка функции для десериализации ассоциативных
 * контейнеров стандартной библиотеки, реализующих структуру типа множество
 * (set, multiset).
 *
 * @tparam Archive тип входного архива
 * @tparam Set тип десериализуемого контейнера (std::set или std::multiset)
 * @param ar ссылка на входной архив
 * @param seq ссылка на десериализуемый контейнер
 */
template <class Archive, class Set> void loadSet(Archive& ar, Set& set) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    set.clear();
    auto hint = set.begin();

    for (SizeType i = 0; i < size; i++) {
        typename Set::key_type elem;
        ar >> elem;
        hint = set.insert(hint, std::move(elem));
    }
}
} // namespace Concepts
} // namespace Details
} // namespace KtSerial
