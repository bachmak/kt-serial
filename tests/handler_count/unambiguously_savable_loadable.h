#pragma once

#include "kt-serial/macros.h"

namespace UnambiguouslySavableLoadable
{
class Archive { Archive(const Archive&) = delete; };

class MethodSavableLoadable
{
public:
    template <class Ar>
    void SAVE_METHOD(Ar&) const;

    template <class Ar>
    void LOAD_METHOD(Ar&) const;
};

class FunctionSavableLoadable {};

template <class Ar>
void SAVE_FUNCTION(Ar&, const FunctionSavableLoadable&);

template <class Ar>
void LOAD_FUNCTION(Ar&, FunctionSavableLoadable&);

class MethodSavableFunctionLoadable
{
public:
    template <class Ar>
    void SAVE_METHOD(Ar&) const;
};

class FunctionSavableMethodLoadable
{
public:
    template <class Ar>
    void LOAD_METHOD(Ar&) const;
};

template <class Ar>
void SAVE_FUNCTION(Ar&, const FunctionSavableMethodLoadable&);

template <class Ar>
void LOAD_FUNCTION(Ar&, MethodSavableFunctionLoadable&);
} // namespace UnambiguouslySavableLoadable
