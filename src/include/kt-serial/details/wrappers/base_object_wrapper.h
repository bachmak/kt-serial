#pragma once

#include <utility>

#include "kt-serial/details/error_messages.h"
// #include "kt-serial/details/polymorphic/polymorphic_cast.h"

namespace KtSerial {
/**
 * @brief Класс-обертка над сериализуемым объектом, хранящая указатель на объект
 * базового класса этого объекта. Используется для сериализации производных
 * классов, для базовых классах которых так же определена процедура
 * сериализации.
 *
 * @tparam Base тип базового класса
 */
template <class Base> struct BaseObjectWrapper {
    /**
     * @brief Конструктор класса.
     *
     * @tparam Derived тип производного класса
     * @param derived указатель на объект производного класса
     */
    template <class Derived>
    BaseObjectWrapper(Derived* derived)
        : baseObject(static_cast<Base*>(derived)) {
        static_assert(std::is_base_of<Base, Derived>::value,
                      KTSERIAL_ERROR_INVALID_UPCAST);
        // RegisterPolymorphicCaster<Base, Derived>::bind();
    }

    Base* baseObject; /** указатель на объект базового класса */
};

/**
 * @brief Функция для создания объектов BaseObjectWrapper по любым указателям
 * (константным и неконстантным).
 *
 * @tparam Base тип базового класса сериализуемого объекта
 * @tparam Derived тип сериализуемого объекта
 * @param derived указатель на сериализуемый объект
 */
template <class Base, class Derived>
BaseObjectWrapper<Base> makeBaseObjectWrapper(const Derived* derived) {
    return {const_cast<Derived*>(derived)};
}
} // namespace KtSerial

