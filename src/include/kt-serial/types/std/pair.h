#pragma once

#include <utility>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации пар стандартной библиотеки
 * std::pair.
 *
 * @tparam T1 тип первого элемента пары
 * @tparam T2 тип второго элемента пары
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param p сериализуемая пара
 */
template <class T1, class T2, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::pair<T1, T2>& p) {
    ar << p.first << p.second;
}

/**
 * @brief Перегрузка функции для десериализации пар стандартной библиотеки
 * std::pair.
 *
 * @tparam T1 тип первого элемента пары
 * @tparam T2 тип второго элемента пары
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param p десериализуемая пара
 */
template <class Archive, class T1, class T2>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::pair<T1, T2>& p) {
    ar >> p.first >> p.second;
}
} // namespace Details
} // namespace KtSerial
