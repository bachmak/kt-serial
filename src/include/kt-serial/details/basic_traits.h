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

} // namespace Traits
} // namespace KtSerial
