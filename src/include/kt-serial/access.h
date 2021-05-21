#pragma once

#include "kt-serial/details/macros.h"

namespace KtSerial {
/**
 * Структура, обеспечивающая доступ к приватным методам serialize/save/load
 * сериализуемых классов.
 * При наличии приватных методов сериализации необходимо сделать данную
 * структуру дружественной по отношению к сериализуемому классу.
 */
struct Access {
    /**
     * Метод для вызова приватного метода класса KTSERIAL_SERIALIZE_METHOD
     * (определено в macros.h). Компилируется, если KTSERIAL_SERIALIZE_METHOD
     * для типа Type существует
     * @param ar ссылка на архив, осуществляющий сериализацию/десериализацию
     * @param t ссылка на сериализуемый объект
     */
    template <class Archive, class Type>
    inline static auto serialize(Archive& ar, Type& t)
        -> decltype(t.KTSERIAL_SERIALIZE_METHOD(ar)) {
        return t.KTSERIAL_SERIALIZE_METHOD(ar);
    }

    /**
     * Метод для вызова приватного метода класса KTSERIAL_SAVE_METHOD
     * (определено в macros.h). Компилируется, если константный
     * KTSERIAL_SAVE_METHOD для типа Type существует
     * @param ar ссылка на архив, осуществляющий сериализацию
     * @param t ссылка на сериализуемый объект
     */
    template <class Archive, class Type>
    inline static auto save(Archive& ar, const Type& t)
        -> decltype(t.KTSERIAL_SAVE_METHOD(ar)) {
        return t.KTSERIAL_SAVE_METHOD(ar);
    }

    /**
     * Метод для вызова приватного метода класса KTSERIAL_LOAD_METHOD
     * (определено в macros.h). Компилируется, если KTSERIAL_LOAD_METHOD
     * для типа Type существует
     * @param ar ссылка на архив, осуществляющий сериализацию
     * @param t ссылка на сериализуемый объект
     */
    template <class Archive, class Type>
    inline static auto load(Archive& ar, Type& t)
        -> decltype(t.KTSERIAL_LOAD_METHOD(ar)) {
        return t.KTSERIAL_LOAD_METHOD(ar);
    }
};
} // namespace KtSerial
