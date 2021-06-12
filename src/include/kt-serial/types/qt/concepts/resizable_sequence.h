#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
template <class Archive, class Set> void saveSet(Archive& ar, const Set& set) {
    ar << makeSizeWrapper(set.size());

    for (const auto& elem : set) {
        ar << elem;
    }
}

template <class Archive, class Set> void loadSet(Archive& ar, Set& set) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    set.clear();

    for (SizeType i = 0; i < size; ++i) {
        typename Set::key_type elem;
        ar >> elem;
        set.insert(elem);
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
