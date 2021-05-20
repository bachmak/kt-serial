#pragma once

#include <string>

#include "kt-serial/access.h"
#include "kt-serial/archives/details/base_output_archive.h"

namespace SaveMethodHandled {
class Archive : public KtSerial::Details::BaseOutputArchive<Archive> {
  public:
    Archive() : KtSerial::Details::BaseOutputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

static std::string global_string;

class Savable {
  public:
    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar&) const {
        global_string += "Savable";
    }
};

class NotSavable {};

class NonConstSavable {
  public:
    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar&) {
        global_string += "NonConstSavable";
    }
};

class PrivateAccess {
  private:
    friend struct KtSerial::Access;
    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar&) const {
        global_string += "PrivateAccess";
    }
};

class PrivateNoFriends {
  private:
    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar&) const {
        global_string += "PrivateNoFriends";
    }
};

class ArchiveValue {
  public:
    template <class Ar> void KTSERIAL_SAVE_METHOD(Ar) const {
        global_string += "ArchiveValue";
    }
};
} // namespace SaveMethodHandled
