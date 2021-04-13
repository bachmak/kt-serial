#pragma once

#include <type_traits>
#include <vector>

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/wrappers.h"
#include "kt-serial/macros.h"

namespace KtSerial {
/**
 * @brief Перегрузка функции для сериализации контейнера std::vector, элементы
 * которого удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определена функция сериализации класса-обертки DataWrapper над
 * элементами типа T).
 *
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param vec сериализуемый контейнер
 */
template <class T, class Alloc, class Archive,
          Traits::ConjunctiveEnableIf<std::is_arithmetic<T>::value,
                                      Traits::HasExactlyOneOutputHandler<
                                          DataWrapper<T>, Archive>::value,
                                      !std::is_same<T, bool>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::vector<T, Alloc>& vec) {
    ar << makeSizeWrapper(vec.size())
       << makeDataWrapper(vec.data(), vec.size());
}

/**
 * @brief Перегрузка функции для сериализации контейнера std::vector, элементы
 * которого не удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определены метод/функция сериализации элементов типа T
 * непосредственно).
 *
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param vec сериализуемый контейнер
 */
template <class T, class Alloc, class Archive,
          Traits::ConjunctiveEnableIf<
              !std::is_arithmetic<T>::value,
              Traits::HasExactlyOneOutputHandler<T, Archive>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::vector<T, Alloc>& vec) {
    ar << makeSizeWrapper(vec.size());

    for (const auto& value : vec) {
        ar << value;
    }
}

/**
 * @brief Перегрузка функции для сериализации контейнера std::vector с
 * элементами булевого типа.
 *
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param vec сериализуемый контейнер
 */
template <class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::vector<bool, Alloc>& vec) {
    ar << makeSizeWrapper(vec.size());

    for (const auto& value : vec) {
        ar << static_cast<bool>(value);
    }
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::vector, элементы
 * которого удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определена функция десериализации класса-обертки DataWrapper
 * над элементами типа T).
 *
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param vec десериализуемый контейнер
 */
template <class T, class Alloc, class Archive,
          Traits::ConjunctiveEnableIf<
              std::is_arithmetic<T>::value,
              Traits::HasExactlyOneInputHandler<DataWrapper<T>, Archive>::value,
              !std::is_same<T, bool>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::vector<T, Alloc>& vec) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    vec.resize(size);
    ar >> makeDataWrapper(const_cast<T*>(vec.data()), size);
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::vector, элементы
 * которого не удовлетворяют условию std::is_arithmetic (при условии, что для
 * данного архива определены метод/функция десериализации элементов типа T
 * непосредственно).
 *
 * @tparam T тип элементов контейнера
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param vec десериализуемый контейнер
 */
template <class T, class Alloc, class Archive,
          Traits::ConjunctiveEnableIf<
              !std::is_arithmetic<T>::value,
              Traits::HasExactlyOneInputHandler<T, Archive>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::vector<T, Alloc>& vec) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    vec.resize(size);

    for (auto& value : vec) {
        ar >> value;
    }
}

/**
 * @brief Перегрузка функции для десериализации контейнера std::vector с
 * элементами булевого типа.
 *
 * @tparam Alloc аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param vec десериализуемый контейнер
 */
template <class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::vector<bool, Alloc>& vec) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    vec.resize(size);

    for (auto&& value : vec) {
        bool boolValue;
        ar >> boolValue;
        value = boolValue;
    }
}
} // namespace KtSerial
