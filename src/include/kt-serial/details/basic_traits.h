#pragma once

#include <type_traits>

#include "kt-serial/access.h"

namespace KtSerial
{
namespace Traits
{

template <bool Expr>
using BoolConstant = std::integral_constant<bool, Expr>;

template <int Expr>
using IntConstant = std::integral_constant<int, Expr>;

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

// ###########################################################################

template <bool ... Args>
struct AndEnabler : std::enable_if<Conjunction<Args...>::value, bool> {};

template <bool ... Args>
struct OrEnabler : std::enable_if<Disjunction<Args...>::value, bool> {};

template <bool ... Args>
using ConjunctiveEnableIf = typename AndEnabler<Args...>::type;

template <bool ... Args>
using DisjunctiveEnableIf = typename OrEnabler<Args...>::type;

} // namespace Traits
} // namespace KtSerial
