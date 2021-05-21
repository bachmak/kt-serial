#pragma once

#include "kt-serial/details/macros.h"

namespace AmbiguouslySerializable {
class Archive {
    Archive(const Archive&) = delete;
};

class MethodFunctionSerializable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);
};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, MethodFunctionSerializable&);

class MethodSerializableSavable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);

    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar&) const;
};

class FunctionSerializableSavable {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, FunctionSerializableSavable&);

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar&, const FunctionSerializableSavable&);

class TwoFunctionSerializable {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, TwoFunctionSerializable&);

template <class Ar>
int KTSERIAL_SERIALIZE_FUNCTION(Ar&, TwoFunctionSerializable&);

class TwoFunctionSavable {};

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar&, const TwoFunctionSavable&) {}

template <class Ar> int KTSERIAL_SAVE_FUNCTION(Ar&, const TwoFunctionSavable&) {
    return 0;
}

} // namespace AmbiguouslySerializable
