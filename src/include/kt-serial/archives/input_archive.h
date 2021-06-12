#pragma once

#include <istream>
#include <stdexcept>

#include "kt-serial/archives/details/base_input_archive.h"
#include "kt-serial/details/macros.h"

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/wrappers.h"

namespace KtSerial {
/**
 * @brief Класс архива, реализующий десериализацию данных из входного потока в
 * бинарном виде.
 */
class InputArchive : public Details::BaseInputArchive<InputArchive> {
  public:
    /**
     * @brief Конструктор класса
     * @param is ссылка на входной поток для десериализации данных
     */
    explicit InputArchive(std::istream& is)
        : Details::BaseInputArchive<InputArchive>(*this), stream(is) {}

    /**
     * @brief Деструктор класса
     */
    ~InputArchive() override = default;

    /**
     * @brief Метод для побайтового чтения данных из потока.
     *
     * @param data указатель на начало участка памяти
     * @param size размера участка памяти в байтах
     */
    void readData(void* data, std::streamsize size) {
        /* Считываем данные (напрямую через .rdbuf()->sgetn() быстрее, чем
        через .read()) и сохраняем количество считанных байт в переменную*/
        std::streamsize readSize =
            stream.rdbuf()->sgetn(reinterpret_cast<char*>(data), size);

        /* Если запрошенное количество байт не было считано, бросаем
        исключение */
        if (readSize != size) {
            throw std::runtime_error(KTSERIAL_ERROR_STREAM_READ_FAILURE);
        }
    }

  private:
    std::istream& stream; /** ссылка на входной поток для чтения */
};

namespace Details {
/**
 * @brief Перегрузка функции для десериализации арифметических типов
 * (https://en.cppreference.com/w/cpp/types/is_arithmetic) с использованием
 * бинарного входного архива.
 *
 * @tparam Type тип десериализуемых данных
 * @param ar ссылка на бинарный входной архив
 * @param t десериализуемые данные
 */
template <class Type,
          Details::Traits::EnableIf<std::is_arithmetic<Type>::value> = true>
void KTSERIAL_LOAD_FUNCTION(InputArchive& ar, Type& t) {
    ar.readData(reinterpret_cast<void*>(std::addressof(t)), sizeof(t));
}

/**
 * @brief Перегрузка функции для десериализации непрерывной последовательности
 * байтов с использованием бинарного входного архива. DataWrapper передается по
 * значению для возможности использования move-семантики (ar >>
 * makeDataWrapper(...)).
 *
 * @tparam Type тип десериализуемых данных
 * @param ar ссылка на бинарный входной архив
 * @param data объект-обертка над десериализуемыми данными
 */
template <class Type>
void KTSERIAL_LOAD_FUNCTION(InputArchive& ar, Details::DataWrapper<Type> data) {
    ar.readData(data.data, static_cast<std::streamsize>(data.size));
}

/**
 * @brief Перегрузка функции для десериализации размеров контейнеров с
 * использованием бинарного входного архива. SizeWrapper передается по значению
 * для возможности использования move-семантики (ar >> makeSizeWrapper(...);).
 *
 * @tparam SizeT тип для хранения размера контейнера в SizeWrapper (ссылка или
 * значение)
 * @param ar ссылка на бинарный входной архив
 * @param size объект-обертка над размером контейнера
 */
template <class SizeT>
void KTSERIAL_LOAD_FUNCTION(InputArchive& ar,
                            Details::SizeWrapper<SizeT> sizeWrapper) {
    SizeType size;
    ar.readData(reinterpret_cast<void*>(&size), sizeof(size));
    sizeWrapper.size =
        static_cast<typename Details::SizeWrapper<SizeT>::SizeType>(size);
}

/**
 * @brief Перегрузка функции для десериализации адаптера над парой ключ-значение
 * с использованием бинарного входного архива. KeyValueWrapper передается по
 * значению для возможности использования move-семантики (ar >>
 * makeKeyValueWrapper(...);)
 *
 * @tparam Key тип для хранения ключа в KeyValueWrapper (ссылка или
 * значение)
 * @tparam Value тип для хранения значения в KeyValueWrapper (ссылка или
 * значение)
 * @param ar ссылка на бинарный входной архив
 * @param keyValue объект-обертка над парой ключ-значение
 */
template <class Key, class Value>
void KTSERIAL_LOAD_FUNCTION(InputArchive& ar,
                            Details::KeyValueWrapper<Key, Value> keyValue) {
    ar(keyValue.key, keyValue.value);
}
} // namespace Details
} // namespace KtSerial
