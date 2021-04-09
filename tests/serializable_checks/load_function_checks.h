#pragma once

#include "kt-serial/macros.h"

namespace LoadFunctionChecks {
class Archive {
    Archive(const Archive&) = delete;
};
class Loadable {};
class NotLoadable {};
class ConstLoadable {};
class ArchiveAcceptedByValueLoadable {};
class AcceptedByValueLoadable {};
class WrongSignatureLoadable {};
class SwappedLoadable {};
class SwappedConstArchiveLoadable {};
class SwappedConstLoadable {};
class MultipleLoadable {};

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, Loadable&);

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, const ConstLoadable&);

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(Ar, ArchiveAcceptedByValueLoadable&);

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, AcceptedByValueLoadable);

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(Ar&, WrongSignatureLoadable&, int);

template <class Ar> void KTSERIAL_LOAD_FUNCTION(SwappedLoadable&, Ar&);

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(SwappedConstArchiveLoadable&, const Ar&);

template <class Ar>
void KTSERIAL_LOAD_FUNCTION(const SwappedConstLoadable&, Ar&);

template <class Ar> void KTSERIAL_LOAD_FUNCTION(Ar&, MultipleLoadable&);

template <class Ar> int KTSERIAL_LOAD_FUNCTION(Ar&, MultipleLoadable&);
} // namespace LoadFunctionChecks
