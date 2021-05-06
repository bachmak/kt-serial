#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial {
namespace Concepts {
/**
 * @brief ���������� ���������� ������� ��� ������������ ���������������
 * ������������� ����������� ����������� ����������, ����������� ��������� ����
 * ������� (unordered_map, unordered_multimap).
 *
 * @tparam Archive ��� ��������� ������
 * @tparam UnorderedMap ��� �������������� ���������� (std::unordered_map ���
 * std::unordered_multimap)
 * @param ar ������ �� �������� �����
 * @param map ������ �� ������������� ���������
 */
template <class Archive, class UnorderedMap>
void saveUnorderedMap(Archive& ar, const UnorderedMap& map) {
    ar << makeSizeWrapper(map.size()) << makeSizeWrapper(map.bucket_count());

    for (const auto& item : map) {
        auto wrapper = makeKeyValueWrapper(item.first, item.second);
        ar << wrapper;
    }
}

/**
 * @brief ���������� ���������� ������� ��� �������������� ���������������
 * ������������� ����������� ����������� ����������, ����������� ��������� ����
 * ������� (unordered_map, unordered_multimap).
 *
 * @tparam Archive ��� �������� ������
 * @tparam UnorderedMap ��� ���������������� ���������� (std::unordered_map ���
 * std::unordered_multimap)
 * @param ar ������ �� ������� �����
 * @param map ������ �� ��������������� ���������
 */
template <class Archive, class UnorderedMap>
void loadUnorderedMap(Archive& ar, UnorderedMap& map) {
    SizeType size, bucketCount;
    ar >> makeSizeWrapper(size) >> makeSizeWrapper(bucketCount);

    map.clear();
    map.rehash(bucketCount);

    for (SizeType i = 0; i < size; i++) {
        typename UnorderedMap::key_type key;
        typename UnorderedMap::mapped_type value;
        auto wrapper = makeKeyValueWrapper(key, value);
        ar >> wrapper;
        map.insert(std::make_pair(std::move(key), std::move(value)));
    }
}
} // namespace Concepts
} // namespace KtSerial
