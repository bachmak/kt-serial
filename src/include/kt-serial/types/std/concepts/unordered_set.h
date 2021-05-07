#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial {
namespace Concepts {
/**
 * @brief ���������� ���������� ������� ��� ������������ ���������������
 * ������������� ����������� ����������� ����������, ����������� ��������� ����
 * ��������� (unordered_set, unordered_multiset).
 *
 * @tparam Archive ��� ��������� ������
 * @tparam UnorderedSet ��� �������������� ���������� (std::unordered_set ���
 * std::unordered_multiset)
 * @param ar ������ �� �������� �����
 * @param set ������ �� ������������� ���������
 */
template <class Archive, class UnorderedSet>
void saveUnorderedSet(Archive& ar, const UnorderedSet& set) {
    ar << makeSizeWrapper(set.size()) << makeSizeWrapper(set.bucket_count());

    for (const auto& elem : set) {
        ar << elem;
    }
}

/**
 * @brief ���������� ���������� ������� ��� �������������� ���������������
 * ������������� ����������� ����������� ����������, ����������� ��������� ����
 * ��������� (unordered_set, unordered_multiset).
 *
 * @tparam Archive ��� �������� ������
 * @tparam UnorderedSet ��� ���������������� ���������� (std::unordered_set ���
 * std::unordered_multiset)
 * @param ar ������ �� ������� �����
 * @param set ������ �� ��������������� ���������
 */
template <class Archive, class UnorderedSet>
void loadUnorderedSet(Archive& ar, UnorderedSet& set) {
    SizeType size, bucketCount;
    ar >> makeSizeWrapper(size) >> makeSizeWrapper(bucketCount);

    set.clear();
    set.rehash(bucketCount);

    for (SizeType i = 0; i < size; i++) {
        typename UnorderedSet::key_type key;

        ar >> key;
        set.insert(std::move(key));
    }
}
} // namespace Concepts
} // namespace KtSerial
