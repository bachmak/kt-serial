#pragma once

#include <utility>

#include "kt-serial/details/error_messages.h"
#include "kt-serial/details/serializable_traits.h"

#ifdef KTSERIAL_TEST_MODE
#include <stdexcept>
#endif

namespace KtSerial {
/**
 * @brief Базовый класс архива для десериализации. Осуществляет проверки
 * десериализуемых типов на возможность десериализации, передает управление
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
     * @brief Конструктор класса
     *
     * @param derived ссылка на экзмепляр класса наследника
     */
    explicit BaseInputArchive(DerivedArchive& derived) : archive(derived) {}

    /**
     * @brief Перемещающий конструктор
     */
    BaseInputArchive(BaseInputArchive&&) = default;

    /**
     * @brief Перемещающий оператор присваивания
     *
     * @return BaseInputArchive& текущий экземпляр
     */
    BaseInputArchive& operator=(BaseInputArchive&&) = default;

    /**
     * @brief Копирующий конструктор
     */
    BaseInputArchive(const BaseInputArchive&) = delete;

    /**
     * @brief Копирующий оператор присваивания
     */
    BaseInputArchive& operator=(const BaseInputArchive&) = delete;

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~BaseInputArchive() = default;

    /**
     * @brief Интерфейсный оператор десериализации. Перенаправляет вызов на
     * соответствующий аргументу обработчик.
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type> DerivedArchive& operator>>(Type&& t) {
        return archive.handle(std::forward<Type>(t));
    }

    /**
     * @brief Интерфейсный оператор десериализации. Перенаправляет вызов на
     * соответствующий аргументу обработчик.
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type> DerivedArchive& operator&(Type&& t) {
        return archive.handle(std::forward<Type>(t));
    }

    /**
     * @brief Интерфейсный оператор десериализации для обработки произвольного
     * количества аргументов. Перенаправляет вызов на обработчик десериализации
     * последовательности объектов.
     *
     * @tparam Types типы десериализуемых объектов
     * @param t десериализуемые объекты
     */
    template <class... Types> void operator()(Types&&... t) {
        return archive.handleSequence(std::forward<Types>(t)...);
    }

  private:
    /**
     * @brief Метод, перенаправляющий десериализацию одного объекта на
     * соответствующий обработчик.
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     */
    template <class Type> void handleSequence(Type&& t) {
        archive.handle(std::forward<Type>(t));
    }

    /**
     * @brief Метод, перенаправляющий десериализацию объектов на соответствующие
     * типам объектов обработчики. Перенаправляет вызов на конкретные
     * обработчики только для первого элемента последовательности. Для остальных
     * - вызывается рекурсивно.
     *
     * @tparam Type тип первого объекта последовательности
     * @tparam Types остальные типы
     * @param t первый объект
     * @param ts остальные объекты
     */
    template <class Type, class... Types>
    void handleSequence(Type&& t, Types&&... ts) {
        archive.handleSequence(std::forward<Type>(t));
        archive.handleSequence(std::forward<Types>(ts)...);
    }

/**
 * @brief Макрос для выбора перегрузок метода для перенаправления вызова.
 * Перегрузка метода подставляется, если для типа Type существует
 * однозначная конфигурация методов/функций для десериализации.
 */
#define SERIALIZATION_CASE(HandlerName)                                        \
    Traits::ConjunctiveEnableIf<                                               \
        Traits::Has##HandlerName<Type, DerivedArchive>::value,                 \
        Traits::HasExactlyOneInputHandler<Type, DerivedArchive>::value> = true

    /**
     * @brief Метод, обрабатывающий случай десериализации типа, для которого
     * существует метод KTSERIAL_SERIALIZE_METHOD (определено в macros.h)
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(SerializeMethod)>
    inline DerivedArchive& handle(Type& t) {
        Access::serialize(archive, t);
        return archive;
    }

    /**
     * @brief Метод, обрабатывающий случай десериализации типа, для которого
     * существует функция KTSERIAL_SERIALIZE_FUNCTION (определено в macros.h)
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(SerializeFunction)>
    inline DerivedArchive& handle(Type&& t) {
        KTSERIAL_SERIALIZE_FUNCTION(archive, std::forward<Type>(t));
        return archive;
    }

    /**
     * @brief Метод, обрабатывающий случай десериализации типа, для которого
     * существует метод KTSERIAL_LOAD_METHOD (определено в macros.h)
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(LoadMethod)>
    inline DerivedArchive& handle(Type& t) {
        Access::load(archive, t);
        return archive;
    }

    /**
     * @brief Метод, обрабатывающий случай десериализации типа, для которого
     * существует функция KTSERIAL_LOAD_FUNCTION (определено в macros.h)
     *
     * @tparam Type тип десериализуемого объекта
     * @param t десериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(LoadFunction)>
    inline DerivedArchive& handle(Type&& t) {
        KTSERIAL_LOAD_FUNCTION(archive, std::forward<Type>(t));
        return archive;
    }
#undef SERIALIZATION_CASE

    /**
     * @brief Метод, обрабатывающий случай десериализации типа, для которого не
     * подошла ни одна из прочих перегрузок.
     *
     * @tparam Type тип десериализуемого объекта
     * @return DerivedArchive& ссылка на архив-наследник
     */
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
