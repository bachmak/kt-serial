#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
template <class Container, class Archive>
void saveKeyValueContainer(Archive& ar, const Container& con) {
    ar << makeSizeWrapper(con.size());

    for (auto it = con.constBegin(); it != con.constEnd(); ++it) {
        ar << makeKeyValueWrapper(it.key(), it.value());
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
