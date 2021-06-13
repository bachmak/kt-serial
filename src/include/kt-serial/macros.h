#pragma once

#include "kt-serial/details/macros.h"

/**
 * @brief Макрос для объявления чисто виртуальных методов сериализации
 * (например, в классе ICalcElement). Не требует передачи аргументов.
 */
#define SERIALIZABLE_PURE_VIRTUAL                                              \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive&) const = 0;   \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive&) = 0;

/**
 * @brief Макрос для определения виртуальных методов сериализации (например, в
 * классе CalcElement). В качестве аргументов принимает поля класса, которые
 * неоходимо сериализовать (допускается также отсутствие аргументов).
 */
#define SERIALIZABLE_VIRTUAL(...)                                              \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const {   \
        oa(__VA_ARGS__);                                                       \
    }                                                                          \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) {          \
        ia(__VA_ARGS__);                                                       \
    }

/**
 * @brief Макрос для определения невиртуальных методов сериализации (например, в
 * классе пользовательского блока). В качестве аргументов принимает поля класса,
 * которые неоходимо сериализовать (допускается также отсутствие аргументов).
 */
#define SERIALIZABLE(...)                                                      \
    void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& outArchive) const {   \
        outArchive(__VA_ARGS__);                                               \
    }                                                                          \
    void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& inArchive) {           \
        inArchive(__VA_ARGS__);                                                \
    }

/**
 * @brief Макрос для определения невиртуальных методов сериализации.
 * Используется в том случае, когда сериализация полей производного класса
 * включает в себя сериализацию полей базового класса. В качестве первого
 * обязательного аргумента принимает имя базового класса, затем поля текущего
 * класса, которые неоходимо сериализовать (допускается также отсутствие
 * аргументов - за исключением первого аргумента).
 */
#define SERIALIZABLE_DERIVED(baseClassName, ...)                               \
    void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const {           \
        oa(static_cast<const baseClassName&>(*this), __VA_ARGS__);             \
    }                                                                          \
    void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) {                  \
        ia(static_cast<baseClassName&>(*this), __VA_ARGS__);                   \
    }

/**
 * @brief Макрос для определения виртуальных методов сериализации.
 * Используется в том случае, когда сериализация полей производного класса
 * включает в себя сериализацию полей базового класса. В качестве первого
 * обязательного аргумента принимает имя базового класса, затем поля текущего
 * класса, которые неоходимо сериализовать (допускается также отсутствие
 * аргументов - за исключением первого аргумента).
 */
#define SERIALIZABLE_DERIVED_VIRTUAL(baseClassName, ...)                       \
    virtual void KTSERIAL_SAVE_METHOD(::KtSerial::OutputArchive& oa) const {   \
        oa(static_cast<const baseClassName&>(*this), __VA_ARGS__);             \
    }                                                                          \
    virtual void KTSERIAL_LOAD_METHOD(::KtSerial::InputArchive& ia) {          \
        ia(static_cast<baseClassName&>(*this), __VA_ARGS__);                   \
    }
