#pragma once
#include <iostream>

template <typename type>
struct hash
{
	size_t operator()(const type& var) const
	{
		try {
			throw std::runtime_error("Data type not specified for hashing function!");
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			std::abort();
		}
		return 0;
	}
};

#define hash_for_int_like_datatypes(int_like)\
template<>\
struct hash<int_like>\
{\
	size_t operator()(const int_like& var) const\
	{\
		return static_cast<size_t>(var);\
	}\
};

hash_for_int_like_datatypes(int)
hash_for_int_like_datatypes(long)
hash_for_int_like_datatypes(long long)
hash_for_int_like_datatypes(short)
hash_for_int_like_datatypes(unsigned int)
hash_for_int_like_datatypes(unsigned long)
hash_for_int_like_datatypes(unsigned long long)
hash_for_int_like_datatypes(unsigned short)
hash_for_int_like_datatypes(char)
hash_for_int_like_datatypes(signed char)
hash_for_int_like_datatypes(unsigned char)
hash_for_int_like_datatypes(bool)

#undef hash_for_int_like_datatypes


#define hash_for_floating_point_datatypes(fp_like)\
template<>\
struct hash<fp_like>\
{\
	size_t operator()(const fp_like& var) const\
	{\
		if(var==0) return 0; else {\
		size_t result;\
		std::memcpy(&result, &var, sizeof(fp_like));\
		return result ^ (size_t)var; \
		}\
	}\
};

hash_for_floating_point_datatypes(double)
hash_for_floating_point_datatypes(long double)
hash_for_floating_point_datatypes(float)
#undef hash_for_floating_point_datatypes


template<typename type>
struct hash<type*>
{
	size_t operator()(type* var) const
	{
		size_t result = reinterpret_cast<size_t>(var);
		return (result>>3)^(result<<5);
	}
};

template<>
struct hash<std::string>
{
	size_t operator()(const std::string& var) const
	{
		size_t result = 0;
		for (const char& c : var)
		{
			result = ((result << 5) + result)+ c; //mai eficient, dar echivalent cu (result*33 + c), functia lui Daniel J. Bernstein (djb2)
		}
		return result;
	}
};