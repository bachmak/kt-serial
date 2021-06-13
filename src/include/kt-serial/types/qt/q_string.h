#pragma once

#include <QString>

#include "kt-serial/types/qt/concepts/continuous_container.h"

namespace KtSerial {
namespace Details {
/**
 * @brief Перегрузка функции для сериализации строк QString.
 *
 * @tparam Archive класс архива для сериализации
 * @param ar ссылка на архив
 * @param str сериализумая строка
 */
template <class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QString& str) {
    QtConcepts::saveContinuousContainer(ar, str);
}

/**
 * @brief Перегрузка функции для десериализации строк QString.
 *
 * @tparam Archive класс архива для десериализации
 * @param ar ссылка на архив
 * @param str десериализумая строка
 */
template <class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QString& str) {
    QtConcepts::loadContinuousContainer(ar, str);
}
} // namespace Details
} // namespace KtSerial
