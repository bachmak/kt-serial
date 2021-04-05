#pragma once

#include <string>

#include "kt-serial/archives/details/base_output_archive.h"
#include "kt-serial/access.h"

namespace SerializeMethodHandled
{
class Archive : public KtSerial::BaseOutputArchive<Archive>
{
public:
    Archive() : KtSerial::BaseOutputArchive<Archive>(*this) {}
    Archive(const Archive&) = delete;
};

static std::string global_string;

class Serializable
{
public:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&)
    {
        global_string += "Serializable";
    }
};

class NotSerializable {};

class ConstSerializable
{
public:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&) const
    {
        global_string += "ConstSerializable";
    }
};

class StaticSerializable
{
public:
    template <class Ar>
    static void KTSERIAL_SERIALIZE_METHOD(const Ar&)
    {
        global_string += "StaticSerializable";
    }
};

class PrivateAccess
{
private:
    friend struct KtSerial::Access;
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&)
    {
        global_string += "PrivateAccess";
    }
};

class PrivateNoFriends
{
private:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar&)
    {
        global_string += "PrivateNoFriends";
    }
};

class ArchiveValue
{
public:
    template <class Ar>
    void KTSERIAL_SERIALIZE_METHOD(Ar)
    {
        global_string += "ArchiveValue";
    }
};
} // namespace SerializeMethodHandled
