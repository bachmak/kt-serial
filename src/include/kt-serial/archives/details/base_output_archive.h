#pragma once

#include <utility>

#include "kt-serial/details/error_messages.h"
#include "kt-serial/details/serializable_traits.h"
#include "kt-serial/details/wrappers.h"

#ifdef KTSERIAL_TEST_MODE
#include <stdexcept>
#endif

namespace KtSerial {
/**
 * @brief Базовый класс архива для сериализации. Осуществляет проверки
 * сериализуемых типов на возможность сериализации, передает управление
 * в соответствующие функции/методы и сообщает об ошибках при их наличии.
 *
 * Классы архивов, реализующих конкретные способы сериализации, должны
 * наследоваться от данного класса с передачей собственного типа в качестве
 * шаблонного аргумента (идиома CRTP).
 * @tparam DerivedArchive класс архива-наследника, реализующего сериализацию
 */
template <class DerivedArchive> class BaseOutputArchive {
  public:
    /**
     * Конструктор класса
     *
     * @param derived ссылка на экземпляр класса наследника
     */
    explicit BaseOutputArchive(DerivedArchive& derived) : archive(derived) {}

    /**
     * @brief Перемещающий конструктор
     */
    BaseOutputArchive(BaseOutputArchive&&) = default;

    /**
     * @brief Перемещающий оператор присваивания
     *
     * @return BaseOutputArchive& текущий экзмепляр
     */
    BaseOutputArchive& operator=(BaseOutputArchive&&) = default;

    /**
     * @brief Копирующий конструктор
     */
    BaseOutputArchive(const BaseOutputArchive&) = delete;

    /**
     * @brief Копирующий оператор присваивания
     */
    BaseOutputArchive& operator=(const BaseOutputArchive&) = delete;

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~BaseOutputArchive() = default;

    /**
     * @brief Интерфейсный оператор сериализации. Перенаправляет вызов на
     * соответствующий аргументу обработчик.
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     * @return DerivedArchive& ссылка на архив наследника
     */
    template <class Type> DerivedArchive& operator<<(Type&& t) {
        return archive.handle(std::forward<Type>(t));
    }

    /**
     * @brief Интерфейсный оператор сериализации. Перенаправляет вызов на
     * соответствующий аргументу обработчик.
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type> DerivedArchive& operator&(Type&& t) {
        return archive.handle(std::forward<Type>(t));
    }

    /**
     * @brief Интерфейсный оператор сериализации для обработки произвольного
     * количества аргументов. Перенаправляет вызов на обработчик сериализации
     * последовательности объектов.
     *
     * @tparam Types типы сериализуемых объектов
     * @param t сериализуемые объекты
     */
    template <class... Types> void operator()(Types&&... t) {
        return archive.handleSequence(std::forward<Types>(t)...);
    }

  private:
    /**
     * @brief Метод, перенаправляющий сериализацию одного объекта на
     * соответствующий обработчик.
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     */
    template <class Type> void handleSequence(Type&& t) {
        archive.handle(std::forward<Type>(t));
    }

    /**
     * @brief Метод, перенаправляющий сериализацию объектов на соответствующие
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
     * @brief Метод, обрабатывающий случай сериализации базового типа через
     * объект производного типа с помощью класса-обертки BaseObjectWrapper.
     *
     * @tparam Type тип базового класса
     * @param t обертка над сериализуемым объектом, содержащая указатель на
     * его базовый класс
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type>
    inline DerivedArchive& handle(BaseObjectWrapper<Type> t) {
        return archive.handle(*t.baseObject);
    }

/**
 * @brief Макрос для выбора перегрузок метода для перенаправления вызова.
 * Перегрузка метода подставляется, если для типа Type существует
 * однозначная конфигурация методов/функций для сериализации.
 */
#define SERIALIZATION_CASE(HandlerName)                                        \
    Traits::ConjunctiveEnableIf<                                               \
        Traits::Has##HandlerName<Type, DerivedArchive>::value,                 \
        Traits::HasExactlyOneOutputHandler<Type, DerivedArchive>::value> =     \
        true

    /**
     * @brief Метод, обрабатывающий случай сериализации типа, для которого
     * существует метод KTSERIAL_SERIALIZE_METHOD (определено в macros.h)
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(SerializeMethod)>
    inline DerivedArchive& handle(Type& t) {
        Access::serialize(archive, t);
        return archive;
    }

    /**
     * @brief Метод, обрабатывающий случай сериализации типа, для которого
     * существует функция KTSERIAL_SERIALIZE_FUNCTION (определено в macros.h)
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(SerializeFunction)>
    inline DerivedArchive& handle(Type& t) {
        KTSERIAL_SERIALIZE_FUNCTION(archive, t);
        return archive;
    }

    /**
     * @brief Метод, обрабатывающий случай сериализации типа, для которого
     * существует метод KTSERIAL_SAVE_METHOD (определено в macros.h)
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(SaveMethod)>
    inline DerivedArchive& handle(const Type& t) {
        Access::save(archive, t);
        return archive;
    }

    /**
     * @brief Метод, обрабатывающий случай сериализации типа, для которого
     * существует функция KTSERIAL_SAVE_FUNCTION (определено в macros.h)
     *
     * @tparam Type тип сериализуемого объекта
     * @param t сериализуемый объект
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type, SERIALIZATION_CASE(SaveFunction)>
    inline DerivedArchive& handle(const Type& t) {
        KTSERIAL_SAVE_FUNCTION(archive, t);
        return archive;
    }
#undef SERIALIZATION_CASE

    /**
     * @brief Метод, обрабатывающий случай сериализации типа, для которого не
     * подошла ни одна из прочих перегрузок.
     *
     * @tparam Type тип сериализуемого объекта
     * @return DerivedArchive& ссылка на архив-наследник
     */
    template <class Type,
              Traits::ConjunctiveEnableIf<!Traits::HasExactlyOneOutputHandler<
                  Type, DerivedArchive>::value> = true>
    DerivedArchive& handle(const Type&) {
/* В тестовом режиме бросаем исключения*/
#if defined(KTSERIAL_TEST_MODE)
        if (!Traits::HasAtLeastOneOutputHandler<Type, DerivedArchive>::value) {
            throw std::invalid_argument(
                KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);
        }
        if (!Traits::HasExactlyOneOutputHandler<Type, DerivedArchive>::value) {
            throw std::invalid_argument(
                KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
        }
#else
        /* В обычном режиме - ошибки компиляции*/
        static_assert(
            Traits::HasAtLeastOneOutputHandler<Type, DerivedArchive>::value,
            KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND);

        static_assert(
            Traits::HasExactlyOneOutputHandler<Type, DerivedArchive>::value,
            KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND);
#endif

        return archive;
    }

  private:
    DerivedArchive& archive; /** ссылка на архив наследника */
};
} // namespace KtSerial
