#pragma once

#include <string>

#include "kt-serial/access.h"
#include "kt-serial/archives/details/base_output_archive.h"

namespace SaveFunctionHandled {
class Archive : public KtSerial::Details::BaseOutputArchive<Archive> {
  public:
    Archive() : KtSerial::Details::BaseOutputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

static std::string global_string;

class Savable {};

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar&, const Savable&) {
    global_string += "Savable";
}

class NotSavable {};

class NonConstSavable {};

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar&, NonConstSavable&) {
    global_string += "NonConstSavable";
}

class ArchiveValue {};

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar, const ArchiveValue&) {
    global_string += "ArchiveValue";
}
} // namespace SaveFunctionHandled
