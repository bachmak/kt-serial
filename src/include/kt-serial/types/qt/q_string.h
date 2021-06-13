#pragma once

#include <QString>

#include "kt-serial/types/qt/concepts/continuous_container.h"

namespace KtSerial {
namespace Details {
template <class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QString& str) {
	QtConcepts::saveContinuousContainer(ar, str);
}

template <class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QString& str) {
	QtConcepts::loadContinuousContainer(ar, str);
}
} // namespace Details
} // namespace KtSerial
