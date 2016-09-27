#ifndef MY_BASE_API_H
#define MY_BASE_API_H

#ifndef MY_BASE_API
#define MY_BASE_API __declspec(dllimport)
#else
#define MY_BASE_API __declspec(dllexport)
#endif

#define DISALLOW_COPYING(class_name) private:\
class_name(const class_name &);\
void operator=(const class_name &)


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>


#endif//MY_BASE_API_H