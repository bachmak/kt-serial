#pragma once

#include <type_traits>
#include <vector>

#include "kt-serial/details/basic_traits.h"
#include "kt-serial/details/wrappers.h"
#include "kt-serial/macros.h"

namespace KtSerial {
template <class T, class Alloc, class Archive,
          Traits::ConjunctiveEnableIf<std::is_arithmetic<T>::value,
                                      !std::is_same<T, bool>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::vector<T, Alloc>& vec) {
    ar << makeSizeWrapper(vec.size())
       << makeDataWrapper(vec.data(), vec.size() * sizeof(T));
}

template <class T, class Alloc, class Archive,
          Traits::ConjunctiveEnableIf<
              Traits::HasExactlyOneOutputHandler<T, Archive>::value,
              !std::is_arithmetic<T>::value> = true>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::vector<T, Alloc>& vec) {
    ar << makeSizeWrapper(vec.size());

    for (const auto& value : vec) {
        ar << value;
    }
}

template <class T, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::vector<bool, Alloc>& vec) {
    ar << makeSizeWrapper(vec.size());

    for (const auto& value : vec) {
        ar << static_cast<bool>(value);
    }
}
} // namespace KtSerial
