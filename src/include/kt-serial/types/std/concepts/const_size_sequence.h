#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial
{
template <class Archive, class Sequence>
void saveConstSizeSequence(Archive& ar, Sequence& seq) {
    for (const auto& value : seq) {
        ar << value;
    }
}

template <class Archive, class Sequence>
void loadConstSizeSequence(Archive& ar, Sequence& seq) {
    for (auto& value : seq) {
        ar >> value;
    }
}
} // namespace KtSerial
