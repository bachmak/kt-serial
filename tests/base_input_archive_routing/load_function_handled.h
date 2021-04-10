#pragma once

#include <string>

#include "kt-serial/access.h"
#include "kt-serial/archives/details/base_input_archive.h"

namespace LoadFunctionHandled {
class Archive : public KtSerial::BaseInputArchive<Archive> {
  public:
    Archive() : KtSerial::BaseInputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

static std::string global_string;

class Loadable {};

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, Loadable&) {
    global_string += "Loadable";
}

class NotLoadable {};

class ArchiveValue {};

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar, ArchiveValue&) {
    global_string += "ArchiveValue";
}
} // namespace SaveFunctionHandled
