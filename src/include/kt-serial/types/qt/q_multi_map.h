#pragma once

#include <QMultiMap>

#include "kt-serial/types/qt/concepts/key_value_container.h"
#include "kt-serial/types/qt/concepts/map.h"

namespace KtSerial {
namespace Details {
template <class Key, class T, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QMultiMap<Key, T>& map) {
    QtConcepts::saveKeyValueContainer(ar, map);
}

template <class Key, class T, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QMultiMap<Key, T>& map) {
    QtConcepts::loadMap(ar, map);
}
} // namespace Details
} // namespace KtSerial
