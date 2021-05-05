#pragma once

#include <map>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/map.h"

namespace KtSerial {
/**
 * @brief ���������� ������� ��� ������������ ���������� std::map.
 * 
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Compare ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� ��������� ������
 * @param ar ������ �� �����
 * @param map ������������� ���������
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar,
                            const std::map<Key, T, Compare, Alloc>& map) {
    Concepts::saveMap(ar, map);
}

/**
 * @brief ���������� ������� ��� ������������ ���������� std::multimap.
 * 
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Compare ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� ��������� ������
 * @param ar ������ �� �����
 * @param map ������������� ���������
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar,
                            const std::multimap<Key, T, Compare, Alloc>& map) {
    Concepts::saveMap(ar, map);
}

/**
 * @brief ���������� ������� ��� �������������� ���������� std::map.
 * 
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Compare ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� �������� ������
 * @param ar ������ �� �����
 * @param map ��������������� ���������
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar,
                            std::map<Key, T, Compare, Alloc>& map) {
    Concepts::loadMap(ar, map);
}

/**
 * @brief ���������� ������� ��� �������������� ���������� std::multimap.
 * 
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Compare ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� �������� ������
 * @param ar ������ �� �����
 * @param map ��������������� ���������
 */
template <class Key, class T, class Compare, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(Archive& ar,
                            std::multimap<Key, T, Compare, Alloc>& map) {
    Concepts::loadMap(ar, map);
}
} // namespace KtSerial
