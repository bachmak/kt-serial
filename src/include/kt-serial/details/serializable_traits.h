#pragma once

#include <type_traits>

#include "kt-serial/access.h"
#include "kt-serial/details/basic_traits.h"

namespace KtSerial {
namespace Details {
namespace Traits {

//                                Проверки на наличие методов для сериализации
// ###########################################################################

/**
 * Структура для проверки наличия у класса неконстантного метода
 * KTSERIAL_SERIALIZE_METHOD (определено в macros.h)
 * @tparam Type сериализуемый/десериализуемый класс, для которого
 * осуществляется проверка на наличие метода
 * @tparam Archive класс архива, принимаемый в метод по неконстантной ссылке
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class Archive> struct HasSerializeMethod {
  private:
    template <class T, class A>
    static auto check(int)
        -> decltype(Access::serialize(std::declval<A&>(), std::declval<T&>()),
                    std::true_type{});

    template <class T, class A> static auto check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

  public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия у класса константного метода
 * KTSERIAL_SAVE_METHOD (определено в macros.h)
 * @tparam Type сериализуемый класс, для которого осуществляется проверка на
 * наличие метода
 * @tparam Archive класс архива, принимаемый в метод по неконстантной ссылке
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class Archive> struct HasSaveMethod {
  private:
    template <class T, class A>
    static auto check(int)
        -> decltype(Access::save(std::declval<A&>(), std::declval<const T&>()),
                    std::true_type{});

    template <class T, class A> static auto check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

  public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия у класса неконстантного метода
 * KTSERIAL_LOAD_METHOD (определено в macros.h)
 * @tparam Type десериализуемый класс, для которого осуществляется проверка на
 * наличие метода
 * @tparam Archive класс архива, принимаемый в метод по неконстантной ссылке
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class Archive> struct HasLoadMethod {
  private:
    template <class T, class A>
    static auto check(int)
        -> decltype(Access::load(std::declval<A&>(), std::declval<T&>()),
                    std::true_type{});

    template <class T, class A> static auto check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

  public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

//                      Проверки на наличие свободных функций для сериализации
// ###########################################################################

/**
 * Структура для проверки наличия для заданных типов свободной функции
 * KTSERIAL_SERIALIZE_FUNCTION (определено в macros.h)
 * @tparam Type сериализуемый/десериализуемый класс, принимаемый в функцию по
 * неконстантной ссылке вторым параметром
 * @tparam Archive класс архива, принимаемый в функцию по неконстантной ссылке
 * первым параметром
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class Archive> struct HasSerializeFunction {
  private:
    template <class T, class A>
    static auto check(int)
        -> decltype(KTSERIAL_SERIALIZE_FUNCTION(std::declval<A&>(),
                                                std::declval<T&>()),
                    std::true_type{});

    template <class T, class A> static auto check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

  public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия для заданных типов свободной функции
 * KTSERIAL_SAVE_FUNCTION (определено в macros.h)
 * @tparam Type сериализуемый класс, принимаемый в функцию по константной
 * ссылке вторым параметром
 * @tparam Archive класс архива, принимаемый в функцию по неконстантной ссылке
 * первым параметром
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class Archive> struct HasSaveFunction {
  private:
    template <class T, class A>
    static auto check(int)
        -> decltype(KTSERIAL_SAVE_FUNCTION(std::declval<A&>(),
                                           std::declval<const T&>()),
                    std::true_type{});

    template <class T, class A> static auto check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

  public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

/**
 * Структура для проверки наличия для заданных типов свободной функции
 * KTSERIAL_LOAD_FUNCTION (определено в macros.h)
 * @tparam Type десериализуемый класс, принимаемый в функцию по неконстантной
 * ссылке вторым параметром
 * @tparam Archive класс архива, принимаемый в функцию по неконстантной ссылке
 * первым параметром
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class Archive> struct HasLoadFunction {
  private:
    template <class T, class A>
    static auto check(int)
        -> decltype(KTSERIAL_LOAD_FUNCTION(std::declval<A&>(),
                                           std::declval<T&>()),
                    std::true_type{});

    template <class T, class A> static auto check(...) -> std::false_type;

    using check_type = decltype(check<Type, Archive>(0));

  public:
    static const bool value = std::is_same<check_type, std::true_type>::value;
};

//                            Проверки на однозначность процедуры сериализации
// ###########################################################################

/**
 * Структура для вычисления количества доступных функций/методов для
 * описания процедуры сериализации, соответствующих заданным типу и архиву
 * @extends std::integral_constant
 * @tparam Type сериализуемый тип
 * @tparam OutputArchive класс архива, осуществляющего сериализацию
 * @returns value – статическое поле с вычисленным количеством
 */
template <class Type, class OutputArchive>
struct OutputHandlerCount
    : IntConstant<HasSerializeMethod<Type, OutputArchive>::value +
                  HasSerializeFunction<Type, OutputArchive>::value +
                  HasSaveMethod<Type, OutputArchive>::value +
                  HasSaveFunction<Type, OutputArchive>::value> {};

/**
 * Структура для вычисления количества доступных функций/методов для
 * описания процедуры десериализации, соответствующих заданным типу и архиву
 * @extends std::integral_constant
 * @tparam Type десериализуемый тип
 * @tparam InputArchive класс архива, осуществляющего десериализацию
 * @returns value – статическое поле с вычисленным количеством
 */
template <class Type, class InputArchive>
struct InputHandlerCount
    : IntConstant<HasSerializeMethod<Type, InputArchive>::value +
                  HasSerializeFunction<Type, InputArchive>::value +
                  HasLoadMethod<Type, InputArchive>::value +
                  HasLoadFunction<Type, InputArchive>::value> {};

/**
 * Структура для проверки наличия для заданных типа и архива хотя бы одной
 * описанной процедуры сериализации
 * @extends std::integral_constant
 * @tparam Type сериализуемый тип
 * @tparam OutputArchive класс архива, осуществляющего сериализацию
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class OutputArchive>
struct HasAtLeastOneOutputHandler
    : BoolConstant<(OutputHandlerCount<Type, OutputArchive>::value > 0)> {};

/**
 * Структура для проверки наличия для заданных типа и архива хотя бы одной
 * описанной процедуры десериализации
 * @extends std::integral_constant
 * @tparam Type десериализуемый тип
 * @tparam InputArchive класс архива, осуществляющего десериализацию
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class InputArchive>
struct HasAtLeastOneInputHandler
    : BoolConstant<(InputHandlerCount<Type, InputArchive>::value > 0)> {};

/**
 * Структура для проверки наличия для заданных типа и архива ровно одной
 * описанной процедуры сериализации
 * @extends std::integral_constant
 * @tparam Type сериализуемый тип
 * @tparam OutputArchive класс архива, осуществляющего сериализацию
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class OutputArchive>
struct HasExactlyOneOutputHandler
    : BoolConstant<OutputHandlerCount<Type, OutputArchive>::value == 1> {};

/**
 * Структура для проверки наличия для заданных типа и архива ровно одной
 * описанной процедуры десериализации
 * @extends std::integral_constant
 * @tparam Type десериализуемый тип
 * @tparam InputArchive класс архива, осуществляющего десериализацию
 * @returns value – статическое поле с результатом проверки
 */
template <class Type, class InputArchive>
struct HasExactlyOneInputHandler
    : BoolConstant<InputHandlerCount<Type, InputArchive>::value == 1> {};

} // namespace Traits
} // namespace Details
} // namespace KtSerial
