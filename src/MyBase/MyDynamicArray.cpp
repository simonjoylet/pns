#define MY_BASE_API __declspec(dllexport)
#include "MyBase/MyBase.h"
using namespace pns;


// int * MyDynamicArray::get(int index)
// {
// 	if (index >= 0 && index < m_size)
// 	{
// 		int majorIndex = index / 1024;
// 		int minorIndex = index % 1024;
// 		return &m_array[majorIndex]->item[minorIndex];
// 	}
// 	return NULL;
// }
// 
// int MyDynamicArray::reloc(int size)
// {
// 	if (size >= 1024 * 2048) return -1; // Ԫ��̫��
// 	while (m_size < size)
// 	{
// 		int index = m_size / 1024;
// 		m_array[index] = (Items *)calloc(1, sizeof(Items));
// 		if (m_array[index] == NULL) return -1; // �ڴ����ʧ��
// 		m_size += 1024;
// 	}
// 	return 0;
// }
// 
// int * MyDynamicArray::operator[](int index)
// {
// 
// }
