#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial {
namespace Concepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации неупорядоченных
 * ассоциативных контейнеров стандартной библиотеки, реализующих структуру типа
 * множество (unordered_set, unordered_multiset).
 *
 * @tparam Archive тип выходного архива
 * @tparam UnorderedSet тип сериализуемого контейнера (std::unordered_set или
 * std::unordered_multiset)
 * @param ar ссылка на выходной архив
 * @param set ссылка на сериализуемый контейнер
 */
template <class Archive, class UnorderedSet>
void saveUnorderedSet(Archive& ar, const UnorderedSet& set) {
    ar << makeSizeWrapper(set.size()) << makeSizeWrapper(set.bucket_count());

    for (const auto& elem : set) {
        ar << elem;
    }
}

/**
 * @brief Обобщенная перегрузка функции для десериализации неупорядоченных
 * ассоциативных контейнеров стандартной библиотеки, реализующих структуру типа
 * множество (unordered_set, unordered_multiset).
 *
 * @tparam Archive тип входного архива
 * @tparam UnorderedSet тип десериализуемого контейнера (std::unordered_set или
 * std::unordered_multiset)
 * @param ar ссылка на входной архив
 * @param set ссылка на десериализуемый контейнер
 */
template <class Archive, class UnorderedSet>
void loadUnorderedSet(Archive& ar, UnorderedSet& set) {
    SizeType size, bucketCount;
    ar >> makeSizeWrapper(size) >> makeSizeWrapper(bucketCount);

    set.clear();
    set.rehash(bucketCount);

    for (SizeType i = 0; i < size; i++) {
        typename UnorderedSet::key_type key;

        ar >> key;
        set.insert(std::move(key));
    }
}
} // namespace Concepts
} // namespace KtSerial
