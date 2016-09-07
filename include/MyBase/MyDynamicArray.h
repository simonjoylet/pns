#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H
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
class MyDynamicArray
{
private:
	struct Items
	{
		void * item[1024];
	};

	Items * m_array[2048];
	pns::Uint m_size;

public:
	MyDynamicArray();
	~MyDynamicArray();

	// ���������С
	pns::Bool SetSize(pns::Int itemCount, pns::Uint itemSize);
	pns::Bool Realloc(pns::Int itemCount, pns::Uint itemSize);

	// ��ȡ����Ԫ��
	void * operator [](pns::Int index);

	// ��ȡ���鵱ǰ��С
	pns::Uint Size();
};



#endif//MY_DYNAMIC_ARRAY_H