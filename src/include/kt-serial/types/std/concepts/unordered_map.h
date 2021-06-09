#pragma once

#include "kt-serial/details/wrappers/key_value_wrapper.h"
#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace StdConcepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации неупорядоченных
 * ассоциативных контейнеров стандартной библиотеки, реализующих структуру типа
 * словарь (unordered_map, unordered_multimap).
 *
 * @tparam Archive тип выходного архива
 * @tparam UnorderedMap тип сериализуемого контейнера (std::unordered_map или
 * std::unordered_multimap)
 * @param ar ссылка на выходной архив
 * @param map ссылка на сериализуемый контейнер
 */
template <class Archive, class UnorderedMap>
void saveUnorderedMap(Archive& ar, const UnorderedMap& map) {
    ar << makeSizeWrapper(map.size()) << makeSizeWrapper(map.bucket_count());

    for (const auto& item : map) {
        auto wrapper = makeKeyValueWrapper(item.first, item.second);
        ar << wrapper;
    }
}

/**
 * @brief Обобщенная перегрузка функции для десериализации неупорядоченных
 * ассоциативных контейнеров стандартной библиотеки, реализующих структуру типа
 * словарь (unordered_map, unordered_multimap).
 *
 * @tparam Archive тип входного архива
 * @tparam UnorderedMap тип десериализуемого контейнера (std::unordered_map или
 * std::unordered_multimap)
 * @param ar ссылка на входной архив
 * @param map ссылка на десериализуемый контейнер
 */
template <class Archive, class UnorderedMap>
void loadUnorderedMap(Archive& ar, UnorderedMap& map) {
    SizeType size, bucketCount;
    ar >> makeSizeWrapper(size) >> makeSizeWrapper(bucketCount);

    map.clear();
    map.rehash(bucketCount);

    for (SizeType i = 0; i < size; i++) {
        typename UnorderedMap::key_type key;
        typename UnorderedMap::mapped_type value;
        auto wrapper = makeKeyValueWrapper(key, value);
        ar >> wrapper;
        map.insert(std::make_pair(std::move(key), std::move(value)));
    }
}
} // namespace StdConcepts
} // namespace Details
} // namespace KtSerial
