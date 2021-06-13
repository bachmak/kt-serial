#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
/**
 * @brief Обобщенная перегрузка функции для сериализации ассоциативных
 * контейнеров бибиотеки Qt, реализующих структуру типа словарь.
 *
 * @tparam Map тип сериализуемого контейнера
 * @tparam Archive тип выходного архива
 * @param ar ссылка на выходной архив
 * @param map ссылка на сериализуемый контейнер
 */
template <class Map, class Archive> void loadMap(Archive& ar, Map& map) {
    SizeType size;
    ar >> makeSizeWrapper(size);

    map.clear();
    auto hint = map.begin();

    for (SizeType i = 0; i < size; ++i) {
        typename Map::key_type key;
        typename Map::mapped_type value;
        ar >> makeKeyValueWrapper(key, value);
        hint = map.insert(hint, key, value);
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
