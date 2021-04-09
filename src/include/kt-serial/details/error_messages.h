#pragma once

/**
 * Макросы для сообщений об ошибках
 */

/* Сообщение для случая отсутствия для сериализуемого типа подходящих методов/
функций serialize/save/load*/
#define KTSERIAL_ERROR_NO_HANDLERS_FOUND                                       \
    "Error: matching output serialization handlers not found"

/* Сообщение для случая наличия для сериализуемого типа более одного
подходящего метода/функции serialize/save/load*/
#define KTSERIAL_ERROR_AMBIGUOUS_HANDLERS_FOUND                                \
    "Error: more than one matching output handler found"

/* Сообщение об ошибке записи в поток*/
#define KTSERIAL_ERROR_STREAM_WRITE_FAILURE                                    \
    "Error: failed to write to the output stream"
