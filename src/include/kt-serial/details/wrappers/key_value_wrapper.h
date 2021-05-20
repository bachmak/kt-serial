#pragma once

#include <utility>

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/macros.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Класс-обертка над кортежами "ключ-значение".
 * Используется для унификации передачи keyvalue-пар и элементов словарей в
 * методы различных архивов (по-разному реализующих сериализацию. При
 * использовании с lvalue-ссылками сохраняет ссылки на объекты, иначе - копирует
 * значения.
 *
 * @tparam Key тип сериализуемого ключа
 * @tparam Value тип сериализуемого значения
 */
template <class Key, class Value> struct KeyValueWrapper {
    /** Key& либо Key, в зависимости от того, является ли Key ссылкой */
    using KeyType = Traits::DecayIfNotLvalueReference<Key>;
    /** Value& либо Value, в зависимости от того, является ли Value ссылкой */
    using ValueType = Traits::DecayIfNotLvalueReference<Value>;

    KeyType key;     /** ключ */
    ValueType value; /** значение */

    /**
     * @brief Метод, описывающий сериализацию объектов KeyValueWrapper.
     * Метод не является константным, так как подразумевается сериализация
     * объектов KeyValueWrapper через функцию makeKeyValueWrapper(...).
     */
    template <class Archive> void KTSERIAL_SERIALIZE_METHOD(Archive& ar) {
        ar(key, value);
    }
};

/**
 * @brief Функция для создания объектов KeyValueWrapper без явного указания
 * шаблонного типа.
 *
 * @tparam Key тип ключа сериализуемого кортежа
 * @tparam Value тип значения сериализуемого кортежа
 * @param key ключ сериализуемого кортежа
 * @param value значение сериализуемого кортежа
 */
template <class Key, class Value>
KeyValueWrapper<Key, Value> makeKeyValueWrapper(Key&& key, Value&& value) {
    return {std::forward<Key>(key), std::forward<Value>(value)};
}
} // namespace Details
} // namespace KtSerial
