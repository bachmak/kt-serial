#include <gtest/gtest.h>

#include "kt-serial/details/traits.h"

class Archive {};

class PublicSerializable
{
public:
    template <class Ar>
    void serialize(Ar&);
};

class PrivateSerializable
{
private:
    friend struct KtSerial::Access;
    template <class Ar>
    void serialize(Ar&);
};

class SerializableByFunction {};

template <typename Ar>
void serialize(Ar&, SerializableByFunction&);

using namespace KtSerial::Traits;

TEST(SerializeMethod, HandlesSerializableClasses)
{
    auto publicSerializable = HasSerializeMethod<PublicSerializable, Archive>::value;
    EXPECT_TRUE(publicSerializable);

    auto privateSerializable = HasSerializeMethod<PrivateSerializable, Archive>::value;
    EXPECT_TRUE(privateSerializable);
}
