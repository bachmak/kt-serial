#pragma once

#include <string>
#include <utility>

#include "kt-serial/details/basic_traits.h"

namespace KtSerial {
/**
 * @brief Класс-обертка над названием объекта и ссылкой на него (или его
 * значением). Используется для унификации передачи именованных объектов в
 * методы различных архивов (по-разному реализующих сериализацию – в том числе
 * не сериализующих название объета). При использовании с lvalue-ссылкой
 * сохраняет ссылку на объект, иначе - копирует значение.
 *
 * @tparam Type тип сериализуемого объекта
 */
template <class Type> struct NameValueWrapper {
    /** Type& либо Type, в зависимости от того, является ли Type ссылкой */
    using ValueType = Traits::DecayIfNotLvalueReference<Type>;

    std::string name; /** имя объекта */
    ValueType value;  /** сериализуемый объект */
};

/**
 * @brief Функция для создания объектов NameValueWrapper без явного указания
 * шаблонного типа.
 *
 * @tparam Type тип сериализуемого объекта
 * @param name имя сериализуемого объекта
 * @param value сериализуемый объект
 */
template <class Type>
NameValueWrapper<Type> makeNameValueWrapper(std::string name, Type&& value) {
    return {std::move(name), std::forward<Type>(value)};
}
} // namespace KtSerial
