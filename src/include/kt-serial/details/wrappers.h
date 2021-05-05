#pragma once

#include <string>
#include <utility>

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/common.h"

namespace KtSerial {
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
 * @param value серилизуемый объект
 */
template <class Type>
NameValueWrapper<Type> makeNameValueWrapper(std::string name, Type&& value) {
    return {std::move(name), std::forward<Type>(value)};
}

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
        ar(makeNameValueWrapper("key", key),
           makeNameValueWrapper("value", value));
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
    return {std::forward<Key>(name), std::forward<Value>(value)};
}
} // namespace KtSerial
