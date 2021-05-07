#pragma once

#include "kt-serial/details/wrappers.h"

namespace KtSerial {
/**
 * @brief ������� ��� �������� ������������ ������-������� ��� ���������� ��
 * ������������� ������ ��� ������������ ��� �������� �������. ������������
 * �������� ������ ����� ������� ���������������� ������ ������ ������� �
 * ������� ������������ �������� ������, ��� ��� �� ������� ������ ��������
 * ����������� ������� ������������ (����� ������� save/load/serialize ���
 * ��������������� ������).
 * 
 * @tparam Base ��� �������� ������ �������������� �������
 * @tparam Derived ��� ������ �������������� ������� (����������� �����)
 * @param derived ��������� �� ������������� ������ (this)
 */
template <class Base, class Derived>
BaseObjectWrapper<Base> baseObject(const Derived* derived) {
    return makeBaseObjectWrapper<Base>(derived);
}
} // namespace KtSerial
