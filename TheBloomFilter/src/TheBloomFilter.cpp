#include <cstdio>
#include <iostream>

#include "BloomFilter.h"

using namespace std;

int main()
{
	/*
	size_t k = 23;
	size_t m = 33548945;
	*/
	
	size_t k = 2;
	size_t m = 10;
	
	BloomFilter blomFilter(m, k);
	
	const string val = "123";
	const string val2 = "124";
	const string val3 = "121123";
	blomFilter.Insert(val2);
	cout << "Check result is " << blomFilter.Check(val3) << endl;
	
	blomFilter.Print();
	
	return 0;
}
