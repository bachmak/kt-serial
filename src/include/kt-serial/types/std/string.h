#pragma once

#include <string>

#include "kt-serial/details/serializable_traits.h"
#include "kt-serial/details/wrappers.h"
#include "kt-serial/macros.h"

namespace KtSerial {
/**
 * Перегрузка функции для сериализации строк стандартной библиотеки:
 * string, wstring, u8string и т.д.
 * (https://en.cppreference.com/w/cpp/string/basic_string)
 * @param ar класс архива для сериализации
 * @param str сериализуемая строка
 */
template <class CharT, class TraitsT, class AllocT, class Archive,
          Traits::EnableIf<std::is_arithmetic<CharT>::value> = true>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar, const std::basic_string<CharT, TraitsT, AllocT>& str) {
    ar << makeSizeWrapper(str.size())
       << makeDataWrapper(str.data(), str.size() * sizeof(CharT));
}

template <class CharT, class TraitsT, class AllocT, class Archive,
          Traits::EnableIf<std::is_arithmetic<CharT>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar,
                            std::basic_string<CharT, TraitsT, AllocT>& str) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    str.resize(size);
    ar >> makeDataWrapper(const_cast<CharT*>(str.data()), size * sizeof(CharT));
}
} // namespace KtSerial
