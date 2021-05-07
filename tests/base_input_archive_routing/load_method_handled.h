#pragma once

#include <string>

#include "kt-serial/access.h"
#include "kt-serial/archives/details/base_input_archive.h"

namespace LoadMethodHandled {
class Archive : public KtSerial::BaseInputArchive<Archive> {
  public:
    Archive() : KtSerial::BaseInputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

static std::string global_string;

class Loadable {
  public:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&) {
        global_string += "Loadable";
    }
};

class NotLoadable {};

class PrivateAccess {
  private:
    friend struct KtSerial::Access;
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&) {
        global_string += "PrivateAccess";
    }
};

class PrivateNoFriends {
  private:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&) {
        global_string += "PrivateNoFriends";
    }
};

class ArchiveValue {
  public:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar) {
        global_string += "ArchiveValue";
    }
};
} // namespace LoadMethodHandled
