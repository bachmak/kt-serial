#pragma once

#include "kt-serial/access.h"
#include "kt-serial/macros.h"

namespace SerializeMethodChecks {
class Archive {
    Archive(const Archive&) = delete;
};

class PublicSerializable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);
};

class PrivateSerializable {
  private:
    friend struct KtSerial::Access;
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);
};

class NotSerializable {};

class NoAccessPrivateSerializable {
  private:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar&);
};

class StaticSerializable {
  public:
    template <class Ar> static void KTSERIAL_SERIALIZE_METHOD(Ar& ar);
};

class MultipleSerializable {
  public:
    template <class Ar> void KTSERIAL_SERIALIZE_METHOD(Ar& ar);

    template <class Ar> int KTSERIAL_SERIALIZE_METHOD(Ar& ar);
};
} // namespace SerializeMethodChecks
