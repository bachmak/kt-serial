#include "kt-serial/macros.h"

namespace KtSerial
{
struct Access
{
    template <class Archive, class T> inline static
    auto serialize(Archive& ar, T& t) -> decltype(t.SERIALIZE(ar))
    {
        return t.SERIALIZE(ar);
    }

    template <class Archive, class T> inline static
    auto save(Archive& ar, const T& t) -> decltype(t.SAVE(ar))
    {
        return t.SAVE(ar);
    }

    template <class Archive, class T> inline static
    auto load(Archive& ar, T& t) -> decltype(t.LOAD(ar))
    {
        return t.LOAD(ar);
    }
};
} // namespace KtSerial
