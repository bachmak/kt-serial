#pragma once

#include "kt-serial/access.h"
#include "kt-serial/macros.h"

namespace SaveMethodChecks
{
class Archive { Archive(const Archive&) = delete; };

class PublicSavable
{
public:
    template <class Ar>
    void KTSERIAL_SAVE_METHOD(Ar&) const;
};

class PrivateSavable
{
private:
    friend struct KtSerial::Access;
    template <class Ar>
    int KTSERIAL_SAVE_METHOD(Ar&) const;
};

class NotSavable {};

class NoAccessPrivateSavable
{
private:
    template <class Ar>
    void KTSERIAL_SAVE_METHOD(Ar&) const;
};

class NonConstSavable
{
public:
    template <class Ar> 
    void KTSERIAL_SAVE_METHOD(Ar& ar);
};

class MultipleSavable
{
public:
    template <class Ar>
    void KTSERIAL_SAVE_METHOD(Ar& ar);

    template <class Ar>
    int KTSERIAL_SAVE_METHOD(Ar& ar);
};
} // namespace SaveMethodChecks
