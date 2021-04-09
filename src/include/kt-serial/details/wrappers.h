#pragma once

#include <utility>

#include "kt-serial/details/common.h"
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
    using PointerType = Traits::VoidPointerKeepingConst<Type>;

    PointerType data;
    SizeType size;
};

/**
 * Функция для создания объектов DataWrapper без явного указания шаблонного
 * типа.
 * @param data указатель на начало байтовой последовательности
 * @param size размер байтовой последовательности
 */
template <class Type>
DataWrapper<Type> makeDataWrapper(Type&& data, SizeType size)
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
    SizeType size;
};

/**
 * Функция для создания объектов SizeWrapper. Не имеет непосредственной
 * необходимости, но введена для однообразия создания оберток (по аналогии с 
 * makeDataWrapper).
 * @param size размер контейнера
 */
SizeWrapper makeSizeWrapper(SizeType size)
{
    return { size };
}
} // namespace KtSerial
