#pragma once

#include <utility>

#include "kt-serial/types/common.h"

namespace KtSerial {
/**
 * @brief ���������� ������� ��� ������������ ��� ����������� ����������
 * std::pair.
 *
 * @tparam T1 ��� ������� �������� ����
 * @tparam T2 ��� ������� �������� ����
 * @tparam Archive ����� ������ ��� ������������
 * @param ar ������ �� �����
 * @param p ������������� ����
 */
template <class T1, class T2, class Archive>
void KTSERIAL_SAVE_FUNCTION(Archive& ar, const std::pair<T1, T2>& p) {
    ar << makeNameValueWrapper("first", p.first)
       << makeNameValueWrapper("second", p.second);
}

/**
 * @brief ���������� ������� ��� �������������� ��� ����������� ����������
 * std::pair.
 *
 * @tparam T1 ��� ������� �������� ����
 * @tparam T2 ��� ������� �������� ����
 * @tparam Archive ����� ������ ��� ��������������
 * @param ar ������ �� �����
 * @param p ��������������� ����
 */
template <class Archive, class T1, class T2>
void KTSERIAL_LOAD_FUNCTION(Archive& ar, std::pair<T1, T2>& p) {
    ar >> makeNameValueWrapper("first", p.first) >>
        makeNameValueWrapper("second", p.second);
}
} // namespace KtSerial
