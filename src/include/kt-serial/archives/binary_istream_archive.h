#pragma once

#include <istream>
#include <stdexcept>

#include "kt-serial/archives/details/base_input_archive.h"
#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/wrappers.h"
#include "kt-serial/macros.h"

namespace KtSerial {
/**
 * Класс архива, реализующий десериализацию данных из входного потока в
 * бинарном виде.
 * @extends BaseInputArchive
 */
class BinaryIstreamArchive : public BaseInputArchive<BinaryIstreamArchive> {
  public:
    /**
     * Конструктор класса
     * @param is ссылка на входной поток для десериализации данных
     */
    BinaryIstreamArchive(std::istream& is)
        : BaseInputArchive<BinaryIstreamArchive>(*this), stream(is) {}

    /* Деструктор по умолчанию*/
    ~BinaryIstreamArchive() = default;

    /**
     * Метод для побайтового чтения данных из потока.
     * @param data указатель на начало участка памяти с данными
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

/**
 * Перегрузка функции для десериализации арифметических типов
 * (https://en.cppreference.com/w/cpp/types/is_arithmetic) с использованием
 * бинарного входного архива
 * @tparam Type тип десериализуемых данных
 * @param ar ссылка на бинарный входной архив
 * @param t десериализуемые данные
 */
template <class Type, Traits::EnableIf<std::is_arithmetic<Type>::value> = true>
void KTSERIAL_LOAD_FUNCTION(BinaryIstreamArchive& ar, Type& t) {
    ar.readData(reinterpret_cast<void*>(std::addressof(t)), sizeof(t));
}

/**
 * Перегрузка функции для десериализации непрерывной последовательности байтов
 * с использованием бинарного входного архива
 * @tparam Type тип десериализуемых данных
 * @param ar ссылка на бинарный входной архив
 * @param data объект-обертка над десериализуемыми данными
 */
template <class Type>
void KTSERIAL_LOAD_FUNCTION(BinaryIstreamArchive& ar, DataWrapper<Type> data) {
    ar.readData(data.data, static_cast<std::streamsize>(data.size));
}

/**
 * Перегрузка функции для десериализации размера контейнеров с использованием
 * бинарного входного архива
 * @param ar ссылка на бинарный входной архив
 * @param size объект-обертка над размером контейнера
 */
template <class SizeT>
void KTSERIAL_LOAD_FUNCTION(BinaryIstreamArchive& ar, SizeWrapper<SizeT> size) {
    ar.readData(reinterpret_cast<void*>(&size.size), sizeof(size.size));
}
} // namespace KtSerial
