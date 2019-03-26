#include <stdexcept>
#include <iostream>

#include "MurmurHash3.h"
#include "BloomFilter.h"

using namespace std;

BloomFilter::BloomFilter(size_t k, size_t m)
{
	Init_bit_array(m);
	m_num_hashes = k;
}

BloomFilter::~BloomFilter()
{
	delete[] m_bit_array;
}

void BloomFilter::Init_bit_array(size_t m)
{
	if (m_bit_array != NULL)
		delete[] m_bit_array;
		
	m_bit_array = new char[m];
	m_bit_array_size = m;
}

bool BloomFilter::New(size_t vec_size)
{
	Init_bit_array(vec_size);
	
	return true;
}

bool BloomFilter::Get_bit(size_t n) const
{
	if (n >= m_bit_array_size)
		throw out_of_range("Out of range");
		
	return m_bit_array[n];
}

void BloomFilter::Set_bit(size_t n, bool val)
{
	if (n >= m_bit_array_size)
		throw out_of_range("Out of range");
	else
		m_bit_array[n] = val;
}

void BloomFilter::Print() const
{
	cout << "Bit array:" << endl;
	
	for (size_t i = 0; i < m_bit_array_size; ++i)
		cout << (int)m_bit_array[i] << " ";
		
	cout << endl;
}

void BloomFilter::Insert(const string & element)
{
	auto hash = Get_hash(element);

	for (size_t i = 0; i < m_num_hashes; ++i) 
		Set_bit(Nth_hash(i, hash[0], hash[1], m_bit_array_size), true);
}

bool BloomFilter::Check(const string & element)
{
	auto hash = Get_hash(element);
	
	for (size_t i = 0; i < m_num_hashes; ++i)
	{
		if (!Get_bit(Nth_hash(i, hash[0], hash[1], m_bit_array_size)))
			return false;
	}
	
	return true;
}

inline uint64_t BloomFilter::Nth_hash(uint8_t n, uint64_t hash_A, uint64_t hash_B, uint64_t filter_size) const
{
	return (hash_A + n * hash_B) % filter_size;
}

array<uint64_t, 2> BloomFilter::Get_hash(const string & element)
{
	array<uint64_t, 2> hash_value;
	
	MurmurHash3_x64_128((const void*)element.c_str(), (int)element.length(), 0, hash_value.data());
	
	return hash_value;
}
