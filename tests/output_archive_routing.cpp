#include <gtest/gtest.h>

#include "kt-serial/archives/details/base_output_archive.h"

#include "base_output_archive_routing/ambiguously_handled.h"
#include "base_output_archive_routing/save_function_handled.h"
#include "base_output_archive_routing/save_method_handled.h"
#include "base_output_archive_routing/serialize_function_handled.h"
#include "base_output_archive_routing/serialize_method_handled.h"

#define EXPECT_THROW_MESSAGE(tryBlock, exceptionMessage)                       \
    {                                                                          \
        std::string message;                                                   \
        try {                                                                  \
            tryBlock                                                           \
        } catch (const std::exception& e) {                                    \
            message = e.what();                                                \
        }                                                                      \
        EXPECT_EQ(message, exceptionMessage);                                  \
    }

TEST(BaseOutputArchiveRouting, SerializeMethodHandled) {
    using namespace KtSerial;
    using namespace SerializeMethodHandled;

    Archive a;
    global_string = "";

    {
        Serializable s;
        a << s;
        a& s;

        EXPECT_EQ(global_string, "SerializableSerializable");
        global_string.clear();
    }

    {
        NotSerializable ns;
        EXPECT_THROW_MESSAGE({ a << ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        ConstSerializable cs;
        a << cs;
        a& cs;

        EXPECT_EQ(global_string, "ConstSerializableConstSerializable");
        global_string.clear();
    }

    {
        StaticSerializable ss;
        a << ss;
        a& ss;

        EXPECT_EQ(global_string, "StaticSerializableStaticSerializable");
        global_string.clear();
    }

    {
        PrivateAccess pa;
        a << pa;
        a& pa;

        EXPECT_EQ(global_string, "PrivateAccessPrivateAccess");
        global_string.clear();
    }

    {
        PrivateNoFriends pa;
        EXPECT_THROW_MESSAGE({ a << pa; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& pa; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        ArchiveValue av;
        EXPECT_THROW_MESSAGE({ a << av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }
}

TEST(BaseOutputArchiveRouting, SerializeFunctionHandled) {
    using namespace KtSerial;
    using namespace SerializeFunctionHandled;

    Archive a;
    global_string = "";

    {
        Serializable s;
        a << s;
        a& s;

        EXPECT_EQ(global_string, "SerializableSerializable");
        global_string.clear();
    }

    {
        NotSerializable ns;
        EXPECT_THROW_MESSAGE({ a << ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        ConstSerializable cs;
        a << cs;
        a& cs;

        EXPECT_EQ(global_string, "ConstSerializableConstSerializable");
        global_string.clear();
    }

    {
        ArchiveValue av;
        EXPECT_THROW_MESSAGE({ a << av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }
}

TEST(BaseOutputArchiveRouting, SaveMethodHandled) {
    using namespace KtSerial;
    using namespace SaveMethodHandled;

    Archive a;
    global_string = "";

    {
        Savable s;
        a << s;
        a& s;

        EXPECT_EQ(global_string, "SavableSavable");
        global_string.clear();
    }

    {
        NotSavable ns;
        EXPECT_THROW_MESSAGE({ a << ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        NonConstSavable ncs;
        EXPECT_THROW_MESSAGE({ a << ncs; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ncs; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        PrivateAccess pa;
        a << pa;
        a& pa;

        EXPECT_EQ(global_string, "PrivateAccessPrivateAccess");
        global_string.clear();
    }

    {
        PrivateNoFriends pnf;
        EXPECT_THROW_MESSAGE({ a << pnf; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& pnf; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        ArchiveValue av;
        EXPECT_THROW_MESSAGE({ a << av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }
}

TEST(BaseOutputArchiveRouting, SaveFunctionHandled) {
    using namespace KtSerial;
    using namespace SaveFunctionHandled;

    Archive a;
    global_string = "";

    {
        Savable s;
        a << s;
        a& s;

        EXPECT_EQ(global_string, "SavableSavable");
        global_string.clear();
    }

    {
        NotSavable ns;
        EXPECT_THROW_MESSAGE({ a << ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        NonConstSavable ncs;
        EXPECT_THROW_MESSAGE({ a << ncs; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ncs; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }

    {
        ArchiveValue av;
        EXPECT_THROW_MESSAGE({ a << av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& av; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }
}

TEST(BaseOutputArchiveRouting, AmbiguouslyHandled) {
    using namespace KtSerial;
    using namespace AmbiguouslyHandled;

    Archive a;

    {
        SerializableSavable ss;
        EXPECT_THROW_MESSAGE({ a << ss; },
                             KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ss; },
                             KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
    }
    {
        NotSerializable ns;
        EXPECT_THROW_MESSAGE({ a << ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ns; },
                             KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
    }
    {
        SerializableLoadable sl;
        EXPECT_NO_THROW({ a << sl; });
        EXPECT_NO_THROW({ a& sl; });
    }
    {
        SavableLoadable sl;
        EXPECT_NO_THROW({ a << sl; });
        EXPECT_NO_THROW({ a& sl; });
    }
    {
        SavableSavable ss;
        EXPECT_THROW_MESSAGE({ a << ss; },
                             KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ss; },
                             KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
    }
    {
        SerializableSerializable ss;
        EXPECT_THROW_MESSAGE({ a << ss; },
                             KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
        EXPECT_THROW_MESSAGE({ a& ss; },
                             KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
    }
}