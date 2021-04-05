#pragma once

#include "kt-serial/macros.h"

namespace UnambiguouslySavable
{
class Archive { Archive(const Archive&) = delete; };

class OnlyMethodSavable
{
public:
    template <class Ar>
    void KTSERIAL_SAVE_METHOD(Ar&) const;
};

class OnlyFunctionSavable {};

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar&, const OnlyFunctionSavable&);

class NotSavable {};
} // namespace UnambiguouslySavable
