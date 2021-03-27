#pragma once

#include "kt-serial/macros.h"

namespace UnambiguouslyLoadable
{
class Archive { Archive(const Archive&) = delete; };

class OnlyMethodLoadable
{
public:
    template <class Ar>
    void LOAD_METHOD(Ar&);
};

class OnlyFunctionLoadable {};

template <class Ar>
void LOAD_FUNCTION(Ar&, OnlyFunctionLoadable&);

class NotLoadable {};
} // namespace UnambiguouslySerializable
