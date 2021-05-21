#pragma once

#include <QList>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QList<T>& lst) {
    ar << makeSizeWrapper(lst.size());

    for (const auto& elem : lst) {
        ar << elem;
    }
}

template <class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QList<T>& lst) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    lst.reserve(size);

    for (SizeType i = 0; i < size; ++i) {
        T elem;
        ar >> elem;
        lst.append(elem);
    }
}
} // namespace Details
} // namespace KtSerial
