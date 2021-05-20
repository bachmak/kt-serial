#pragma once

#include <utility>

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/common.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Класс-обертка над бинарными данными, которые можно сериализовать как
 * непрерывную байтовую последовательность. Используется для передачи данных
 * из функций, описывающих процедуру сериализации стандартных типов, в
 * методы различных архивов (по-разному реализующих сериализацию).
 *
 * @tparam Type тип указателя на начало последовательности
 */
template <class Type> struct DataWrapper {
    /**
     * @brief Конструктор по указателю и количеству элементов последовательности
     *
     * @param dataPtr указатель на начало байтовой последовательности
     * @param dataSize количество элементов в последовательности
     */
    explicit DataWrapper(Type&& dataPtr, std::size_t dataSize)
        : data(std::forward<Type>(dataPtr)),
          size(dataSize * sizeof(typename Traits::RemovePointer<Type>::type)) {}

    /** void* либо const void* - в зависимости от константности Type */
    using PointerType = Traits::VoidPointerKeepingConst<Type>;

    PointerType data; /** указатель на начало участка памяти с данными */
    SizeType size; /** размер участка памяти в байтах */
};

/**
 * @brief Функция для создания объектов DataWrapper без явного указания
 * шаблонного типа.
 *
 * @tparam Type тип указателя на начало последовательности
 * @param data указатель на начало байтовой последовательности
 * @param size количество элементов в последовательности
 */
template <class Type>
DataWrapper<Type> makeDataWrapper(Type&& data, std::size_t size) {
    return DataWrapper<Type>(std::forward<Type>(data), size);
}
} // namespace Details
} // namespace KtSerial
