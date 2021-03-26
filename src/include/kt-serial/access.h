#pragma once

#include "kt-serial/macros.h"

namespace KtSerial
{
struct Access
{
    template <class Archive, class Type> inline static
    auto serialize(Archive& ar, Type& t) -> decltype(t.SERIALIZE(ar))
    {
        return t.SERIALIZE(ar);
    }

    template <class Archive, class Type> inline static
    auto save(Archive& ar, const Type& t) -> decltype(t.SAVE(ar))
    {
        return t.SAVE(ar);
    }

    template <class Archive, class Type> inline static
    auto load(Archive& ar, Type& t) -> decltype(t.LOAD(ar))
    {
        return t.LOAD(ar);
    }
};
} // namespace KtSerial
