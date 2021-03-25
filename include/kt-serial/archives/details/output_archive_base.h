#pragma once

#include <utility>

namespace KtSerial
{
template <class OutputArchiveDerived>
class OutputArchiveBase
{
public:
    OutputArchiveBase(const OutputArchiveDerived &archive) : self(archive) {}

    template <class T>
    OutputArchiveDerived& operator<<(T&& t)                                             // основной оператор для сериализации
    {
        return self.process(std::forward<T>(t));
    }

private:
    const OutputArchiveDerived &self;

private:
    // TODO: process overloads
};
} // namespace KtSerial
