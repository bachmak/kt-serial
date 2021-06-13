#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
template <class Container, class Archive>
void saveValueOnlyContainer(Archive& ar, const Container& con) {
    ar << makeSizeWrapper(con.size());

    for (const auto& value : con) {
        ar << value;
    }
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
