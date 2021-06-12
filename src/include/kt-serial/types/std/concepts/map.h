#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace StdConcepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации ассоциативных
 * контейнеров стандартной бибиотеки, реализующих структуру типа словарь (map,
 * multimap).
 *
 * @tparam Archive тип выходного архива
 * @tparam Map тип сериализуемого контейнера (std::map или std::multimap)
 * @param ar ссылка на выходной архив
 * @param map ссылка на сериализуемый контейнер
 */
template <class Archive, class Map> void saveMap(Archive& ar, const Map& map) {
    ar << makeSizeWrapper(map.size());

    for (const auto& item : map) {
        ar << makeKeyValueWrapper(item.first, item.second);
    }
}

/**
 * @brief Обобщенная перегрузка функции для десериализации ассоциативных
 * контейнеров стандартной бибиотеки, реализующих структуру типа словарь (map,
 * multimap).
 *
 * @tparam Archive тип входного архива
 * @tparam Map тип десериализуемого контейнера (std::map или std::multimap)
 * @param ar ссылка на входной архив
 * @param map ссылка на десериализуемый контейнер
 */
template <class Archive, class Map> void loadMap(Archive& ar, Map& map) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    map.clear();
    auto hint = map.begin();

    for (SizeType i = 0; i < size; i++) {
        typename Map::key_type key;
        typename Map::mapped_type value;
        ar >>  makeKeyValueWrapper(key, value);
        hint = std::next(
            map.insert(hint, std::make_pair(std::move(key), std::move(value))));
    }
}
} // namespace StdConcepts
} // namespace Details
} // namespace KtSerial
