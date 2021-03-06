#pragma once

#include <string>

#include "kt-serial/access.h"
#include "kt-serial/archives/details/base_output_archive.h"

namespace SerializeFunctionHandled {
class Archive : public KtSerial::BaseOutputArchive<Archive> {
  public:
    Archive() : KtSerial::BaseOutputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

static std::string global_string;

class Serializable {};

template <class Ar> void KTSERIAL_SERIALIZE_FUNCTION(Ar&, Serializable&) {
    global_string += "Serializable";
}

class NotSerializable {};

class ConstSerializable {};

template <class Ar>
void KTSERIAL_SERIALIZE_FUNCTION(Ar&, const ConstSerializable&) {
    global_string += "ConstSerializable";
}

class ArchiveValue {};

template <class Ar> void KTSERIAL_SERIALIZE_FUNCTION(Ar, ArchiveValue&) {
    global_string += "ArchiveValue";
}
} // namespace SerializeFunctionHandled
