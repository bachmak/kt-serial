#pragma once

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/push_back.hpp>
#include <boost/preprocessor/tuple/remove.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <random>
#include <tuple>

#include "kt-serial/macros.h"
#include "test_helpers/test_functions.h"

#define __GENERATE_FIELD(r, _, typeAndName)                                    \
    BOOST_PP_TUPLE_ELEM(2, 0, typeAndName)                                     \
    BOOST_PP_TUPLE_ELEM(2, 1, typeAndName);

#define __RECURSIVELY_SWAP_1(x) ((x)) __RECURSIVELY_SWAP_1_
#define __RECURSIVELY_SWAP_1_(x) ((x)) __RECURSIVELY_SWAP_1
#define __RECURSIVELY_SWAP_1_END
#define __RECURSIVELY_SWAP_1__END

#define __RECURSIVELY_SWAP_2(x, y) ((x, y)) __RECURSIVELY_SWAP_2_
#define __RECURSIVELY_SWAP_2_(x, y) ((x, y)) __RECURSIVELY_SWAP_2
#define __RECURSIVELY_SWAP_2_END
#define __RECURSIVELY_SWAP_2__END

#define __WRAP_IN_PARENTHESES_2(args)                                          \
    BOOST_PP_CAT(__RECURSIVELY_SWAP_2 args, _END)
#define __WRAP_IN_PARENTHESES_1(args)                                          \
    BOOST_PP_CAT(__RECURSIVELY_SWAP_1 args, _END)

#define __ADD_NAME(r, _, i, elem)                                              \
    BOOST_PP_TUPLE_PUSH_BACK(elem, BOOST_PP_CAT(field, i))

#define __ADD_NAMES(types)                                                     \
    BOOST_PP_SEQ_FOR_EACH_I(__ADD_NAME, _, __WRAP_IN_PARENTHESES_1(types))

#define __GENERATE_FIELDS(typeAndName)                                         \
    BOOST_PP_SEQ_FOR_EACH(__GENERATE_FIELD, _,                                 \
                          __WRAP_IN_PARENTHESES_2(typeAndName))

#define __GET_NAME(R, _, typeAndName) BOOST_PP_TUPLE_REMOVE(typeAndName, 0)
#define __GET_TYPE(r, _, typeAndName) BOOST_PP_TUPLE_REMOVE(typeAndName, 1)

#define __GET_NAMES(typesAndNames)                                             \
    BOOST_PP_SEQ_FOR_EACH(__GET_NAME, _, __WRAP_IN_PARENTHESES_2(typesAndNames))

#define __GET_TYPES(typesAndNames)                                             \
    BOOST_PP_SEQ_FOR_EACH(__GET_TYPE, _, __WRAP_IN_PARENTHESES_2(typesAndNames))

#define __COMMA_SEPARATED(seq) BOOST_PP_SEQ_ENUM(seq)

#define __MAKE_SEQ(...) BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)

// ############################################################################

#define __GENERATE_GET_KEY_METHOD(fieldNames)                                  \
    auto getKey()                                                              \
        const->decltype(std::make_tuple(__COMMA_SEPARATED(fieldNames))) {      \
        return std::make_tuple(__COMMA_SEPARATED(fieldNames));                 \
    }

#define __GENERATE_DERIVED_GET_KEY_METHOD(baseStructName, fieldNames)          \
    auto getKey() const->decltype(                                             \
        std::make_tuple(static_cast<const baseStructName&>(*this).getKey(),    \
                        __COMMA_SEPARATED(fieldNames))) {                      \
        return std::make_tuple(baseStructName::getKey(),                       \
                               __COMMA_SEPARATED(fieldNames));                 \
    }

#define GENERATE_GET_KEY_METHOD(...)                                           \
    __GENERATE_GET_KEY_METHOD(__MAKE_SEQ(__VA_ARGS__))

#define GENERATE_DERIVED_GET_KEY_METHOD(baseStructName, ...)                   \
    __GENERATE_DERIVED_GET_KEY_METHOD(baseStructName, __MAKE_SEQ(__VA_ARGS__))

// ############################################################################

#define GENERATE_EQUAL_METHOD                                                  \
    template <class T> bool operator==(const T& t) const {                     \
        return getKey() == t.getKey();                                         \
    }

#define GENERATE_COMPARE_METHOD                                                \
    template <class T> bool operator<(const T& t) const {                      \
        return getKey() < t.getKey();                                          \
    }

// ############################################################################

#define __GENERATE_COMPARATORS(fieldNames)                                     \
    __GENERATE_GET_KEY_METHOD(fieldNames)                                      \
    GENERATE_EQUAL_METHOD                                                      \
    GENERATE_COMPARE_METHOD

#define __GENERATE_DERIVED_COMPARATORS(baseStructName, fieldNames)             \
    __GENERATE_DERIVED_GET_KEY_METHOD(baseStructName, fieldNames)              \
    GENERATE_EQUAL_METHOD                                                      \
    GENERATE_COMPARE_METHOD

#define GENERATE_COMPARATORS(...)                                              \
    __GENERATE_COMPARATORS(__MAKE_SEQ(__VA_ARGS__))

#define GENERATE_DERIVED_COMPARATORS(baseStructName, ...)                      \
    __GENERATE_DERIVED_COMPARATORS(baseStructName, __MAKE_SEQ(__VA_ARGS__))

// ############################################################################

#define __GENERATE_RANDOMIZE_METHOD(fieldNames)                                \
    void randomize(std::mt19937& gen) {                                        \
        TestFunctions::randomizeVariadic(gen, __COMMA_SEPARATED(fieldNames));  \
    }

#define __GENERATE_DERIVED_RANDOMIZE_METHOD(baseStructName, fieldNames)        \
    void randomize(std::mt19937& gen) {                                        \
        TestFunctions::randomizeVariadic(gen,                                  \
                                         static_cast<baseStructName&>(*this),  \
                                         __COMMA_SEPARATED(fieldNames));       \
    }

#define GENERATE_RANDOMIZE_METHOD(...)                                         \
    __GENERATE_RANDOMIZE_METHOD(__MAKE_SEQ(__VA_ARGS__))

#define GENERATE_DERIVED_RANDOMIZE_METHOD(baseStructName, ...)                 \
    __GENERATE_DERIVED_RANDOMIZE_METHOD(baseStructName, __MAKE_SEQ(__VA_ARGS__))

// ############################################################################

#define __GENERATE_HASH_CODE_METHOD(fieldNames)                                \
    std::size_t hashCode() const {                                             \
        return TestFunctions::hashCode(__COMMA_SEPARATED(fieldNames));         \
    }

#define __GENERATE_DERIVED_HASH_CODE_METHOD(baseStructName, fieldNames)        \
    std::size_t hashCode() const {                                             \
        return TestFunctions::hashCode(static_cast<baseStructName>(*this),     \
                                       __COMMA_SEPARATED(fieldNames));         \
    }

#define GENERATE_HASH_CODE_METHOD(...)                                         \
    __GENERATE_HASH_CODE_METHOD(__MAKE_SEQ(__VA_ARGS__))

#define GENERATE_DERIVED_HASH_CODE_METHOD(baseStructName, ...)                 \
    __GENERATE_DERIVED_HASH_CODE_METHOD(baseStructName, __MAKE_SEQ(__VA_ARGS__))

// ############################################################################

#define __GENERATE_SAVE_LOAD_METHODS(fieldNames)                               \
    template <class Archive> void KTSERIAL_SAVE_METHOD(Archive& ar) const {    \
        ar(__COMMA_SEPARATED(fieldNames));                                     \
    }                                                                          \
                                                                               \
    template <class Archive> void KTSERIAL_LOAD_METHOD(Archive& ar) {          \
        ar(__COMMA_SEPARATED(fieldNames));                                     \
    }

#define __GENERATE_DERIVED_SAVE_LOAD_METHODS(baseStructName, fieldNames)       \
    template <class Archive> void KTSERIAL_SAVE_METHOD(Archive& ar) const {    \
        ar(KtSerial::baseObject<baseStructName>(this),                         \
           __COMMA_SEPARATED(fieldNames));                                     \
    }                                                                          \
                                                                               \
    template <class Archive> void KTSERIAL_LOAD_METHOD(Archive& ar) {          \
        ar(KtSerial::baseObject<baseStructName>(this),                         \
           __COMMA_SEPARATED(fieldNames));                                     \
    }

#define GENERATE_SAVE_LOAD_METHODS(...)                                        \
    __GENERATE_SAVE_LOAD_METHODS(__MAKE_SEQ(__VA_ARGS__))

#define GENERATE_DERIVED_SAVE_LOAD_METHODS(baseStructName, ...)                \
    __GENERATE_DERIVED_SAVE_LOAD_METHODS(baseStructName,                       \
                                         __MAKE_SEQ(__VA_ARGS__))

// ############################################################################

#define GENERATE_HASH_FUNCTIONS(structName)                                    \
    namespace boost {                                                          \
    std::size_t hash_value(const structName& sn) { return sn.hashCode(); }     \
    }                                                                          \
                                                                               \
    namespace std {                                                            \
    template <> struct hash<structName> {                                      \
        std::size_t operator()(const structName& sn) const noexcept {          \
            return sn.hashCode();                                              \
        }                                                                      \
    };                                                                         \
    }

// ############################################################################

#define __GENERATE_STRUCT_BODY(typesAndNames)                                  \
    __GENERATE_FIELDS(typesAndNames)                                           \
    __GENERATE_COMPARATORS(__GET_NAMES(typesAndNames))                         \
    __GENERATE_RANDOMIZE_METHOD(__GET_NAMES(typesAndNames))                    \
    __GENERATE_HASH_CODE_METHOD(__GET_NAMES(typesAndNames))                    \
    __GENERATE_SAVE_LOAD_METHODS(__GET_NAMES(typesAndNames))

#define __GENERATE_DERIVED_STRUCT_BODY(baseStructName, typesAndNames)          \
    __GENERATE_FIELDS(typesAndNames)                                           \
    __GENERATE_DERIVED_COMPARATORS(baseStructName, __GET_NAMES(typesAndNames)) \
    __GENERATE_DERIVED_RANDOMIZE_METHOD(baseStructName,                        \
                                        __GET_NAMES(typesAndNames))            \
    __GENERATE_DERIVED_HASH_CODE_METHOD(baseStructName,                        \
                                        __GET_NAMES(typesAndNames))            \
    __GENERATE_DERIVED_SAVE_LOAD_METHODS(baseStructName,                       \
                                         __GET_NAMES(typesAndNames))

// ############################################################################

#define __GENERATE_STRUCT(structName, typesAndNames)                           \
    struct structName {                                                        \
        __GENERATE_STRUCT_BODY(typesAndNames)                                  \
    };                                                                         \
                                                                               \
    GENERATE_HASH_FUNCTIONS(structName)

#define __GENERATE_DERIVED_STRUCT(structName, baseStructName, typesAndNames)   \
    struct structName : baseStructName {                                       \
        __GENERATE_DERIVED_STRUCT_BODY(baseStructName, typesAndNames)          \
    };                                                                         \
                                                                               \
    GENERATE_HASH_FUNCTIONS(structName)

#define GENERATE_STRUCT(structName, ...)                                       \
    __GENERATE_STRUCT(structName, __ADD_NAMES(__MAKE_SEQ(__VA_ARGS__)))

#define GENERATE_DERIVED_STRUCT(structName, baseStructName, ...)               \
    __GENERATE_DERIVED_STRUCT(structName, baseStructName,                      \
                              __ADD_NAMES(__MAKE_SEQ(__VA_ARGS__)))
