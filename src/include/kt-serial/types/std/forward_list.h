#pragma once

#include <forward_list>

#include "kt-serial/types/common.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::forward_list.
 * 
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param lst сериализуемый контейнер
 */
template <class T, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar,
                            const std::forward_list<T, Alloc>& lst) {
    ar << makeSizeWrapper(std::distance(lst.begin(), lst.end()));

    for (const auto& elem : lst) {
        ar << elem;
    }
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::forward_list.
 * 
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param lst десериализуемый контейнер
 */
template <class T, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::forward_list<T, Alloc>& lst) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    lst.resize(size);

    for (auto& elem : lst) {
        ar >> elem;
    }
}

} // namespace KtSerial
