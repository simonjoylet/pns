#ifndef MY_SINGLETON_H
#define MY_SINGLETON_H

class MY_BASE_API MySingleton
{
public:
	static MySingleton * GetInstance();

private:
	MySingleton() {}
	MySingleton(const MySingleton &);
};

#endif//MY_SINGLETON_H
