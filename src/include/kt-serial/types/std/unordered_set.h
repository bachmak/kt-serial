#pragma once

#include <unordered_set>

#include "kt-serial/types/common.h"
#include "kt-serial/types/std/concepts/unordered_set.h"

namespace KtSerial {
/**
 * @brief ���������� ������� ��� ������������ ���������� std::unordered_set.
 * 
 * @tparam Key ��� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� ��������� ������
 * @param ar ������ �� �����
 * @param set ������������� ���������
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar, const std::unordered_set<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::saveUnorderedSet(ar, set);
}

/**
 * @brief ���������� ������� ��� ������������ ���������� std::unordered_multiset.
 * 
 * @tparam Key ��� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� ��������� ������
 * @param ar ������ �� �����
 * @param set ������������� ���������
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_SAVE_FUNCTION(
    Archive& ar,
    const std::unordered_multiset<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::saveUnorderedSet(ar, set);
}

/**
 * @brief ���������� ������� ��� �������������� ���������� std::unordered_set.
 * 
 * @tparam Key ��� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� �������� ������
 * @param ar ������ �� �����
 * @param set ������������� ���������
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar, std::unordered_set<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::loadUnorderedSet(ar, set);
}

/**
 * @brief ���������� ������� ��� �������������� ���������� std::unordered_multiset.
 * 
 * @tparam Key ��� ��������� ����������
 * @tparam Hash ���-�������
 * @tparam KeyEqual ����������
 * @tparam Alloc ���������
 * @tparam Archive ��� �������� ������
 * @param ar ������ �� �����
 * @param set ������������� ���������
 */
template <class Key, class Hash, class KeyEqual, class Alloc, class Archive>
void KTSERIAL_LOAD_FUNCTION(
    Archive& ar,
    std::unordered_multiset<Key, Hash, KeyEqual, Alloc>& set) {
    Concepts::loadUnorderedSet(ar, set);
}
} // namespace KtSerial

