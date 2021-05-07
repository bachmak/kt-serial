#include <gtest/gtest.h>
#include <random>
#include <string>

#include "kt-serial/base_object.h"
#include "kt-serial/macros.h"
#include "kt-serial/types/std/deque.h"
#include "kt-serial/types/std/string.h"
#include "test_helpers/struct_generator.h"
#include "test_helpers/test_functions.h"

GENERATE_STRUCT(SCBase, int, int, int, bool, bool)

GENERATE_DERIVED_STRUCT(SCDerived, SCBase, std::string, double, long double,
                        SCBase)

TEST(BaseObjectSerialization, SimpleCase) {
    std::mt19937 gen;
    TestFunctions::createInstanceAndTestIOSerialization<SCBase>(gen);
    TestFunctions::createInstanceAndTestIOSerialization<SCDerived>(gen);
}

GENERATE_STRUCT(DIBase, int, int, int, bool, bool)

GENERATE_DERIVED_STRUCT(DIDerived1, DIBase, std::string, double, long double,
                        DIBase)

GENERATE_DERIVED_STRUCT(DIDerived2, DIDerived1, std::deque<std::string>, DIBase,
                        DIDerived1)

GENERATE_DERIVED_STRUCT(DIDerived3, DIDerived2, std::deque<int>, bool,
                        std::deque<bool>, long double, DIBase, DIDerived1)

GENERATE_DERIVED_STRUCT(DIDerived4, DIDerived3, char32_t, DIDerived2,
                        int_fast32_t, DIBase, bool, bool, std::deque<unsigned>)

TEST(BaseObjectSerialization, DeepInheritance) {
    std::mt19937 gen;
    TestFunctions::createInstanceAndTestIOSerialization<DIBase>(gen);
    TestFunctions::createInstanceAndTestIOSerialization<DIDerived1>(gen);
    TestFunctions::createInstanceAndTestIOSerialization<DIDerived2>(gen);
    TestFunctions::createInstanceAndTestIOSerialization<DIDerived3>(gen);
    TestFunctions::createInstanceAndTestIOSerialization<DIDerived4>(gen);

    TestFunctions::createInstanceAndTestIOSerialization<std::deque<DIDerived4>>(
        gen);
}

struct VMBase {
    std::string a;
    std::string b;
    int c;
    double d;

    virtual int foo() = 0;

    virtual int bar() = 0;

    GENERATE_COMPARATORS(a, b, c, d)
    GENERATE_RANDOMIZE_METHOD(a, b, c, d)
    GENERATE_SAVE_LOAD_METHODS(a, b, c, d)
};

struct VMDerived1 : VMBase {
    char a;
    bool b;
    unsigned c;
    std::deque<std::string> d;

    int foo() override { return 1; }

    GENERATE_DERIVED_SAVE_LOAD_METHODS(VMBase, a, b, c, d)
    GENERATE_DERIVED_COMPARATORS(VMBase, a, b, c, d)
    GENERATE_DERIVED_RANDOMIZE_METHOD(VMBase, a, b, c, d)
};

struct VMDerived2 : VMDerived1 {
    std::wstring a;
    std::deque<bool> b;
    std::size_t c;
    std::float_t d;
    std::ptrdiff_t e;

    int bar() override { return 2; };

    GENERATE_DERIVED_SAVE_LOAD_METHODS(VMDerived1, a, b, c, d, e)
    GENERATE_DERIVED_COMPARATORS(VMDerived1, a, b, c, d, e)
    GENERATE_DERIVED_RANDOMIZE_METHOD(VMDerived1, a, b, c, d, e)
};

TEST(BaseObjectSerialization, VirtualMethods) {
    std::mt19937 gen;
    TestFunctions::createInstanceAndTestIOSerialization<VMDerived2>(gen);
}

struct MSBase {
    std::ptrdiff_t a;
    std::float_t b;
    std::string c;
    std::deque<int> d;

    virtual void foo() const {}
    double func() const { return 3.0; }

    GENERATE_COMPARATORS(a, b, c, d)
    GENERATE_RANDOMIZE_METHOD(a, b, c, d)

    template <class Archive> void KTSERIAL_SERIALIZE_METHOD(Archive& ar) {
        ar(a, b, c, d);
    }
};

struct MSDerived : MSBase {
    std::string a;
    int b;
    unsigned long long c;
    bool d;

    void foo() const override {}
    double func() const { return 3.14; }

    GENERATE_DERIVED_COMPARATORS(MSBase, a, b, c, d)
    GENERATE_DERIVED_RANDOMIZE_METHOD(MSBase, a, b, c, d)

    template <class Archive> void KTSERIAL_SERIALIZE_METHOD(Archive& ar) {
        ar(KtSerial::baseObject<MSBase>(this), a, b, c, d);
    }
};

TEST(BaseObjectSerialization, MethodSerializable) {
    std::mt19937 gen;
    TestFunctions::createInstanceAndTestIOSerialization<MSDerived>(gen);
}

struct FSBase {
    char a;
    int b;
    std::deque<std::wstring> c;
    std::string d;

    virtual double foo() const = 0;

    GENERATE_COMPARATORS(a, b, c, d)
    GENERATE_RANDOMIZE_METHOD(a, b, c, d)
};

template <class Archive>
void KTSERIAL_SERIALIZE_FUNCTION(Archive& ar, FSBase& b) {
    ar(b.a, b.b, b.c, b.d);
}

struct FSDerived : FSBase {
    double a;
    bool b;
    std::streamsize c;
    std::deque<bool> d;

    double foo() const override { return 0.0; }

    GENERATE_DERIVED_COMPARATORS(FSBase, a, b, c, d)
    GENERATE_DERIVED_RANDOMIZE_METHOD(FSBase, a, b, c, d)
};

template <class Archive>
void KTSERIAL_SERIALIZE_FUNCTION(Archive& ar, FSDerived& d) {
    ar(KtSerial::baseObject<FSBase>(&d), d.a, d.b, d.c, d.d);
}

TEST(BaseObjectSerialization, FunctionSerializable) {
    std::mt19937 gen;
    TestFunctions::createInstanceAndTestIOSerialization<FSDerived>(gen);
}
