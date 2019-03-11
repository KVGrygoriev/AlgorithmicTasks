#include <utility>
#include <cstdio>
#include <vector>

typedef std::pair<size_t, size_t> pairValueIndex;
typedef std::pair<size_t, size_t> firstLastIndex;

class FieldHandler 
{
	private:

		bool CheckForPlateau(const auto & _field, const size_t _leftEdge) const;
		bool CheckForPeak(const size_t _leftEdge, const size_t _rightEdge) const;
		
		auto FindLowlands(const auto & _field, const size_t _beginPos, const size_t _endPos) const;
		
		size_t CalculateFilledOutFields(const auto & _field, const auto & _lowlands) const;
	
	public:
	
		pairValueIndex GetLeftEdge(const auto & _field) const;
		pairValueIndex GetRightEdge(const auto & _field, const int _leftEdge) const;
		
		size_t GetFilledOutAmount(const std::vector<size_t> & _field) const;
};
