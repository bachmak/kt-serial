#pragma once

#include <QMultiHash>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMultiHash<Key, T>& hash) {
    ar << makeSizeWrapper(hash.size());

    for (auto it = hash.constBegin(); it != hash.constEnd(); ++it) {
        ar << makeKeyValueWrapper(it.key(), it.value());
    }
}

template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMultiHash<Key, T>& hash) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    hash.clear();

    hash.reserve(size);

    for (SizeType i = 0; i < size; ++i) {
        Key key;
        T value;
        ar >> makeKeyValueWrapper(key, value);
        hash.insert(key, value);
    }
}
} // namespace Details
} // namespace KtSerial
