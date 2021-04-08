#pragma once

#include <cstdint>
#include <utility>

#include "kt-serial/details/basic_traits.h"

namespace KtSerial
{
/**
 * Класс-обертка над бинарными данными, которые можно сериализовать как
 * непрерывную байтовую последовательность. Используется для передачи данных
 * из функций, описывающих процедуру сериализации стандартных типов, в
 * методы различных архивов (по-разному реализующих сериализацию).
 * @tparam Type тип сериализуемых данных
 */ 
template <class Type>
struct DataWrapper
{
    using type = Traits::VoidPointerKeepingConst<Type>;

    type data;
    uint64_t size;
};

template <class Type>
DataWrapper<Type> makeDataWrapper(Type&& data, uint64_t size)
{
    return { std::forward<Type>(data), size };
}

/**
 * Класс-обертка над значением размера сериализуемых контейнеров. Используется
 * для унификации передачи данных о размере контейнера из функций, описывающих
 * процедуру сериализации стандартных типов, в методы различных архивов
 * (по-разному реализующих сериализацю).
 */
struct SizeWrapper
{
    uint64_t size;
};

SizeWrapper makeSizeWrapper(uint64_t size)
{
    return { size };
}
} // namespace KtSerial
