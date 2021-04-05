#pragma once

#include <stdexcept>

#include "kt-serial/archives/details/base_output_archive.h"
#include "kt-serial/access.h"

namespace AmbiguouslyHandled
{
class Archive : public KtSerial::BaseOutputArchive<Archive>
{
public:
    Archive() : KtSerial::BaseOutputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

class SerializableSavable
{
public:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&) {}
};

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar&, const SerializableSavable&) {}

class NotSerializable {};

class SerializableLoadable
{
public:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&) {}
};

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(Ar&, const SerializableLoadable&) {}

class SavableLoadable
{
public:
    template <class Ar>
    void KTSERIAL_SAVE_METHOD(Ar&) const {}

    template <class Ar>
    void KTSERIAL_LOAD_METHOD(Ar&) {}
};

class SavableSavable
{
public:
    template <class Ar>
    void KTSERIAL_SAVE_METHOD(Ar&) const {}
};

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar&, const SavableSavable&) {}

class SerializableSerializable
{
public:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&) const {}
};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, const SerializableSerializable&) {}

} // namespace AmbiguouslyHandled
