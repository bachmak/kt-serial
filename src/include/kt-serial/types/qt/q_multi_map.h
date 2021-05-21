#pragma once

#include <QMultiMap>

#include "Kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMultiMap<Key, T>& map) {
    ar << makeSizeWrapper(map.size());

    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        auto wrapper = makeKeyValueWrapper(it.key(), it.value());
        ar << wrapper;
    }
}

template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMultiMap<Key, T>& map) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    map.clear();
    auto hint = map.begin();

    for (SizeType i = 0; i < size; ++i) {
        Key key;
        T value;
        auto wrapper = makeKeyValueWrapper(key, value);
        ar >> wrapper;
        hint = map.insert(hint, key, value);
    }
}
} // namespace Details
} // namespace KtSerial
