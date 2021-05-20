#pragma once

#include <forward_list>

#include "kt-serial/types/std/concepts/resizable_sequence.h"

namespace KtSerial {
namespace Details {
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
    Concepts::saveResizableSequence(ar, lst);
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
    Concepts::loadResizableSequence(ar, lst);
}
} // namespace Details
} // namespace KtSerial
