#pragma once

#include <QVector>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QVector<T>& vec) {
    ar << makeSizeWrapper(vec.size());

    for (const auto& value : vec) {
        ar << value;
    }
}

template <class T, Archive>
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
