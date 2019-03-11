#include "FieldHandler.h"

#include <iostream>

using namespace std;

bool FieldHandler::CheckForPlateau(const auto & _field, const size_t _leftEdge) const
{
	if ((_field.size() - 1) == _leftEdge)
	{
		cout << "It's a plateau!" << endl;
		return true;
	}
	
	return false;
}

bool FieldHandler::CheckForPeak(const size_t _leftEdge, const size_t _rightEdge) const
{
	if (_leftEdge == _rightEdge)
	{
		cout << "It's a peak!" << endl;
		return true;
	}
	
	return false;
}

pairValueIndex FieldHandler::GetLeftEdge(const auto & _field) const
{
	pairValueIndex edge {0,0};
	
	for (size_t index = 0;
		index < _field.size() && edge.first <= _field[index];
		++index)
	{
		edge.first = _field[index];
		edge.second = index;
	}
	
	//cout << "Left edge.  Value " << edge.first << ", index " << edge.second << endl;
	return edge;
}

pairValueIndex FieldHandler::GetRightEdge(const auto & _field, const int _leftEdge) const
{
	pairValueIndex edge {0,0};
	for (int index = static_cast<int>(_field.size() - 1);
		index >= _leftEdge && edge.first <= _field[index];
		--index)
	{
		edge.first = _field[index];
		edge.second = index;
	}
	
	//cout << "Right edge. Value " << edge.first << ", index " << edge.second << endl << endl;

	return edge;
}

auto FieldHandler::FindLowlands(const auto & _field, const size_t _beginPos, const size_t _endPos) const
{
	vector<firstLastIndex> lowlands;
	size_t index {0}, currentTopPosition {0};
	size_t currentLowlandBeginPos = _beginPos;
	bool goTop = false;

	firstLastIndex currentItem {currentLowlandBeginPos,0};
	
	for (index = _beginPos + 1; index < _endPos; ++index)
	{
		
		if (_field[index] > _field[currentLowlandBeginPos])
		{
			currentTopPosition = index;
			goTop = true;
		}
		else
		{
			if ((_field[index] < _field[currentLowlandBeginPos]) && goTop)
			{
				currentItem.second = currentTopPosition;
				currentLowlandBeginPos = currentTopPosition;
				goTop = false;

				lowlands.push_back(currentItem);
				
				currentItem = {currentLowlandBeginPos,0};
			}
		}
	}
	
	lowlands.push_back(firstLastIndex(currentLowlandBeginPos, index));
	
	return lowlands;
}

size_t FieldHandler::CalculateFilledOutFields(const auto & _field, const auto & _lowlands) const
{
	size_t totalFilled {0};
	
	for (const auto item : _lowlands)
	{
		size_t minLevel = min(_field[item.first], _field[item.second]);
		
		for (size_t index = item.first + 1; index < item.second; ++index)
			totalFilled += minLevel - _field[index];
	}
	
	return totalFilled;
}

size_t FieldHandler::GetFilledOutAmount(const vector<size_t> & _field) const
{
	const pairValueIndex leftEdge = GetLeftEdge(_field);
	
	if (CheckForPlateau(_field, leftEdge.second))
		return 0;


	const pairValueIndex rightEdge = GetRightEdge(_field, leftEdge.second);
	
	if (CheckForPeak(leftEdge.second, rightEdge.second))
		return 0;


	auto lowlands = FindLowlands(_field, leftEdge.second, rightEdge.second);
	
	return CalculateFilledOutFields(_field, lowlands);
}
