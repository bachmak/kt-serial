#pragma once

#include <QLinkedList>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QLinkedList<T>& lst) {
    ar << makeSizeWrapper(lst.size());

    for (const auto& elem : lst) {
        ar << elem;
    }
}

template <class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QLinkedList<T>& lst) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    lst.clear();

    for (SizeType i = 0; i < size; ++i) {
        T elem;
        ar >> elem;
        lst.append(elem);
    }
}
} // namespace Details
} // namespace KtSerial
