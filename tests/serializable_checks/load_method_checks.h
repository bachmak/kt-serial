#pragma once

#include "kt-serial/access.h"
#include "kt-serial/macros.h"

namespace LoadMethodChecks {
class Archive {
    Archive(const Archive&) = delete;
};

class PublicLoadable {
  public:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&);
};

class PrivateLoadable {
  private:
    friend struct KtSerial::Access;
    template <class Ar> int KTSERIAL_LOAD_METHOD(Ar&);
};

class NotLoadable {};

class NoAccessPrivateLoadable {
  private:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar&);
};

class ConstLoadable {
  public:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar& ar) const;
};

class MultipleLoadable {
  public:
    template <class Ar> void KTSERIAL_LOAD_METHOD(Ar& ar);

    template <class Ar> int KTSERIAL_LOAD_METHOD(Ar& ar);
};
} // namespace LoadMethodChecks
