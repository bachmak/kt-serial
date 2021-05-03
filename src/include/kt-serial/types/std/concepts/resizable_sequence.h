#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial
{
template <class Sequence, class Archive>
void saveResizableSequence(Archive& ar, const Sequence& seq) {
    ar << makeSizeWrapper(std::distance(seq.begin(), seq.end()));

    for (const auto& value : seq) {
        ar << value;
    }
}

template <class Sequence, class Archive>
void loadResizableSequence(Archive& ar, Sequence& seq) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    seq.resize(size);
    
    for (auto& value : seq) {
        ar >> value;
    }
}
} // namespace KtSerial

