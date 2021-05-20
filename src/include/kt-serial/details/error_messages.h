#pragma once

/**
 * Макросы для сообщений об ошибках
 */

/* Сообщение для случая отсутствия для сериализуемого типа подходящих методов/
функций serialize/save*/
#define KTSERIAL_ERROR_NO_OUTPUT_HANDLERS_FOUND                                \
    "Error: matching output serialization handlers not found"

/* Сообщение для случая отсутствия для десериализуемого типа подходящих методов/
функций serialize/load*/
#define KTSERIAL_ERROR_NO_INPUT_HANDLERS_FOUND                                 \
    "Error: matching input serialization handlers not found"

/* Сообщение для случая наличия для сериализуемого типа более одного
подходящего метода/функции serialize/save*/
#define KTSERIAL_ERROR_AMBIGUOUS_OUTPUT_HANDLERS_FOUND                         \
    "Error: more than one matching output handler found"

/* Сообщение для случая наличия для десериализуемого типа более одного
подходящего метода/функции serialize/load*/
#define KTSERIAL_ERROR_AMBIGUOUS_INPUT_HANDLERS_FOUND                          \
    "Error: more than one matching input handler found"

/* Сообщение об ошибке записи в поток*/
#define KTSERIAL_ERROR_STREAM_WRITE_FAILURE                                    \
    "Error: failed to write to the output stream"

/* Сообщение об ошибке чтения из потока*/
#define KTSERIAL_ERROR_STREAM_READ_FAILURE                                     \
    "Error: failed to read from the input stream"

