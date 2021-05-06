#pragma once

#include <unordered_map>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/unordered_map.h"

namespace KtSerial {
/**
 * @brief ���������� ������� ��� ������������ ���������� std::unordered_map.
 *
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� ��������� ������
 * @param ar ������ �� �����
 * @param map ������������� ���������
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar, const std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::saveUnorderedMap(ar, map);
}

/**
 * @brief ���������� ������� ��� ������������ ����������
 * std::unordered_multimap.
 *
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� ��������� ������
 * @param ar ������ �� �����
 * @param map ������������� ���������
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar,
    const std::unordered_multimap<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::saveUnorderedMap(ar, map);
}

/**
 * @brief ���������� ������� ��� �������������� ���������� std::unordered_map.
 *
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� �������� ������
 * @param ar ������ �� �����
 * @param map ��������������� ���������
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar, std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::loadUnorderedMap(ar, map);
}

/**
 * @brief ���������� ������� ��� �������������� ����������
 * std::unordered_multimap.
 *
 * @tparam Key ��� ����� ��������� ����������
 * @tparam T ��� �������� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� �������� ������
 * @param ar ������ �� �����
 * @param map ��������������� ���������
 */
template <class Key, class T, class Hash, class KeyEqual, class Alloc,
          class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar, std::unordered_multimap<Key, T, Hash, KeyEqual, Alloc>& map) {
    Concepts::loadUnorderedMap(ar, map);
}
} // namespace KtSerial
