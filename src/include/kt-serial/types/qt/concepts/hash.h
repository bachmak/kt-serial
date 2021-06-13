#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
/**
 * @brief Обобщенная перегрузка функции для десериализации неупорядоченных
 * ассоциативных контейнеров библиотеки Qt, реализующих хэш-таблицы.
 *
 * @tparam Hash тип десериализуемого контейнера
 * @tparam Archive тип входного архива
 * @param ar ссылка на входной архив
 * @param hash ссылка на десериализуемый контейнер
 */
template <class Hash, class Archive> void loadHash(Archive& ar, Hash& hash) {
    SizeType size;
    ar >> makeSizeWrapper(size);

    hash.clear();
    hash.reserve(size);

    for (SizeType i = 0; i < size; ++i) {
        typename Hash::key_type key;
        typename Hash::mapped_type value;
        ar >> makeKeyValueWrapper(key, value);
        hash.insert(key, value);
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
