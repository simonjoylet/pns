#ifndef MY_BASE_API_H
#define MY_BASE_API_H

#ifndef MY_BASE_API
#define MY_BASE_API __declspec(dllimport)
#else
#define MY_BASE_API __declspec(dllexport)
#endif

#endif//MY_BASE_API_H