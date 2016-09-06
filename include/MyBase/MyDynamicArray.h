#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H
/**
* 动态数组
* 【注意】：借鉴网上的思路，还未完善，目前还不可用
* 预先分配指针空间，然后根据需要分配具体的数据空间，已经分配的数据地址不会变化
* 时间复杂度：数组随机访问多了一次指针代价，基本可以忽略
* 空间复杂度：只多了8K的指针空间，代价同样很小
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


	// 获取数组元素
	int & operator [](int index);

	// 申请增加空间
	pns::Bool Realloc(pns::Uint size);

	// 获取数组当前大小
	pns::Uint Size();
};



#endif//MY_DYNAMIC_ARRAY_H