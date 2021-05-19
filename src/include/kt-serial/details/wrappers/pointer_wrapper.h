#pragma once

#include <cstdint>
#include <utility>

#include "kt-serial/details/wrappers/name_value_wrapper.h"
#include "kt-serial/macros.h"

namespace KtSerial {
/**
 * @brief Класс-обертка над указателем произвольного типа.
 * Используется для непосредственной сериализации/десериализации данных, на
 * которые указывает обернутый указатель (без попыток преобразования типов).
 *
 * @tparam Type тип указателя (может быть как константным, так и неконстантным)
 */
template <class Type> struct PointerWrapper {
    /** Конструктор класса */
    PointerWrapper(Type&& p) : pointer(std::forward<Type>(p)) {}

    Type pointer; /** обернутый указатель */
};

/**
 * @brief Функция для создания объектов PointerWrapper без явного указания
 * шаблонного типа.
 *
 * @tparam Type тип указателя
 * @param t указатель
 */
template <class Type> PointerWrapper<Type> makePointerWrapper(Type&& t) {
    return {std::forward<Type>(t)};
}

/**
 * @brief Перегрузка функции для сериализации объектов PointerWrapper. 
 * Сериализует хранимые по обернутому указателю данные, если указатель не пуст
 * 
 * @tparam Type тип указателя
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param wrapper обертка над указателем
 */
template <class Archive, class Type>
void KTSERIAL_SAVE_FUNCTION(Archive& ar,
                            const PointerWrapper<const Type* const&>& wrapper) {
	/* Если указатель пустой, не сериализуем его содержимое */
    if (!wrapper.pointer) {
        ar << makeNameValueWrapper("nullptr", std::uint8_t(1));
    } else {
        ar << makeNameValueWrapper("nullptr", std::uint8_t(0))
           << makeNameValueWrapper("data", *wrapper.pointer);
    }
}

/**
 * @brief Перегрузка функции для сериализации объектов PointerWrapper. 
 * Создает новый объект по типу указателя и десериализует его (в случае, если соответствующий сериализованный указатель не был пуст).
 *
 * @tparam Type тип указателя
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param wrapper обертка над указателем
 */
template <class Archive, class Type>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, PointerWrapper<Type*>& wrapper) {
    std::uint8_t isNullPtr;
    ar >> makeNameValueWrapper("nullptr", isNullPtr);

	/* Если был сериализован пустой указатель, не десериализуем данные */
    if (isNullPtr) {
        wrapper.pointer = nullptr;
    } else {
        Type t;
        ar >> makeNameValueWrapper("data", t);
        wrapper.pointer = new Type;
        *wrapper.pointer = std::move(t);
    }
}
} // namespace KtSerial
