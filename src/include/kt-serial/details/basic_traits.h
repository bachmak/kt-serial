#pragma once

#include <type_traits>

#include "kt-serial/access.h"

namespace KtSerial {
namespace Traits {
/**
 * Сокращение для распространенного случая использования
 * std::integral_constant с типом bool
 * (https://en.cppreference.com/w/cpp/types/integral_constant)
 */
template <bool Expr> using BoolConstant = std::integral_constant<bool, Expr>;

/**
 * Сокращение для распространенного случая использования
 * std::integral_constant с типом int
 * (https://en.cppreference.com/w/cpp/types/integral_constant)
 */
template <int Expr> using IntConstant = std::integral_constant<int, Expr>;

// ###########################################################################

/**
 * Рекурсивная мета-функция для реализации конъюнктивной логической функции.
 * Для истинного выражения Conjunction<...>::value принимает значение true
 * @tparam Head,...Tail логические выражения
 */
template <bool Head, bool... Tail>
struct Conjunction : BoolConstant<Head && Conjunction<Tail...>::value> {};

template <bool Head> struct Conjunction<Head> : BoolConstant<Head> {};

// ###########################################################################

/**
 * Рекурсивная мета-функция для реализации дизъюнктивной логической функции.
 * Для истинного выражения Disjunction<...>::value принимает значение true
 * @tparam Head,...Tail логические выражения
 */
template <bool Head, bool... Tail>
struct Disjunction : BoolConstant<Head || Disjunction<Tail...>::value> {};

template <bool Head> struct Disjunction<Head> : BoolConstant<Head> {};

// ###########################################################################

/**
 * Вспомогательня структура для упрощения использования стандартной
 * метафункции std::enable_if
 * (https://en.cppreference.com/w/cpp/types/enable_if) в сочетании с
 * метафункцией Conjunction. Если выражение логической функции истинно,
 * выражение AndEnabler::type имеет тип bool (иначе не переопределено)
 * @tparam Args логические выражения
 */
template <bool... Args>
struct AndEnabler : std::enable_if<Conjunction<Args...>::value, bool> {};

/**
 * Вспомогательня структура для упрощения использования стандартной
 * метафункции std::enable_if
 * (https://en.cppreference.com/w/cpp/types/enable_if) в сочетании с
 * метафункцией Disjunction. Если выражение логической функции истинно,
 * выражение OrEnabler::type имеет тип bool (иначе не переопределено)
 * @tparam Args логические выражения
 */
template <bool... Args>
struct OrEnabler : std::enable_if<Disjunction<Args...>::value, bool> {};

/**
 * Сокращение для упрощения использования стандартной метафункции
 * std::enable_if (https://en.cppreference.com/w/cpp/types/enable_if).
 * Выражение EnableIf<Arg> имеет тип bool, если Arg истинно (иначе тип не
 * переопределен)
 */
template <bool Arg> using EnableIf = typename std::enable_if<Arg, bool>::type;

/**
 * Сокращение для организации выбора перегрузок функций, для которых каждое
 * условие Args истинно. В таком случае выражение ConjunctiveEnableIf<Args...>
 * имеет тип bool, иначе происходит неудачная подстановка – идиома SFINAE
 * (https://en.cppreference.com/w/cpp/language/sfinae)
 */
template <bool... Args>
using ConjunctiveEnableIf = typename AndEnabler<Args...>::type;

/**
 * Сокращение для организации выбора перегрузок функций, для которых хотя бы
 * одно условие из Args истинно. В таком случае выражение
 * DisjunctiveEnableIf<Args...> имеет тип bool, иначе происходит неудачная
 * подстановка – идиома SFINAE
 * (https://en.cppreference.com/w/cpp/language/sfinae)
 */
template <bool... Args>
using DisjunctiveEnableIf = typename OrEnabler<Args...>::type;

// ###########################################################################

/**
 * Вспомогательня структура для упрощения использования стандартных
 * метафункций std::remove_pointer и std::remove_reference
 * (https://en.cppreference.com/w/cpp/types/remove_pointer,
 * https://en.cppreference.com/w/cpp/types/remove_reference).
 * @tparam Ptr тип указателя
 */
template <class Ptr>
struct RemovePointer
    : std::remove_pointer<typename std::remove_reference<Ptr>::type> {};

/**
 * Вспомогательная структура для упрощения использования стандартной
 * метафункции std::is_const
 * (https://en.cppreference.com/w/cpp/types/is_const).
 * Для константного указателя IsConstPointer<>::value принимает истинное
 * значение.
 * @tparam Ptr тип указателя.
 */
template <class Ptr>
struct IsConstPointer : std::is_const<typename RemovePointer<Ptr>::type> {};

/**
 * Сокращение для преобразования указателя произвольного типа к указателю
 * на тип void (с сохранением константности/неконстантности).
 */
template <class Ptr>
using VoidPointerKeepingConst =
    typename std::conditional<IsConstPointer<Ptr>::value, const void*,
                              void*>::type;

/**
 * Сокращение для выбора типа переменной: если переменная является
 * lvalue-ссылкой, ее тип сохраняется. Иначе преобразуется к исходному типу
 * (например int& -> int&, int&& -> int, int -> int).
 */
template <class Type>
using DecayIfNotLvalueReference =
    typename std::conditional<std::is_lvalue_reference<Type>::value, Type,
                              typename std::decay<Type>::type>::type;
} // namespace Traits
} // namespace KtSerial
