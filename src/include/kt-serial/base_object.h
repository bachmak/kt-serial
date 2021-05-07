#pragma once

#include "kt-serial/details/wrappers.h"

namespace KtSerial {
/**
 * @brief Функция для создания специального класса-обертки над указателем на
 * сериализуемый объект для сериализации его базового объекта. Сериализация
 * базового класса таким образом предпочтительнее явного вызова функций и
 * методов сериализации базового класса, так как не требует явного указания
 * конкретного способа сериализации (через функции save/load/serialize или
 * соответствующие методы).
 * 
 * @tparam Base тип базового класса сериализуемого объекта
 * @tparam Derived тип класса сериализуемого объекта (производный класс)
 * @param derived указатель на сериализуемый объект (this)
 */
template <class Base, class Derived>
BaseObjectWrapper<Base> baseObject(const Derived* derived) {
    return makeBaseObjectWrapper<Base>(derived);
}
} // namespace KtSerial
