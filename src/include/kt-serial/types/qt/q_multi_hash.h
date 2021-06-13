#pragma once

#include <QMultiHash>

#include "kt-serial/types/qt/concepts/hash.h"
#include "kt-serial/types/qt/concepts/key_value_container.h"

namespace KtSerial {
namespace Details {
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMultiHash<Key, T>& hash) {
    QtConcepts::saveKeyValueContainer(ar, hash);
}

template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMultiHash<Key, T>& hash) {
    QtConcepts::loadHash(ar, hash);
}
} // namespace Details
} // namespace KtSerial
