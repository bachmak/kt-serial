#pragma once

#include <string>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации строк стандартной библиотеки:
 * string, wstring, u8string и т.д.
 * (https://en.cppreference.com/w/cpp/string/basic_string)
 *
 * @tparam CharT тип символа строки
 * @tparam TraitsT шаблонный тип, определяющий операции с типом CharT
 * @tparam AllocT аллокатор
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param str сериализумая строка
 */
template <
    class CharT, class TraitsT, class AllocT, class Archive,
    Traits::ConjunctiveEnableIf<std::is_arithmetic<CharT>::value,
                                Traits::HasExactlyOneOutputHandler<
                                    DataWrapper<CharT>, Archive>::value> = true>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar, const std::basic_string<CharT, TraitsT, AllocT>& str) {
    ar << makeSizeWrapper(str.size())
       << makeDataWrapper(str.data(), str.size());
}

/**
 * @brief Перегрузка функции для десериализации строк стандартной библиотеки:
 * string, wstring, u8string и т.д.
 * (https://en.cppreference.com/w/cpp/string/basic_string)
 *
 * @tparam CharT тип символа строки
 * @tparam TraitsT шаблонный тип, определяющий операции с типом CharT
 * @tparam AllocT аллокатор
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param str десериализумая строка
 */
template <
    class CharT, class TraitsT, class AllocT, class Archive,
    Traits::ConjunctiveEnableIf<std::is_arithmetic<CharT>::value,
                                Traits::HasExactlyOneInputHandler<
                                    DataWrapper<CharT>, Archive>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar,
                            std::basic_string<CharT, TraitsT, AllocT>& str) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    str.resize(size);
    ar >> makeDataWrapper(const_cast<CharT*>(str.data()), str.size());
}
} // namespace Details
} // namespace KtSerial
