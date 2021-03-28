#pragma once

#include "kt-serial/macros.h"

namespace SerializeFunctionChecks
{
class Archive { Archive(const Archive&) = delete; };
class Serializable {};
class NotSerializable {};
class MultipleSerializable {};
class SerializeFunctionWrongSignature {};
class AcceptedByValue {};
class ArchiveAcceptedByValue {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, Serializable&);

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, MultipleSerializable&);

template <class Ar>
int KTSERIAL_SERIALIZE_FUNCTION(Ar&, MultipleSerializable&);

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, SerializeFunctionWrongSignature&, int);

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar, ArchiveAcceptedByValue&);

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, AcceptedByValue);
} // namespace SerializeFunctionChecks
