#include <cstdio>
#include <array>

class BloomFilter
{
	char * m_bit_array = NULL;
	size_t m_bit_array_size = 0;
	size_t m_num_hashes = 0;
	
public:
	
	BloomFilter(size_t k, size_t m);	
	~BloomFilter();
	
	bool New(size_t vec_size);

	void Insert(const std::string & element);
	bool Check(const std::string & element);
		
	void Print() const;
	
private:

	void Init_bit_array(size_t m);

	bool Get_bit(size_t n) const;
	void Set_bit(size_t n, bool val);

	uint64_t Nth_hash(uint8_t n, uint64_t hash_A, uint64_t hash_B, uint64_t filter_size) const;
	std::array<uint64_t, 2> Get_hash(const std::string & element);
};
