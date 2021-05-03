#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial
{
template <class Archive, class Set>
void saveSet(Archive& ar, const Set& set) {
    ar << makeSizeWrapper(set.size());

    for (const auto& elem : set) {
        ar << elem;
    }
}

template <class Archive, class Set>
void loadSet(Archive& ar, Set& set) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    set.clear();
    auto hint = set.begin();

    for (SizeType i = 0; i < size; i++) {
        typename Set::key_type elem;
        ar >> elem;
        hint = set.insert(hint, std::move(elem));
    }
}
} // namespace KtSerial
