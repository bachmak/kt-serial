#pragma once

#include <QMap>

#include "kt-serial/details/wrappers/key_value_wrapper.h"
#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMap<Key, T>& map) {
    ar << makeDataWrapper(map.size());

    for (const auto& item : map) {
        auto wrapper = makeKeyValueWrapper(item.first, item.second);
        ar << wrapper;
    }
}

template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMap<Key, T>& map) {
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
