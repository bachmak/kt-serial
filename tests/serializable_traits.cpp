#include <gtest/gtest.h>

#include "kt-serial/details/serializable_traits.h"
#include "serializable_checks/serialize_method_checks.h"
#include "serializable_checks/serialize_function_checks.h"
#include "serializable_checks/save_method_checks.h"
#include "serializable_checks/save_function_checks.h"
#include "serializable_checks/load_method_checks.h"
#include "serializable_checks/load_function_checks.h"

TEST(SerializableClasses, ChecksSerializeMethod)
{
    using namespace KtSerial::Traits;
    using namespace SerializeMethodChecks;

    bool publicSerializable = HasSerializeMethod<PublicSerializable, Archive>::value;
    EXPECT_TRUE(publicSerializable);

    bool privateSerializable = HasSerializeMethod<PrivateSerializable, Archive>::value;
    EXPECT_TRUE(privateSerializable);

    bool notSerializable = HasSerializeMethod<NotSerializable, Archive>::value;
    EXPECT_FALSE(notSerializable);

    bool noAccessPrivateSerializable = HasSerializeMethod<NoAccessPrivateSerializable, Archive>::value;
    EXPECT_FALSE(noAccessPrivateSerializable);

    bool staticSerializable = HasSerializeMethod<StaticSerializable, Archive>::value;
    EXPECT_TRUE(staticSerializable);

    bool multipleSerializable = HasSerializeMethod<MultipleSerializable, Archive>::value;
    EXPECT_FALSE(multipleSerializable);

    bool constSerializable = HasSerializeMethod<const PublicSerializable, Archive>::value;
    EXPECT_FALSE(constSerializable);
}

TEST(SerializableClasses, ChecksSerializeFunction)
{
    using namespace KtSerial::Traits;
    using namespace SerializeFunctionChecks;

    bool simpleSerializable = HasSerializeFunction<Serializable, Archive>::value;
    EXPECT_TRUE(simpleSerializable);

    bool simpleNotSerializable = HasSerializeFunction<NotSerializable, Archive>::value;
    EXPECT_FALSE(simpleNotSerializable);

    bool multipleSerializable = HasSerializeFunction<MultipleSerializable, Archive>::value;
    EXPECT_FALSE(multipleSerializable);

    bool serializeFunctionWrongSignature = HasSerializeFunction<SerializeFunctionWrongSignature, Archive>::value;
    EXPECT_FALSE(serializeFunctionWrongSignature);

    bool acceptedByValue = HasSerializeFunction<AcceptedByValue, Archive>::value;
    EXPECT_TRUE(acceptedByValue);

    bool archiveAcceptedByValue = HasSerializeFunction<ArchiveAcceptedByValue, Archive>::value;
    EXPECT_FALSE(archiveAcceptedByValue);

    bool constSerializable = HasSerializeFunction<const Serializable, Archive>::value;
    EXPECT_FALSE(constSerializable);
}

TEST(SerializableClasses, ChecksSaveMethod)
{
    using namespace KtSerial::Traits;
    using namespace SaveMethodChecks;

    bool publicSavable = HasSaveMethod<PublicSavable, Archive>::value;
    EXPECT_TRUE(publicSavable);

    bool privateSavable = HasSaveMethod<PrivateSavable, Archive>::value;
    EXPECT_TRUE(privateSavable);

    bool notSavable = HasSaveMethod<NotSavable, Archive>::value;
    EXPECT_FALSE(notSavable);

    bool noAccessPrivateSavable = HasSaveMethod<NoAccessPrivateSavable, Archive>::value;
    EXPECT_FALSE(noAccessPrivateSavable);

    bool multipleSavable = HasSaveMethod<MultipleSavable, Archive>::value;
    EXPECT_FALSE(multipleSavable);

    bool nonConstSavable = HasSaveMethod<NonConstSavable, Archive>::value;
    EXPECT_FALSE(nonConstSavable);
}

TEST(SerializableClasses, ChecksSaveFunction)
{
    using namespace KtSerial::Traits;
    using namespace SaveFunctionChecks;

    bool simpleSavable = HasSaveFunction<Savable, Archive>::value;
    EXPECT_TRUE(simpleSavable);

    bool simpleNotSavable = HasSaveFunction<NotSavable, Archive>::value;
    EXPECT_FALSE(simpleNotSavable);

    bool nonConstSavable = HasSaveFunction<NonConstSavable, Archive>::value;
    EXPECT_FALSE(nonConstSavable);

    bool archiveAcceptedByValueSavable = HasSaveFunction<ArchiveAcceptedByValueSavable, Archive>::value;
    EXPECT_FALSE(archiveAcceptedByValueSavable);

    bool acceptedByValueSavable = HasSerializeFunction<AcceptedByValueSavable, Archive>::value;
    EXPECT_FALSE(acceptedByValueSavable);

    bool wrongSignatureSavable = HasSaveFunction<WrongSignatureSavable, Archive>::value;
    EXPECT_FALSE(wrongSignatureSavable);

    bool swappedSavable = HasSaveFunction<SwappedSavable, Archive>::value;
    EXPECT_FALSE(swappedSavable);

    bool swappedConstArchiveSavable = HasSaveFunction<SwappedConstArchiveSavable, Archive>::value;
    EXPECT_FALSE(swappedConstArchiveSavable);

    bool swappedNonConstSavable = HasSaveFunction<SwappedNonConstSavable, Archive>::value;
    EXPECT_FALSE(swappedNonConstSavable);

    bool multipleSavable = HasSerializeFunction<MultipleSavable, Archive>::value;
    EXPECT_FALSE(multipleSavable);
}

TEST(SerializableClasses, ChecksLoadMethod)
{
    using namespace KtSerial::Traits;
    using namespace LoadMethodChecks;

    bool publicLoadable = HasLoadMethod<PublicLoadable, Archive>::value;
    EXPECT_TRUE(publicLoadable);

    bool privateLoadable = HasLoadMethod<PrivateLoadable, Archive>::value;
    EXPECT_TRUE(privateLoadable);

    bool notLoadable = HasLoadMethod<NotLoadable, Archive>::value;
    EXPECT_FALSE(notLoadable);

    bool noAccessPrivateLoadable = HasLoadMethod<NoAccessPrivateLoadable, Archive>::value;
    EXPECT_FALSE(noAccessPrivateLoadable);

    bool multipleLoadable = HasLoadMethod<MultipleLoadable, Archive>::value;
    EXPECT_FALSE(multipleLoadable);

    bool nonConstLoadable = HasLoadMethod<ConstLoadable, Archive>::value;
    EXPECT_TRUE(nonConstLoadable);
}

TEST(SerializableClasses, ChecksLoadFunction)
{
    using namespace KtSerial::Traits;
    using namespace LoadFunctionChecks;

    bool simpleLoadable = HasLoadFunction<Loadable, Archive>::value;
    EXPECT_TRUE(simpleLoadable);

    bool simpleNotLoadable = HasLoadFunction<NotLoadable, Archive>::value;
    EXPECT_FALSE(simpleNotLoadable);

    bool constLoadable = HasLoadFunction<ConstLoadable, Archive>::value;
    EXPECT_TRUE(constLoadable);

    bool archiveAcceptedByValueLoadable = HasLoadFunction<ArchiveAcceptedByValueLoadable, Archive>::value;
    EXPECT_FALSE(archiveAcceptedByValueLoadable);

    bool acceptedByValueLoadable = HasSerializeFunction<AcceptedByValueLoadable, Archive>::value;
    EXPECT_FALSE(acceptedByValueLoadable);

    bool wrongSignatureLoadable = HasLoadFunction<WrongSignatureLoadable, Archive>::value;
    EXPECT_FALSE(wrongSignatureLoadable);

    bool swappedLoadable = HasLoadFunction<SwappedLoadable, Archive>::value;
    EXPECT_FALSE(swappedLoadable);

    bool swappedConstArchiveLoadable = HasLoadFunction<SwappedConstArchiveLoadable, Archive>::value;
    EXPECT_FALSE(swappedConstArchiveLoadable);

    bool swappedConstLoadable = HasLoadFunction<SwappedConstLoadable, Archive>::value;
    EXPECT_FALSE(swappedConstLoadable);

    bool multipleLoadable = HasSerializeFunction<MultipleLoadable, Archive>::value;
    EXPECT_FALSE(multipleLoadable);
}