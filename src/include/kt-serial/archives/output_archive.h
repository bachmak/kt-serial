#pragma once

#include <ostream>
#include <stdexcept>

#include "kt-serial/archives/details/base_output_archive.h"
#include "kt-serial/details/macros.h"

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/common.h"
#include "kt-serial/details/wrappers.h"

namespace KtSerial {
/**
 * @brief Класс архива, реализующий сериализацию данных в выходной поток в
 * бинарном виде.
 */
class OutputArchive : public Details::BaseOutputArchive<OutputArchive> {
  public:
    /**
     * @brief Конструктор класса
     * @param os ссылка на выходной поток для сериализации данных
     */
    explicit OutputArchive(std::ostream& os)
        : Details::BaseOutputArchive<OutputArchive>(*this), stream(os) {}

    /**
     * @brief Деструктор класса
     */
    ~OutputArchive() override = default;

    /**
     * @brief Метод для побайтовой записи данных в поток.
     *
     * @param data указатель на начало участка памяти с данными
     * @param size размера участка памяти в байтах
     */
    void writeData(const void* data, std::streamsize size) {
        /* Записываем данные (напрямую через .rdbuf()->sputn() быстрее, чем
        через .write()) и сохраняем количество записанных байт в переменную*/
        std::streamsize writtenSize =
            stream.rdbuf()->sputn(reinterpret_cast<const char*>(data), size);

        /* Если запрошенное количество байт не было записано, бросаем
        исключение */
        if (writtenSize != size) {
            throw std::runtime_error(KTSERIAL_ERROR_STREAM_WRITE_FAILURE);
        }
    }

  private:
    std::ostream& stream; /** ссылка на выходной поток для записи */
};

namespace Details {
/**
 * @brief Перегрузка функции для сериализации арифметических типов
 * (https://en.cppreference.com/w/cpp/types/is_arithmetic) с использованием
 * бинарного выходного архива.
 *
 * @tparam Type тип сериализуемых данных
 * @param ar ссылка на бинарный выходной архив
 * @param t сериализуемые данные
 */
template <class Type,
          Details::Traits::EnableIf<std::is_arithmetic<Type>::value> = true>
void KTSERIAL_SAVE_FUNCTION(OutputArchive& ar, const Type& t) {
    ar.writeData(reinterpret_cast<const void*>(std::addressof(t)), sizeof(t));
}

/**
 * @brief Перегрузка функции для сериализации непрерывной последовательности
 * байтов с использованием бинарного выходного архива.
 *
 * @tparam Type тип сериализуемых данных
 * @param ar ссылка на бинарный выходной архив
 * @param data объект-обертка над сериализуемыми данными
 */
template <class Type>
void KTSERIAL_SAVE_FUNCTION(OutputArchive& ar,
                            const Details::DataWrapper<Type>& data) {
    ar.writeData(data.data, static_cast<std::streamsize>(data.size));
}

/**
 * @brief Перегрузка функции для сериализации размера контейнеров с
 * использованием бинарного выходного архива.
 *
 * @tparam SizeT тип для хранения размера контейнера в SizeWrapper (ссылка или
 * значение)
 * @param ar ссылка на бинарный выходной архив
 * @param size объект-обертка над размером контейнера
 */
template <class SizeT>
void KTSERIAL_SAVE_FUNCTION(OutputArchive& ar,
                            const Details::SizeWrapper<SizeT>& sizeWrapper) {
    SizeType size = static_cast<SizeType>(sizeWrapper.size);
    ar.writeData(reinterpret_cast<const void*>(&size), sizeof(size));
}

/**
 * @brief Перегрузка функции для сериализации адаптера над парой ключ-значение с
 * использованием бинарного выходного архива.
 *
 * @tparam Key тип для хранения ключа в KeyValueWrapper (ссылка или
 * значение)
 * @tparam Value тип для хранения значения в KeyValueWrapper (ссылка или
 * значение)
 * @param ar ссылка на бинарный выходной архив
 * @param keyValue объект-обертка над парой ключ-значение
 */
template <class Key, class Value>
void KTSERIAL_SAVE_FUNCTION(
    OutputArchive& ar, const Details::KeyValueWrapper<Key, Value>& keyValue) {
    ar(keyValue.key, keyValue.value);
}

} // namespace Details
} // namespace KtSerial
