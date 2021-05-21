#pragma once

#include <QSet>

#include "kt-serial/types/details/commmon.h"

namespace KtSerial {
namespace Details {
template <class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QSet<T>& set) {
    ar << makeSizeWrapper(set.size());

    for (const auto& elem : set) {
        ar << elem;
    }
}

template <class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QSet<T>& set) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    set.clear();

    for (SizeType i = 0; i < size; ++i) {
        T elem;
        ar >> elem;
        set.insert(elem);
    }
}
} // namespace Details
} // namespace KtSerial
