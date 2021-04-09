#include <gtest/gtest.h>

#include "handler_count/unambiguously_loadable.h"
#include "handler_count/unambiguously_savable.h"
#include "handler_count/unambiguously_savable_loadable.h"
#include "handler_count/unambiguously_serializable.h"
#include "kt-serial/details/serializable_traits.h"

#include "handler_count/ambiguously_deserializable.h"
#include "handler_count/ambiguously_serializable.h"

TEST(HasExactlyOneHandler,
     ChecksIfClassesHaveExactlyOneSerializeMethodOrFunction) {
    using namespace KtSerial::Traits;
    using namespace UnambiguouslySerializable;

    bool onlyMethodSerializable =
        HasExactlyOneOutputHandler<OnlyMethodSerializable, Archive>::value;
    EXPECT_TRUE(onlyMethodSerializable);

    bool onlyMethodDeserializable =
        HasExactlyOneInputHandler<OnlyMethodSerializable, Archive>::value;
    EXPECT_TRUE(onlyMethodDeserializable);

    bool onlyFunctionSerializable =
        HasExactlyOneOutputHandler<OnlyFunctionSerializable, Archive>::value;
    EXPECT_TRUE(onlyFunctionSerializable);

    bool onlyFunctionDeserializable =
        HasExactlyOneInputHandler<OnlyFunctionSerializable, Archive>::value;
    EXPECT_TRUE(onlyFunctionDeserializable);

    bool notSerializable =
        HasExactlyOneOutputHandler<NotSerializable, Archive>::value;
    EXPECT_FALSE(notSerializable);

    bool notDeserializable =
        HasExactlyOneInputHandler<NotSerializable, Archive>::value;
    EXPECT_FALSE(notDeserializable);
}

TEST(HasExactlyOneHandler, ChecksIfClassesHaveExactlyOneSaveMethodOrFunction) {
    using namespace KtSerial::Traits;
    using namespace UnambiguouslySavable;

    bool saveMethodSavable =
        HasExactlyOneOutputHandler<OnlyMethodSavable, Archive>::value;
    EXPECT_TRUE(saveMethodSavable);

    bool saveFunctionSavable =
        HasExactlyOneOutputHandler<OnlyFunctionSavable, Archive>::value;
    EXPECT_TRUE(saveFunctionSavable);

    bool saveMethodLoadable =
        HasExactlyOneInputHandler<OnlyMethodSavable, Archive>::value;
    EXPECT_FALSE(saveMethodLoadable);

    bool saveFunctionLoadable =
        HasExactlyOneInputHandler<OnlyFunctionSavable, Archive>::value;
    EXPECT_FALSE(saveFunctionLoadable);
}

TEST(HasExactlyOneHandler, ChecksIfClassesHaveExactlyOneLoadMethodOrFunction) {
    using namespace KtSerial::Traits;
    using namespace UnambiguouslyLoadable;

    bool loadMethodLoadable =
        HasExactlyOneInputHandler<OnlyMethodLoadable, Archive>::value;
    EXPECT_TRUE(loadMethodLoadable);

    bool loadFunctionLoadable =
        HasExactlyOneInputHandler<OnlyFunctionLoadable, Archive>::value;
    EXPECT_TRUE(loadFunctionLoadable);

    bool loadMethodSavable =
        HasExactlyOneOutputHandler<OnlyMethodLoadable, Archive>::value;
    EXPECT_FALSE(loadMethodSavable);

    bool loadFunctionSavable =
        HasExactlyOneOutputHandler<OnlyFunctionLoadable, Archive>::value;
    EXPECT_FALSE(loadFunctionSavable);
}

TEST(HasExactlyOneHandler, ChecksIfClassesHaveExactlyOneSaveLoadPair) {
    using namespace KtSerial::Traits;
    using namespace UnambiguouslySavableLoadable;

    bool saveLoadMethodSavable =
        HasExactlyOneOutputHandler<MethodSavableLoadable, Archive>::value;
    EXPECT_TRUE(saveLoadMethodSavable);

    bool saveLoadMethodLoadable =
        HasExactlyOneInputHandler<MethodSavableLoadable, Archive>::value;
    EXPECT_TRUE(saveLoadMethodLoadable);

    bool saveLoadFunctionSavable =
        HasExactlyOneOutputHandler<FunctionSavableLoadable, Archive>::value;
    EXPECT_TRUE(saveLoadFunctionSavable);

    bool saveLoadFunctionLoadable =
        HasExactlyOneInputHandler<FunctionSavableLoadable, Archive>::value;
    EXPECT_TRUE(saveLoadFunctionLoadable);

    bool saveMethodLoadFunctionSavable =
        HasExactlyOneOutputHandler<MethodSavableFunctionLoadable,
                                   Archive>::value;
    EXPECT_TRUE(saveMethodLoadFunctionSavable);

    bool saveMethodLoadFunctionLoadable =
        HasExactlyOneInputHandler<MethodSavableFunctionLoadable,
                                  Archive>::value;
    EXPECT_TRUE(saveMethodLoadFunctionLoadable);

    bool saveFunctionLoadMethodSavable =
        HasExactlyOneOutputHandler<FunctionSavableMethodLoadable,
                                   Archive>::value;
    EXPECT_TRUE(saveFunctionLoadMethodSavable);

    bool saveFunctionLoadMethodLoadable =
        HasExactlyOneInputHandler<FunctionSavableMethodLoadable,
                                  Archive>::value;
    EXPECT_TRUE(saveFunctionLoadMethodLoadable);
}

TEST(HasMultipleHandlers, ChecksIfSavableClassesHaveAtLeastOneOutputHandler) {
    using namespace KtSerial::Traits;
    using namespace AmbiguouslySerializable;

    bool serializeMethodFunctionSavable =
        HasAtLeastOneOutputHandler<MethodFunctionSerializable, Archive>::value;
    EXPECT_TRUE(serializeMethodFunctionSavable);

    int serializeMethodFunctionOutHandlerCount =
        OutputHandlerCount<MethodFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeMethodFunctionOutHandlerCount, 2);

    bool serializeMethodFunctionLoadable =
        HasAtLeastOneInputHandler<MethodFunctionSerializable, Archive>::value;
    EXPECT_TRUE(serializeMethodFunctionLoadable);

    int serializeMethodFunctionInputHandlerCount =
        InputHandlerCount<MethodFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeMethodFunctionInputHandlerCount, 2);

    bool serializeSaveMethodsSavable =
        HasAtLeastOneOutputHandler<MethodSerializableSavable, Archive>::value;
    EXPECT_TRUE(serializeSaveMethodsSavable);

    int serializeSaveMethodsOutHandlerCount =
        OutputHandlerCount<MethodSerializableSavable, Archive>::value;
    EXPECT_EQ(serializeSaveMethodsOutHandlerCount, 2);

    bool serializeSaveMethodsLoadable =
        HasAtLeastOneInputHandler<MethodSerializableSavable, Archive>::value;
    EXPECT_TRUE(serializeSaveMethodsLoadable);

    int serializeSaveMethodsInputHandlerCount =
        InputHandlerCount<MethodSerializableSavable, Archive>::value;
    EXPECT_EQ(serializeSaveMethodsInputHandlerCount, 1);

    bool serializeSaveFunctionsSavable =
        HasAtLeastOneOutputHandler<FunctionSerializableSavable, Archive>::value;
    EXPECT_TRUE(serializeSaveFunctionsSavable);

    int serializeSaveFunctionsOutHandlerCount =
        OutputHandlerCount<FunctionSerializableSavable, Archive>::value;
    EXPECT_EQ(serializeSaveFunctionsOutHandlerCount, 2);

    bool serializeSaveFunctionsLoadable =
        HasAtLeastOneInputHandler<FunctionSerializableSavable, Archive>::value;
    EXPECT_TRUE(serializeSaveFunctionsLoadable);

    int serializeSaveFunctionsInputHandlerCount =
        InputHandlerCount<FunctionSerializableSavable, Archive>::value;
    EXPECT_EQ(serializeSaveFunctionsInputHandlerCount, 1);

    bool serializeTwoFunctionsSavable =
        HasAtLeastOneOutputHandler<TwoFunctionSerializable, Archive>::value;
    EXPECT_FALSE(serializeTwoFunctionsSavable);

    int serializeTwoFunctionsOutHandlerCount =
        OutputHandlerCount<TwoFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeTwoFunctionsOutHandlerCount, 0);

    bool serializeTwoFunctionsLoadable =
        HasAtLeastOneInputHandler<TwoFunctionSerializable, Archive>::value;
    EXPECT_FALSE(serializeTwoFunctionsLoadable);

    int serializeTwoFunctionsInputHandlerCount =
        InputHandlerCount<TwoFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeTwoFunctionsInputHandlerCount, 0);

    bool saveTwoFunctionsSavable =
        HasAtLeastOneOutputHandler<TwoFunctionSavable, Archive>::value;
    EXPECT_FALSE(saveTwoFunctionsSavable);

    int saveTwoFunctionsOutHandlerCount =
        OutputHandlerCount<TwoFunctionSavable, Archive>::value;
    EXPECT_EQ(saveTwoFunctionsOutHandlerCount, 0);

    bool saveTwoFunctionsLoadable =
        HasAtLeastOneInputHandler<TwoFunctionSavable, Archive>::value;
    EXPECT_FALSE(saveTwoFunctionsLoadable);

    int saveTwoFunctionsInputHandlerCount =
        InputHandlerCount<TwoFunctionSavable, Archive>::value;
    EXPECT_EQ(saveTwoFunctionsInputHandlerCount, 0);
}

TEST(HasMultipleHandlers, ChecksIfLoadableClassesHaveAtLeastOneOutputHandler) {
    using namespace KtSerial::Traits;
    using namespace AmbiguouslyDeserializable;

    bool serializeMethodFunctionSavable =
        HasAtLeastOneOutputHandler<MethodFunctionSerializable, Archive>::value;
    EXPECT_TRUE(serializeMethodFunctionSavable);

    int serializeMethodFunctionOutHandlerCount =
        OutputHandlerCount<MethodFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeMethodFunctionOutHandlerCount, 2);

    bool serializeMethodFunctionLoadable =
        HasAtLeastOneInputHandler<MethodFunctionSerializable, Archive>::value;
    EXPECT_TRUE(serializeMethodFunctionLoadable);

    int serializeMethodFunctionInputHandlerCount =
        InputHandlerCount<MethodFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeMethodFunctionInputHandlerCount, 2);

    bool serializeLoadMethodsSavable =
        HasAtLeastOneOutputHandler<MethodSerializableLoadable, Archive>::value;
    EXPECT_TRUE(serializeLoadMethodsSavable);

    int serializeLoadMethodsOutHandlerCount =
        OutputHandlerCount<MethodSerializableLoadable, Archive>::value;
    EXPECT_EQ(serializeLoadMethodsOutHandlerCount, 1);

    bool serializeLoadMethodsLoadable =
        HasAtLeastOneInputHandler<MethodSerializableLoadable, Archive>::value;
    EXPECT_TRUE(serializeLoadMethodsLoadable);

    int serializeLoadMethodsInputHandlerCount =
        InputHandlerCount<MethodSerializableLoadable, Archive>::value;
    EXPECT_EQ(serializeLoadMethodsInputHandlerCount, 2);

    bool serializeLoadFunctionsSavable =
        HasAtLeastOneOutputHandler<FunctionSerializableLoadable,
                                   Archive>::value;
    EXPECT_TRUE(serializeLoadFunctionsSavable);

    int serializeLoadFunctionsOutHandlerCount =
        OutputHandlerCount<FunctionSerializableLoadable, Archive>::value;
    EXPECT_EQ(serializeLoadFunctionsOutHandlerCount, 1);

    bool serializeLoadFunctionsLoadable =
        HasAtLeastOneInputHandler<FunctionSerializableLoadable, Archive>::value;
    EXPECT_TRUE(serializeLoadFunctionsLoadable);

    int serializeLoadFunctionsInputHandlerCount =
        InputHandlerCount<FunctionSerializableLoadable, Archive>::value;
    EXPECT_EQ(serializeLoadFunctionsInputHandlerCount, 2);

    bool serializeTwoFunctionsSavable =
        HasAtLeastOneOutputHandler<TwoFunctionSerializable, Archive>::value;
    EXPECT_FALSE(serializeTwoFunctionsSavable);

    int serializeTwoFunctionsOutHandlerCount =
        OutputHandlerCount<TwoFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeTwoFunctionsOutHandlerCount, 0);

    bool serializeTwoFunctionsLoadable =
        HasAtLeastOneInputHandler<TwoFunctionSerializable, Archive>::value;
    EXPECT_FALSE(serializeTwoFunctionsLoadable);

    int serializeTwoFunctionsInputHandlerCount =
        InputHandlerCount<TwoFunctionSerializable, Archive>::value;
    EXPECT_EQ(serializeTwoFunctionsInputHandlerCount, 0);

    bool loadTwoFunctionsSavable =
        HasAtLeastOneOutputHandler<TwoFunctionLoadable, Archive>::value;
    EXPECT_FALSE(loadTwoFunctionsSavable);

    int loadTwoFunctionsOutHandlerCount =
        OutputHandlerCount<TwoFunctionLoadable, Archive>::value;
    EXPECT_EQ(loadTwoFunctionsOutHandlerCount, 0);

    bool loadTwoFunctionsLoadable =
        HasAtLeastOneInputHandler<TwoFunctionLoadable, Archive>::value;
    EXPECT_FALSE(loadTwoFunctionsLoadable);

    int loadTwoFunctionsInputHandlerCount =
        InputHandlerCount<TwoFunctionLoadable, Archive>::value;
    EXPECT_EQ(loadTwoFunctionsInputHandlerCount, 0);
}