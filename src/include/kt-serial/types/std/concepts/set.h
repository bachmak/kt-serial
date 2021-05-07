#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial {
namespace Concepts {
/**
 * @brief ���������� ���������� ������� ��� ������������ �������������
 * ����������� ����������� ����������, ����������� ��������� ���� ���������
 * (set, multiset).
 *
 * @tparam Archive ��� ��������� ������
 * @tparam Set ��� �������������� ���������� (std::set ��� std::multiset)
 * @param ar ������ �� �������� �����
 * @param seq ������ �� ������������� ���������
 */
template <class Archive, class Set> void saveSet(Archive& ar, const Set& set) {
    ar << makeSizeWrapper(set.size());

    for (const auto& elem : set) {
        ar << elem;
    }
}

/**
 * @brief ���������� ���������� ������� ��� �������������� �������������
 * ����������� ����������� ����������, ����������� ��������� ���� ���������
 * (set, multiset).
 *
 * @tparam Archive ��� �������� ������
 * @tparam Set ��� ���������������� ���������� (std::set ��� std::multiset)
 * @param ar ������ �� ������� �����
 * @param seq ������ �� ��������������� ���������
 */
template <class Archive, class Set> void loadSet(Archive& ar, Set& set) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    set.clear();
    auto hint = set.begin();

    for (SizeType i = 0; i < size; i++) {
        typename Set::key_type elem;
        ar >> elem;
        hint = set.insert(hint, std::move(elem));
    }
}
} // namespace Concepts
} // namespace KtSerial

