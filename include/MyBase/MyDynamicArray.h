#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H
/**
* ��̬����
* ��ע�⡿��������ϵ�˼·����δ���ƣ�Ŀǰ��������
* Ԥ�ȷ���ָ��ռ䣬Ȼ�������Ҫ�����������ݿռ䣬�Ѿ���������ݵ�ַ����仯
* ʱ�临�Ӷȣ�����������ʶ���һ��ָ����ۣ��������Ժ���
* �ռ临�Ӷȣ�ֻ����8K��ָ��ռ䣬����ͬ����С
*/
class MyDynamicArray
{
private:
	struct Items
	{
		int item[1024];
	};

	Items * m_array[2048];
	pns::Uint m_size;

public:


	// ��ȡ����Ԫ��
	int & operator [](int index);

	// �������ӿռ�
	pns::Bool Realloc(pns::Uint size);

	// ��ȡ���鵱ǰ��С
	pns::Uint Size();
};



#endif//MY_DYNAMIC_ARRAY_H