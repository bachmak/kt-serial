#pragma once

#include <type_traits>

#include "kt-serial/access.h"

namespace KtSerial
{
namespace Traits
{

template <bool Expr>
using BoolConstant = std::integral_constant<bool, Expr>;

// ###########################################################################

template <bool Head, bool ... Tail>
struct Conjunction : BoolConstant<Head && Conjunction<Tail...>::value> {};

template <bool Head>
struct Conjunction<Head> : BoolConstant<Head> {};

// ###########################################################################

template <bool Head, bool ... Tail>
struct Disjunction : BoolConstant<Head || Disjunction<Tail...>::value> {};

template <bool Head>
struct Disjunction<Head> : BoolConstant<Head> {};

//                                Проверки на наличие методов для сериализации
// ###########################################################################

/**
 * Структура для проверки наличия у класса неконстантного метода SERIALIZE 
 * (определено в macros.h)
 * @tparam Type сериализуемый/десериализуемый класс, для которого
 * осуществляется проверка на наличие метода
 * @tparam Archive класс архива, принимаемый в метод по неконстантной ссылке 
 */
template <class Type, class Archive>
struct HasSerializeMethod
{
private:
    template <class T, class A> static auto
    check(int) -> decltype(
        Access::serialize(std::declval<A&>(), std::declval<T&>()),
        std::true_type{}
    );

    template <class T, class A> static auto
    check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия у класса константного метода SAVE 
 * (определено в macros.h)
 * @tparam Type сериализуемый класс, для которого осуществляется проверка на
 * наличие метода
 * @tparam Archive класс архива, принимаемый в метод по неконстантной ссылке 
 */
template <class Type, class Archive>
struct HasSaveMethod
{
private:
    template <class T, class A> static auto
    check(int) -> decltype(
        Access::save(std::declval<A&>(), std::declval<const T&>()),
        std::true_type{}
    );

    template <class T, class A> static auto
    check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия у класса неконстантного метода LOAD 
 * (определено в macros.h)
 * @tparam Type десериализуемый класс, для которого осуществляется проверка на
 * наличие метода
 * @tparam Archive класс архива, принимаемый в метод по неконстантной ссылке
 */
template <class Type, class Archive>
struct HasLoadMethod
{
private:
    template <class T, class A> static auto
    check(int) -> decltype(
        Access::load(std::declval<A&>(), std::declval<T&>()),
        std::true_type{}
    );

    template <class T, class A> static auto
    check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

//                      Проверки на наличие свободных функций для сериализации
// ###########################################################################

/**
 * Структура для проверки наличия для заданных типов свободной функции 
 * SERIALIZE (определено в macros.h)
 * @tparam Type сериализуемый/десериализуемый класс, принимаемый в функцию по
 * неконстантной ссылке вторым параметром
 * @tparam Archive класс архива, принимаемый в функцию по неконстантной ссылке
 * первым параметром
 */
template <class Type, class Archive>
struct HasSerializeFunction
{
private:
    template <class T, class A> static auto
    check(int) -> decltype(
        SERIALIZE(std::declval<A&>(), std::declval<T&>()),
        std::true_type{}
    );

    template <class T, class A> static auto
    check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия для заданных типов свободной функции 
 * SAVE (определено в macros.h)
 * @tparam Type сериализуемый класс, принимаемый в функцию по константной
 * ссылке вторым параметром
 * @tparam Archive класс архива, принимаемый в функцию по неконстантной ссылке
 * первым параметром
 */
template <class Type, class Archive>
struct HasSaveFunction
{
private:
    template <class T, class A> static auto
    check(int) -> decltype(
        SAVE(std::declval<A&>(), std::declval<const T&>()),
        std::true_type{}
    );

    template <class T, class A> static auto
    check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия для заданных типов свободной функции 
 * LOAD (определено в macros.h)
 * @tparam Type десериализуемый класс, принимаемый в функцию по неконстантной
 * ссылке вторым параметром
 * @tparam Archive класс архива, принимаемый в функцию по неконстантной ссылке
 * первым параметром
 */
template <class Type, class Archive>
struct HasLoadFunction
{
private:
    template <class T, class A> static auto
    check(int) -> decltype(
        LOAD(std::declval<A&>(), std::declval<T&>()),
        std::true_type{}
    );

    template <class T, class A> static auto
    check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

} // namespace Traits
} // namespace KtSerial
