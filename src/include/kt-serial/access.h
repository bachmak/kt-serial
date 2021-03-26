#pragma once

#include "kt-serial/macros.h"

namespace KtSerial
{
struct Access
{
    template <class Archive, class Type> inline static
    auto serialize(Archive& ar, Type& t) -> decltype(t.SERIALIZE_METHOD(ar))
    {
        return t.SERIALIZE_METHOD(ar);
    }

    template <class Archive, class Type> inline static
    auto save(Archive& ar, const Type& t) -> decltype(t.SAVE_METHOD(ar))
    {
        return t.SAVE_METHOD(ar);
    }

    template <class Archive, class Type> inline static
    auto load(Archive& ar, Type& t) -> decltype(t.LOAD_METHOD(ar))
    {
        return t.LOAD_METHOD(ar);
    }
};
} // namespace KtSerial
