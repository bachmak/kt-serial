#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial {
namespace Concepts {
/**
 * @brief ���������� ���������� ������� ��� ������������ �������������
 * ����������� ����������� ���������, ����������� ��������� ���� ������� (map,
 * multimap).
 * 
 * @tparam Archive ��� ��������� ������
 * @tparam Map ��� �������������� ���������� (std::map ��� std::multimap)
 * @param ar ������ �� �������� �����
 * @param map ������ �� ������������� ���������
 */
template <class Archive, class Map> void saveMap(Archive& ar, const Map& map) {
    ar << makeSizeWrapper(map.size());

    for (const auto& item : map) {
        auto wrapper = makeKeyValueWrapper(item.first, item.second);
        ar << wrapper;
    }
}

/**
 * @brief ���������� ���������� ������� ��� �������������� �������������
 * ����������� ����������� ���������, ����������� ��������� ���� ������� (map,
 * multimap).
 * 
 * @tparam Archive ��� �������� ������
 * @tparam Map ��� ���������������� ���������� (std::map ��� std::multimap)
 * @param ar ������ �� ������� �����
 * @param map ������ �� ��������������� ���������
 */
template <class Archive, class Map> void loadMap(Archive& ar, Map& map) {
    SizeType size;
    ar >> makeSizeWrapper(size);
    map.clear();
    auto hint = map.begin();

    for (SizeType i = 0; i < size; i++) {
        typename Map::key_type key;
        typename Map::mapped_type value;
        auto wrapper = makeKeyValueWrapper(key, value);
        ar >> wrapper;
        hint = std::next(
            map.insert(hint, std::make_pair(std::move(key), std::move(value))));
    }
}
} // namespace Concepts
} // namespace KtSerial
