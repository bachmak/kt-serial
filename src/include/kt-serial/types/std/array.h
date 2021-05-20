#pragma once

#include <array>

#include "kt-serial/types/details/common.h"
#include "kt-serial/types/std/concepts/const_size_sequence.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::array, элементы
 * которого удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определена функция сериализации класса-обертки DataWrapper над
 * элементами типа T).
 *
 * @tparam T тип элементов контейнера
 * @tparam N размер контейнера
 * @tparam Archive класс архива для сериализации
 * @param ar сслыка на архив
 * @param arr сериализуемый контейнер
 */
template <
    class T, std::size_t N, class Archive,
    Traits::ConjunctiveEnableIf<std::is_arithmetic<T>::value,
                                Traits::HasExactlyOneOutputHandler<
                                    DataWrapper<T>, Archive>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::array<T, N>& arr) {
    ar << makeDataWrapper(arr.data(), arr.size());
}

/**
 * @brief Перегрузка функции для сериализации контейнера std::array, элементы
 * которого не удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определены метод/функция сериализации элементов типа T
 * непосредственно).
 *
 * @tparam T тип элементов контейнера
 * @tparam N размер контейнера
 * @tparam Archive класс архива для сериализации
 * @param ar сслыка на архив
 * @param arr сериализуемый контейнер
 */
template <class T, std::size_t N, class Archive,
          Traits::ConjunctiveEnableIf<
              !std::is_arithmetic<T>::value,
              Traits::HasExactlyOneOutputHandler<T, Archive>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::array<T, N>& arr) {
    Concepts::saveConstSizeSequence(ar, arr);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::array, элементы
 * которого удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определена функция десериализации класса-обертки DataWrapper
 * над элементами типа T).
 *
 * @tparam T тип элементов контейнера
 * @tparam N размер контейнера
 * @tparam Archive класс архива для десериализации
 * @param ar сслыка на архив
 * @param arr десериализуемый контейнер
 */
template <
    class T, std::size_t N, class Archive,
    Traits::ConjunctiveEnableIf<std::is_arithmetic<T>::value,
                                Traits::HasExactlyOneInputHandler<
                                    DataWrapper<T>, Archive>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::array<T, N>& arr) {
    ar >> makeDataWrapper(const_cast<T*>(arr.data()), arr.size());
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::array, элементы
 * которого не удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определены метод/функция десериализации элементов типа T
 * непосредственно).
 *
 * @tparam T тип элементов контейнера
 * @tparam N размер контейнера
 * @tparam Archive класс архива для десериализации
 * @param ar сслыка на архив
 * @param arr десериализуемый контейнер
 */
template <class T, std::size_t N, class Archive,
          Traits::ConjunctiveEnableIf<
              !std::is_arithmetic<T>::value,
              Traits::HasExactlyOneInputHandler<T, Archive>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::array<T, N>& arr) {
    Concepts::loadConstSizeSequence(ar, arr);
}
} // namespace KtSerial
