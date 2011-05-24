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

		T *get(uint64_t key);

	private:
		T table[CFG_T_TABLE_SIZE];

};

template <class T>
Hashtable<T>::Hashtable()
{
	memset(table, 0, sizeof(T)*(CFG_T_TABLE_SIZE));
}

template <class T>
Hashtable<T>::~Hashtable()
{
	delete table;
}

template <class T>
T *Hashtable<T>::get(uint64_t key)
{
	return &table[key%CFG_T_TABLE_SIZE];
}

#endif

