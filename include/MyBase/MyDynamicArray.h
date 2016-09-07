#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H
/**
* 动态数组
* 【注意】：借鉴网上的思路，还未完善，目前还不可用
* 预先分配指针空间，然后根据需要分配具体的数据空间，已经分配的数据地址不会变化
* 时间复杂度：数组随机访问多了一次指针代价，基本可以忽略
* 空间复杂度：只多了8K的指针空间，代价同样很小
* 
* 使用接口还没想好，关键是有删除怎么处理还没想好
* 或者没有元素删除操作。
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

	// 设置数组大小
	pns::Bool SetSize(pns::Int itemCount, pns::Uint itemSize);
	pns::Bool Realloc(pns::Int itemCount, pns::Uint itemSize);

	// 获取数组元素
	void * operator [](pns::Int index);

	// 获取数组当前大小
	pns::Uint Size();
};



#endif//MY_DYNAMIC_ARRAY_H