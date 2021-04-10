#pragma once

#include <utility>

#include "kt-serial/details/error_messages.h"
#include "kt-serial/details/serializable_traits.h"

#ifdef KTSERIAL_TEST_MODE
#include <stdexcept>
#endif

namespace KtSerial {
/**
 * Базовый класс архива для десериализации. Осуществляет проверки
 * сериализуемых типов на возможность десериализации, передает управление
 * в соответствующие функции/методы и сообщает об ошибках при их наличии.
 *
 * Классы архивов, реализующих конкретные способы десериализации, должны
 * наследоваться от данного класса с передачей собственного типа в качестве
 * шаблонного аргумента (идиома CRTP).
 * @tparam DerivedArchive класс архива-наследника, реализующего десериализацию
 */
template <class DerivedArchive> class BaseInputArchive {
  public:
    /**
     * Конструктор класса
     * @param derived ссылка на экземпляр класса наследника
     */
    BaseInputArchive(DerivedArchive& derived) : archive(derived) {}

    /* Перемещающий конструктор*/
    BaseInputArchive(BaseInputArchive&&) = default;

    /* Перемещающий оператор присваивания*/
    BaseInputArchive& operator=(BaseInputArchive&&) = default;

    /* Копирующий конструктор*/
    BaseInputArchive(const BaseInputArchive&) = delete;

    /* Копирующий оператор присваивания*/
    BaseInputArchive& operator=(const BaseInputArchive&) = delete;

    /* Виртуальный деструктор*/
    virtual ~BaseInputArchive() = default;

    /**
     * Интерфейсный оператор десериализации. Перенаправляет вызов на
     * соответствующий аргументу обработчик.
     * @param t десериализуемый объект
     * @returns ссылка на архив наследника
     */
    template <class Type> DerivedArchive& operator>>(Type&& t) {
        return archive.handle(std::forward<Type>(t));
    }

    /**
     * Интерфейсный оператор десериализации. Перенаправляет вызов на
     * соответствующий аргументу обработчик.
     * @param t десериализуемый объект
     * @returns ссылка на архив наследника
     */
    template <class Type> DerivedArchive& operator&(Type&& t) {
        return archive.handle(std::forward<Type>(t));
    }

  private:
/* Макрос для выбора перегрузок метода для перенаправления вызова.
Перегрузка метода подставляется, если для типа Type существует
однозначная конфигурация методов/функций для десериализации*/
#define SERIALIZATION_CASE(HandlerName)                                        \
    Traits::ConjunctiveEnableIf<                                               \
        Traits::Has##HandlerName<Type, DerivedArchive>::value,                 \
        Traits::HasExactlyOneInputHandler<Type, DerivedArchive>::value> = true

    /* Метод, обрабатывающий случай десериализации типа, для которого
    существует метод KTSERIAL_SERIALIZE_METHOD (определено в macros.h)*/
    template <class Type, SERIALIZATION_CASE(SerializeMethod)>
    inline DerivedArchive& handle(Type& t) {
        Access::serialize(archive, t);
        return archive;
    }

    /* Метод, обрабатывающий случай десериализации типа, для которого
    существует функция KTSERIAL_SERIALIZE_FUNCTION (определено в macros.h)*/
    template <class Type, SERIALIZATION_CASE(SerializeFunction)>
    inline DerivedArchive& handle(Type&& t) {
        KTSERIAL_SERIALIZE_FUNCTION(archive, std::forward<Type>(t));
        return archive;
    }

    /* Метод, обрабатывающий случай десериализации типа, для которого
    существует метод KTSERIAL_LOAD_METHOD (определено в macros.h)*/
    template <class Type, SERIALIZATION_CASE(LoadMethod)>
    inline DerivedArchive& handle(Type& t) {
        Access::load(archive, t);
        return archive;
    }

    /* Метод, обрабатывающий случай десериализации типа, для которого
    существует функция KTSERIAL_LOAD_FUNCTION (определено в macros.h)*/
    template <class Type, SERIALIZATION_CASE(LoadFunction)>
    inline DerivedArchive& handle(Type&& t) {
        KTSERIAL_LOAD_FUNCTION(archive, std::forward<Type>(t));
        return archive;
    }
#undef SERIALIZATION_CASE

    /* Метод, обрабатывающий случай десериализации типа, для которого не
    подошла ни одна из прочих перегрузок*/
    template <class Type,
              Traits::ConjunctiveEnableIf<!Traits::HasExactlyOneInputHandler<
                  Type, DerivedArchive>::value> = true>
    DerivedArchive& handle(const Type&) {
/* В тестовом режиме бросаем исключения*/
#if defined(KTSERIAL_TEST_MODE)
        if (!Traits::HasAtLeastOneInputHandler<Type, DerivedArchive>::value) {
            throw std::invalid_argument(KTSERIAL_ERROR_NO_INPUT_HANDLERS_FOUND);
        }
        if (!Traits::HasExactlyOneInputHandler<Type, DerivedArchive>::value) {
            throw std::invalid_argument(
                KTSERIAL_ERROR_AMBIGUOUS_INPUT_HANDLERS_FOUND);
        }
#else
        /* В обычном режиме - ошибки компиляции*/
        static_assert(
            Traits::HasAtLeastOneInputHandler<Type, DerivedArchive>::value,
            KTSERIAL_ERROR_NO_INPUT_HANDLERS_FOUND);

        static_assert(
            Traits::HasExactlyOneInputHandler<Type, DerivedArchive>::value,
            KTSERIAL_ERROR_AMBIGUOUS_INPUT_HANDLERS_FOUND);
#endif

        return archive;
    }

  private:
    DerivedArchive& archive; /** ссылка на архив наследника */
};
} // namespace KtSerial
