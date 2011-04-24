#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "config.h"

#include <stdint.h>
#include <string.h>

template <class T>
class Hashtable
{

	public:
		Hashtable();
		~Hashtable();

		T *get(uint64_t key) const;
		void set(uint64_t key, T *value);

	private:
		T **table;

};

template <class T>
Hashtable<T>::Hashtable()
{
	table = new T*[2 << 16];
	memset(table, 0, sizeof(T*)*(2<<16));
}

template <class T>
Hashtable<T>::~Hashtable()
{
	delete table;
}

template <class T>
T *Hashtable<T>::get(uint64_t key) const
{
	return table[(short)key];
}

template <class T>
void Hashtable<T>::set(uint64_t key, T *value)
{
	table[(short)key] = value;
}

#endif

