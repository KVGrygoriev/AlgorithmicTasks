#include <cstdio>
#include <iostream>
#include <fstream>

#include "BloomFilter.h"

using namespace std;

template<typename Lambda>
void Do_with_all_lines_from_file(const string & file_name, BloomFilter & bloom_filter, Lambda lambda)
{
	string line;
	
	ifstream file(file_name);
	
	if (file.is_open())
	{
		while (getline(file, line))
			lambda(bloom_filter, line);
		
		file.close();
	}
}

int main()
{
	const size_t k = 23;
	const size_t m = 33548945;

	const string src_file = "../h1.txt";
	const string dst_file = "../h2.txt";
	
	const auto Generate_bloom_filter = 
	[](BloomFilter & bloom_filter, const string & line) 
	{
		bloom_filter.Insert(line);
	};
	
	const auto Print_matched_values_from_bloom_filter = 
	[](BloomFilter & bloom_filter, const string & line) 
	{
		if (bloom_filter.Check(line))
			cout << line << endl;
	};
	
	
	BloomFilter bloomFilter(k, m);
	
	Do_with_all_lines_from_file(src_file, bloomFilter, Generate_bloom_filter);
	Do_with_all_lines_from_file(dst_file, bloomFilter, Print_matched_values_from_bloom_filter);

	return 0;
}
