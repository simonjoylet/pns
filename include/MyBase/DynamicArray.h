#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H

#include "MyBase/Common.h"

namespace pns
{

/**
* ��̬����
* ��ע�⡿��������ϵ�˼·����δ���ƣ�Ŀǰ��������
* Ԥ�ȷ���ָ��ռ䣬Ȼ�������Ҫ�����������ݿռ䣬�Ѿ���������ݵ�ַ����仯
* ʱ�临�Ӷȣ�����������ʶ���һ��ָ����ۣ��������Ժ���
* �ռ临�Ӷȣ�ֻ����8K��ָ��ռ䣬����ͬ����С
* 
* ʹ�ýӿڻ�û��ã��ؼ�����ɾ����ô����û���
* ����û��Ԫ��ɾ��������
*/
class DynamicArray
{
private:
	struct Items
	{
		void * item[1024];
	};

	Items * m_array[2048];
	uint32_t m_size;

public:
	DynamicArray();
	~DynamicArray();

	// ���������С
	bool SetSize(int32_t item_count, uint32_t item_size);
	bool Realloc(int32_t item_count, uint32_t item_size);

	// ��ȡ����Ԫ��
	void * operator [](int32_t index);

	// ��ȡ���鵱ǰ��С
	uint32_t Size();
};

} // namespace pns

#endif//MY_DYNAMIC_ARRAY_H