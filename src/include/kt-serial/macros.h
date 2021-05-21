#pragma once

#include "kt-serial/details/macros.h"

#define SERIALIZABLE_PURE_VIRTUAL                                              \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive&) const = 0;   \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive&) = 0;

#define SERIALIZABLE_VIRTUAL(...)                                              \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const {   \
        oa(__VA_ARGS__);                                                       \
    }                                                                          \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) {          \
        ia(__VA_ARGS__);                                                       \
    }

#define SERIALIZABLE(...)                                                      \
    void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& outArchive) const {   \
        outArchive(__VA_ARGS__);                                               \
    }                                                                          \
    void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& inArchive) {           \
        inArchive(__VA_ARGS__);                                                \
    }

#define SERIALIZABLE_VIRTUAL_OVERRIDE(...)                                     \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa)           \
        const override {                                                       \
        oa(__VA_ARGS__);                                                       \
    }                                                                          \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) override { \
        ia(__VA_ARGS__);                                                       \
    }

#define SERIALIZABLE_OVERRIDE(...)                                             \
    void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const override {  \
        oa(__VA_ARGS__);                                                       \
    }                                                                          \
    void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) override {         \
        ia(__VA_ARGS__);                                                       \
    }

#define SERIALIZABLE_DERIVED(baseClassName, ...)                               \
    void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const {           \
        oa(static_cast<const baseClassName&>(*this), __VA_ARGS__);             \
    }                                                                          \
    void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) {                  \
        ia(static_cast<baseClassName&>(*this), __VA_ARGS__);                   \
    }

#define SERIALIZABLE_DERIVED_VIRTUAL(baseClassName, ...)                       \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const {   \
        oa(static_cast<const baseClassName&>(*this), __VA_ARGS__);             \
    }                                                                          \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) {          \
        ia(static_cast<baseClassName&>(*this), __VA_ARGS__);                   \
    }

#define SERIALIZABLE_DERIVED_VIRTUAL_OVERRIDE(baseClassName, ...)              \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa)           \
        const override {                                                       \
        oa(static_cast<const baseClassName&>(*this), __VA_ARGS__);             \
    }                                                                          \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) override { \
        ia(static_cast<baseClassName&>(*this), __VA_ARGS__);                   \
    }

#define SERIALIZABLE_DERIVED_OVERRIDE(baseClassName, ...)                      \
    void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const override {  \
        oa(static_cast<const baseClassName&>(*this), __VA_ARGS__);             \
    }                                                                          \
    void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) override {         \
        ia(static_cast<baseClassName&>(*this), __VA_ARGS__);                   \
    }
