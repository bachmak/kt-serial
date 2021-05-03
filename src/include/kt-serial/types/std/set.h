#pragma once

#include <set>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/set.h"

namespace KtSerial {
template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::set<Key, Compare, Alloc>& set) {
    saveSet(ar, set);
}

template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::multiset<Key, Compare, Alloc>& set) {
    saveSet(ar, set);
}

template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::set<Key, Compare, Alloc>& set) {
    loadSet(ar, set);
}

template <class Key, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::multiset<Key, Compare, Alloc>& set) {
    loadSet(ar, set);
}
}