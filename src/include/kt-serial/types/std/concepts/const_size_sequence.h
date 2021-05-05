#pragma once

#include "kt-serial/types/common.h"

namespace KtSerial {
namespace Concepts {
/**
 * @brief ���������� ���������� ������� ��� ������������ ����������������
 * ����������� ����������� ����������, ������� ���������� �����.
 * 
 * @tparam Archive ��� ��������� ������
 * @tparam Sequence ��� �������������� ����������
 * @param ar ������ �� �������� �����
 * @param seq ������ �� ������������� ���������
 */
template <class Archive, class Sequence>
void saveConstSizeSequence(Archive& ar, const Sequence& seq) {
    for (const auto& value : seq) {
        ar << value;
    }
}

/**
 * @brief ���������� ���������� ������� ��� �������������� ����������������
 * ����������� ����������� ����������, ������� ���������� �����.
 * 
 * @tparam Archive ��� �������� ������
 * @tparam Sequence ��� ���������������� ����������
 * @param ar ������ �� ������� �����
 * @param seq ������ �� ��������������� ���������
 */
template <class Archive, class Sequence>
void loadConstSizeSequence(Archive& ar, Sequence& seq) {
    for (auto& value : seq) {
        ar >> value;
    }
}
} // namespace Concepts
} // namespace KtSerial

