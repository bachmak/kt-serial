#pragma once

#include <QHash>

#include "kt-serial/details/wrappers/key_value_wrapper.h"
#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QHash<Key, T>& hash) {
    ar << makeSizeWrapper(hash.size());

    for (const auto& item : hash) {
        auto wrapper = makeKeyValueWrapper(item.first, item.second);
        ar << wrapper;
    }
}

template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QHash<Key, T>& hash) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    hash.clear();

    hash.reserve(size);

    for (SizeType i = 0; i < size; ++i) {
        Key key;
        T value;
        auto wrapper = makeKeyValueWrapper(key, value);
        ar >> wrapper;
        map.insert(key, value);
    }
}
} // namespace Details
} // namespace KtSerial
