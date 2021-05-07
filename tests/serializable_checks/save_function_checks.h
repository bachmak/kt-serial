#pragma once

#include "kt-serial/macros.h"

namespace SaveFunctionChecks {
class Archive {
    Archive(const Archive&) = delete;
};
class Savable {};
class NotSavable {};
class NonConstSavable {};
class ArchiveAcceptedByValueSavable {};
class AcceptedByValueSavable {};
class WrongSignatureSavable {};
class SwappedSavable {};
class SwappedConstArchiveSavable {};
class SwappedNonConstSavable {};
class MultipleSavable {};

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar&, const Savable&);

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar&, NonConstSavable&);

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar, const ArchiveAcceptedByValueSavable&);

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar&, AcceptedByValueSavable);

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(Ar&, const WrongSignatureSavable&, int);

template <class Ar> void KTSERIAL_SAVE_FUNCTION(const SwappedSavable&, Ar&);

template <class Ar>
void KTSERIAL_SAVE_FUNCTION(const SwappedConstArchiveSavable&, const Ar&);

template <class Ar> void KTSERIAL_SAVE_FUNCTION(SwappedNonConstSavable&, Ar&);

template <class Ar> void KTSERIAL_SAVE_FUNCTION(Ar&, const MultipleSavable&);

template <class Ar> int KTSERIAL_SAVE_FUNCTION(Ar&, const MultipleSavable&);
} // namespace SaveFunctionChecks
