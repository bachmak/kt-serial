#pragma once

#include <deque>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/resizable_sequence.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::deque. Так как
 * std::deque не хранится в памяти непрерывно, элементы сериализуются по
 * отдельности.
 *
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param deq сериализуемый контейнер
 */
template <class T, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::deque<T, Alloc>& deq) {
    Concepts::saveResizableSequence(ar, deq);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::deque. Так как
 * std::deque не хранится в памяти непрерывно, элементы десериализуются по
 * отдельности.
 *
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param deq десериализуемый контейнер
 */
template <class T, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::deque<T, Alloc>& deq) {
    Concepts::loadResizableSequence(ar, deq);
}
} // namespace KtSerial
