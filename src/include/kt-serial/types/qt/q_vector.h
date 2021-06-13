#pragma once

#include <QVector>

#include "kt-serial/types/details/common.h"
#include "kt-serial/types/qt/concepts/continuous_container.h"
#include "kt-serial/types/qt/concepts/value_only_container.h"

namespace KtSerial {
namespace Details {
template <class T, class Archive,
          Traits::EnableIf<std::is_arithmetic<T>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QVector<T>& vec) {
    QtConcepts::saveContinuousContainer(ar, vec);
}

template <class T, class Archive,
          Traits::EnableIf<std::is_arithmetic<T>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QVector<T>& vec) {
    QtConcepts::loadContinuousContainer(ar, vec);
}

template <class T, class Archive,
          Traits::EnableIf<!std::is_arithmetic<T>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QVector<T>& vec) {
    QtConcepts::saveValueOnlyContainer(ar, vec);
}

template <class T, class Archive,
          Traits::EnableIf<!std::is_arithmetic<T>::value> = true>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QVector<T>& vec) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    vec.resize(size);

    for (auto& elem : vec) {
        ar >> elem;
    }
}
} // namespace Details
} // namespace KtSerial
