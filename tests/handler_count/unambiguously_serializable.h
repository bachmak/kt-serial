#pragma once

#include "kt-serial/details/macros.h"

namespace UnambiguouslySerializable {
class Archive {
    Archive(const Archive&) = delete;
};

class OnlyMethodSerializable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);
};

class OnlyFunctionSerializable {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, OnlyFunctionSerializable&);

class NotSerializable {};
} // namespace UnambiguouslySerializable
