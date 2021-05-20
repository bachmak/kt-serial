#pragma once

#include <stdexcept>

#include "kt-serial/access.h"
#include "kt-serial/archives/details/base_input_archive.h"

namespace AmbiguouslyHandled {
class Archive : public KtSerial::Details::BaseInputArchive<Archive> {
  public:
    Archive() : KtSerial::Details::BaseInputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

class SerializableLoadable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&) {}
};

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(Ar&, SerializableLoadable&) {}

class NotSerializable {};

class SavableLoadable {
  public:
    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar&) const {}

    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&) {}
};

class LoadableLoadable {
  public:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&) {}
};

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, LoadableLoadable&) {}

class SerializableSerializable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&) const {}
};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, const SerializableSerializable&) {}

} // namespace AmbiguouslyHandled
