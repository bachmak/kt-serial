#pragma once

#include <deque>

#include "kt-serial/types/common.h"

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
    ar << makeSizeWrapper(deq.size());

    for (const auto& elem : deq) {
        ar << elem;
    }
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
    SizeType size;
    ar >> makeSizeWrapper(size);
    deq.resize(size);

    for (auto& elem : deq) {
        ar >> elem;
    }
}
} // namespace KtSerial
