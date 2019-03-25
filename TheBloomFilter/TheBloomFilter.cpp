#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <array>

#include "MurmurHash3.h"

using namespace std;

class BlomFilter
{
	char * m_bit_array = NULL;
	size_t m_bit_array_size = 0;
	size_t m_num_hashes = 0;
	
public:
	
	BlomFilter(size_t m, size_t k)
	{
		Init_bit_array(m);
		m_num_hashes = k;
	}
	
	~BlomFilter()
	{
		delete[] m_bit_array;
	}
	
	bool New(size_t vec_size)
	{
		Init_bit_array(vec_size);
		
		return true;
	}
	
	bool Get_bit(size_t n) const
	{
		if (n >= m_bit_array_size)
			throw out_of_range("Out of range");
			
		return m_bit_array[n];
	}
	
	void Set_bit(size_t n, bool val)
	{
		if (n >= m_bit_array_size)
			throw out_of_range("Out of range");
		else
			m_bit_array[n] = val;
	}
	
	void Print()
	{
		cout << "Bit array:" << endl;
		
		for (size_t i = 0; i < m_bit_array_size; ++i)
			cout << (int)m_bit_array[i] << " ";
			
		cout << endl;
	}
	
	void Insert(const string & element)
	{		
	}
	
	bool Check(const string & element) const
	{
		return false;
	}
	
	
private:

	inline uint64_t Nth_hash(uint8_t n, uint64_t hash_A, uint64_t hash_B, uint64_t filter_size) 
	{
		return (hash_A + n * hash_B) % filter_size;
	}

	array<uint64_t, 2> Get_hash(const string & element) const
	{
		array<uint64_t, 2> hash_value;
		
		MurmurHash3_x64_128(element.c_str(), element.length(), 0, hash_value.data());
		
		return hash_value;
	}

	void Init_bit_array(size_t m)
	{
		if (m_bit_array != NULL)
			delete[] m_bit_array;
			
		m_bit_array = new char[m];
		m_bit_array_size = m;
	}
};

int main()
{
	BlomFilter blomFilter(3, 2);
	blomFilter.Print();
	
	blomFilter.Set_bit(1,2);
	
	cout << blomFilter.Get_bit(1) << endl;
	blomFilter.Print();
	
	return 0;
}
