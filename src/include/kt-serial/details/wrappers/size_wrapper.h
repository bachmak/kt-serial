#pragma once

#include <utility>

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/common.h"

namespace KtSerial {
/**
 * @brief Класс-обертка над значением размера сериализуемых контейнеров.
 * Используется для унификации передачи данных о размере контейнера из функций,
 * описывающих процедуру сериализации стандартных типов, в методы различных
 * архивов (по-разному реализующих сериализацю). При использовании с
 * lvalue-ссылкой сохраняет ссылку на переменную, иначе - копирует значение.
 *
 * @tparam Type тип размера контейнера
 */
template <class Type> struct SizeWrapper {
    /** Type& либо Type, в зависимости от того, является ли Type ссылкой */
    using SizeType = Traits::DecayIfNotLvalueReference<Type>;
    SizeType size; /** размер контейнера */
};

/**
 * @brief Функция для создания объектов SizeWrapper без явного указания
 * шаблонного типа.
 *
 * @tparam Type тип размера контейнера
 * @param size размер контейнера
 */
template <class Type> SizeWrapper<Type> makeSizeWrapper(Type&& size) {
    return {std::forward<Type>(size)};
}
} // namespace KtSerial

