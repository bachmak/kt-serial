#pragma once

#include <ostream>
#include <stdexcept>

#include "kt-serial/archives/details/base_output_archive.h"
#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/wrappers.h"
#include "kt-serial/macros.h"

namespace KtSerial {
/**
 * Класс архива, реализующий сериализацию данных в выходной поток в
 * бинарном виде.
 * @extends BaseOutputArchive
 * @tparam CharT шаблонный тип символа потока std::basic_ostream
 * @tparam TraitsT шаблонный тип, определяющий операции с типом CharT
 */
template <class CharT, class TraitsT = std::char_traits<CharT>>
class BasicBinaryOstreamArchive
    : public BaseOutputArchive<BasicBinaryOstreamArchive<CharT, TraitsT>> {
  public:
    /**
     * Конструктор класса
     * @param os ссылка на выходной поток для сериализации данных
     */
    BasicBinaryOstreamArchive(std::basic_ostream<CharT, TraitsT>& os)
        : BaseOutputArchive<BasicBinaryOstreamArchive<CharT, TraitsT>>(*this),
          stream(os) {}

    /* Деструктор по умолчанию*/
    ~BasicBinaryOstreamArchive() = default;

    /**
     * Метод для побайтовой записи данных в поток.
     * @param data указатель на начало участка памяти с данными
     * @param size размера участка памяти в байтах
     */
    void writeData(const void* data, std::streamsize size) {
        /* Записываем данные (напрямую через .rdbuf()->sputn() быстрее, чем
        через .write()) и сохраняем количество записанных байт в переменную*/
        std::streamsize writtenSize =
            stream.rdbuf()->sputn(reinterpret_cast<const CharT*>(data), size);

        /* Если запрошенное количество байт не было записано, бросаем
        исключение */
        if (writtenSize != size) {
            throw std::runtime_error(KTSERIAL_ERROR_STREAM_WRITE_FAILURE);
        }
    }

  private:
    std::basic_ostream<CharT, TraitsT>&
        stream; /** ссылка на выходной поток для записи */
};

using BinaryOstreamArchive = BasicBinaryOstreamArchive<char>;

/**
 * Перегрузка функции для сериализации арифметических типов
 * (https://en.cppreference.com/w/cpp/types/is_arithmetic) с использованием
 * бинарного выходного архива
 * @tparam Type тип сериализуемых данных
 * @param ar ссылка на бинарный выходной архив
 * @param t сериализуемые данные
 */
template <class Type, class CharT, class TraitsT,
          Traits::EnableIf<std::is_arithmetic<Type>::value> = true>
void KTSERIAL_SAVE_FUNCTION(BasicBinaryOstreamArchive<CharT, TraitsT>& ar,
                            const Type& t) {
    ar.writeData(reinterpret_cast<const void*>(std::addressof(t)), sizeof(t));
}

/**
 * Перегрузка функции для сериализации непрерывной последовательности байтов
 * с использованием бинарного выходного архива
 * @tparam Type тип сериализуемых данных
 * @param ar ссылка на бинарный выходной архив
 * @param data объект-обертка над сериализуемыми данными
 */
template <class Type, class CharT, class TraitsT>
void KTSERIAL_SAVE_FUNCTION(BasicBinaryOstreamArchive<CharT, TraitsT>& ar,
                            const DataWrapper<Type>& data) {
    ar.writeData(data.data, static_cast<std::streamsize>(data.size));
}

/**
 * Перегрузка функции для сериализации размера контейнеров с использованием
 * бинарного выходного архива
 * @param ar ссылка на бинарный выходной архив
 * @param size объект-обертка над размером контейнера
 */
template <class CharT, class TraitsT>
void KTSERIAL_SAVE_FUNCTION(BasicBinaryOstreamArchive<CharT, TraitsT>& ar,
                            const SizeWrapper& size) {
    ar.writeData(reinterpret_cast<const void*>(&size.size), sizeof(size.size));
}
} // namespace KtSerial
