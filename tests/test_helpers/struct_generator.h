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

#define GENERATE_FIELD(r, _, typeAndName)                                      \
    BOOST_PP_TUPLE_ELEM(2, 0, typeAndName)                                     \
    BOOST_PP_TUPLE_ELEM(2, 1, typeAndName);

#define RECURSIVELY_SWAP_1(x) ((x)) RECURSIVELY_SWAP_1_
#define RECURSIVELY_SWAP_1_(x) ((x)) RECURSIVELY_SWAP_1
#define RECURSIVELY_SWAP_1_END
#define RECURSIVELY_SWAP_1__END

#define RECURSIVELY_SWAP_2(x, y) ((x, y)) RECURSIVELY_SWAP_2_
#define RECURSIVELY_SWAP_2_(x, y) ((x, y)) RECURSIVELY_SWAP_2
#define RECURSIVELY_SWAP_2_END
#define RECURSIVELY_SWAP_2__END

#define WRAP_IN_PARENTHESES_2(args) BOOST_PP_CAT(RECURSIVELY_SWAP_2 args, _END)
#define WRAP_IN_PARENTHESES_1(args) BOOST_PP_CAT(RECURSIVELY_SWAP_1 args, _END)

#define GENERATE_FIELDS(typeAndName)                                           \
    BOOST_PP_SEQ_FOR_EACH(GENERATE_FIELD, _, WRAP_IN_PARENTHESES_2(typeAndName))

#define GET_NAME(R, _, typeAndName) BOOST_PP_TUPLE_REMOVE(typeAndName, 0)
#define GET_TYPE(r, _, typeAndName) BOOST_PP_TUPLE_REMOVE(typeAndName, 1)

#define GET_NAMES(typesAndNames)                                               \
    BOOST_PP_SEQ_FOR_EACH(GET_NAME, _, WRAP_IN_PARENTHESES_2(typesAndNames))

#define GET_TYPES(typesAndNames)                                               \
    BOOST_PP_SEQ_FOR_EACH(GET_TYPE, _, WRAP_IN_PARENTHESES_2(typesAndNames))

#define COMMA_SEPARATED(seq) BOOST_PP_SEQ_ENUM(seq)

#define GENERATE_STRUCT_BY_TYPES_AND_NAMES(structName, typesAndNames)          \
    struct structName {                                                        \
        GENERATE_FIELDS(typesAndNames)                                         \
                                                                               \
        auto getKey() const                                                    \
            -> decltype(std::tie(COMMA_SEPARATED(GET_NAMES(typesAndNames)))) { \
            return std::tie(COMMA_SEPARATED(GET_NAMES(typesAndNames)));        \
        }                                                                      \
                                                                               \
        bool operator==(const structName& sn) const {                          \
            return getKey() == sn.getKey();                                    \
        }                                                                      \
                                                                               \
        bool operator<(const structName& sn) const {                           \
            return getKey() < sn.getKey();                                     \
        }                                                                      \
                                                                               \
        template <class Archive>                                               \
        void KTSERIAL_SAVE_METHOD(Archive& ar) const {                         \
            ar(COMMA_SEPARATED(GET_NAMES(typesAndNames)));                     \
        }                                                                      \
                                                                               \
        template <class Archive> void KTSERIAL_LOAD_METHOD(Archive& ar) {      \
            ar(COMMA_SEPARATED(GET_NAMES(typesAndNames)));                     \
        }                                                                      \
                                                                               \
        void randomize(std::mt19937& gen) {                                    \
            TestFunctions::randomizeVariadic(                                  \
                gen, COMMA_SEPARATED(GET_NAMES(typesAndNames)));               \
        }                                                                      \
                                                                               \
        std::size_t hashCode() const {                                         \
            return TestFunctions::hashCode(                                    \
                COMMA_SEPARATED(GET_NAMES(typesAndNames)));                    \
        }                                                                      \
    };                                                                         \
                                                                               \
    namespace boost {                                                          \
    template <> struct hash<structName> {                                      \
        std::size_t operator()(const structName& sn) const noexcept {          \
            return sn.hashCode();                                              \
        }                                                                      \
    };                                                                         \
    }

#define ADD_NAME(r, _, i, elem)                                                \
    BOOST_PP_TUPLE_PUSH_BACK(elem, BOOST_PP_CAT(field, i))

#define ADD_NAMES(types)                                                       \
    BOOST_PP_SEQ_FOR_EACH_I(ADD_NAME, _, WRAP_IN_PARENTHESES_1(types))

#define GENERATE_STRUCT(structName, ...)                                       \
    GENERATE_STRUCT_BY_TYPES_AND_NAMES(                                        \
        structName, ADD_NAMES(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))
