#pragma once

#include <string>

#include "kt-serial/macros.h"
#include "kt-serial/details/serializable_traits.h"
#include "kt-serial/details/wrappers.h"

namespace KtSerial
{
using namespace Traits;

/**
 * Перегрузка функции для сериализации строк стандартной библиотеки:
 * string, wstring, u8string и т.д.
 * (https://en.cppreference.com/w/cpp/string/basic_string)
 * @param ar класс архива для сериализации
 * @param str сериализуемая строка
 */
template <
    class CharT, class TraitsT, class AllocT, class Archive,
    EnableIf<
        HasExactlyOneOutputHandler<DataWrapper<CharT>, Archive>::value
    > = true
>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar,
    const std::basic_string<CharT, TraitsT, AllocT>& str
)
{
    ar << makeSizeWrapper(str.size()) 
       << makeDataWrapper(str.data(), str.size() * sizeof(CharT));
}
} // namespace KtSerial
