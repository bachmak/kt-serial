#pragma once

#include "kt-serial/details/macros.h"

namespace AmbiguouslyDeserializable {
class Archive {
    Archive(const Archive&) = delete;
};

class MethodFunctionSerializable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);
};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, MethodFunctionSerializable&);

class MethodSerializableLoadable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);

    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&);
};

class FunctionSerializableLoadable {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, FunctionSerializableLoadable&);

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(Ar&, FunctionSerializableLoadable&);

class TwoFunctionSerializable {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, TwoFunctionSerializable&);

template <class Ar>
int KTSERIAL_SERIALIZE_FUNCTION(Ar&, TwoFunctionSerializable&);

class TwoFunctionLoadable {};

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, TwoFunctionLoadable&) {}

template <class Ar> int KTSERIAL_LOAD_FUNCTION(Ar&, TwoFunctionLoadable&) {
    return 0;
}

} // namespace AmbiguouslyDeserializable
