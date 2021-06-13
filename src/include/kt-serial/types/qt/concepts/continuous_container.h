#pragma once

#include "kt-serial/types/details/common.h"

namespace KtSerial {
namespace Details {
namespace QtConcepts {
template <class Container, class Archive>
void saveContinuousContainer(Archive& ar, const Container& con) {
    ar << makeSizeWrapper(con.size())
       << makeDataWrapper(con.data(), static_cast<SizeType>(con.size()));
}

template <class Container, class Archive>
void loadContinuousContainer(Archive& ar, Container& con) {
	SizeType size;
	ar >> makeSizeWrapper(size);
	con.resize(size);
	ar >> makeDataWrapper(con.data(), static_cast<SizeType>(size));
}
} // namespace QtConcepts
} // namespace Details
} // namespace KtSerial
