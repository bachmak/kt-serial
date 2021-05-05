#pragma once

#include <list>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/resizable_sequence.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::list.
 * 
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param lst сериализуемый контейнер
 */
template <class T, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::list<T, Alloc>& lst) {
    Concepts::saveResizableSequence(ar, lst);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::list.
 * 
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param lst десериализуемый контейнер
 */
template <class T, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::list<T, Alloc>& lst) {
    Concepts::loadResizableSequence(ar, lst);
}

} // namespace KtSerial
