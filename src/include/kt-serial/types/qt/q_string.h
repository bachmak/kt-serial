#pragma once

#include <QString>

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {

template <class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const QString& str) {
    ar << makeSizeWrapper(str.size())
       << makeDataWrapper(str.data(), static_cast<SizeType>(str.size()));
}

template <class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, QString& str) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    str.resize(size);
    ar >> makeDataWrapper(str.data(), static_cast<SizeType>(str.size()));
}
} // namespace Details
} // namespace KtSerial
