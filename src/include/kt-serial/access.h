#pragma once

#include "kt-serial/macros.h"

namespace KtSerial
{
struct Access
{
    template <class Archive, class Type> inline static
    auto serialize(Archive& ar, Type& t) -> decltype(t.KTSERIAL_SERIALIZE_METHOD(ar))
    {
        return t.KTSERIAL_SERIALIZE_METHOD(ar);
    }

    template <class Archive, class Type> inline static
    auto save(Archive& ar, const Type& t) -> decltype(t.KTSERIAL_SAVE_METHOD(ar))
    {
        return t.KTSERIAL_SAVE_METHOD(ar);
    }

    template <class Archive, class Type> inline static
    auto load(Archive& ar, Type& t) -> decltype(t.KTSERIAL_LOAD_METHOD(ar))
    {
        return t.KTSERIAL_LOAD_METHOD(ar);
    }
};
} // namespace KtSerial
