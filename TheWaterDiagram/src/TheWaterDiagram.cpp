#include <iostream>
#include <sstream>

#include <vector>

#include "FieldHandler.h"

using namespace std;

const int NO_PARAMS_PASS = 1;

template <class Container>
void convertStringToContainer(const string & _srcStr, Container & _dstContainer, char _delimeter = ',')
{
    stringstream ss(_srcStr);
    string token;
    
    while (getline(ss, token, _delimeter)) {
		try
		{
			auto convertedValue = stoi(token);
			
			if (convertedValue < 0)
			{
				errno = ERANGE;
				throw std::out_of_range("Value should be positive, according to task description");
			}
			
			_dstContainer.push_back(convertedValue);
		}
		catch (const std::exception& e)
		{
			cout << "Oops. Data is broken. " << e.what();
			exit(EXIT_FAILURE);
		}
    }
}

		
int main(int argc, char* argv[])
{
	vector<size_t> fieldConfiguration;
		
	if (NO_PARAMS_PASS == argc)
	{
		string defaultField = "5,2,1,1,0,1,1,2,2,4"; //22
		//string defaultField = "1,1,2,3,5,3,2,1,0,0"; //0
		//string defaultField = "1,1,1"; //0
		//string defaultField = "4,1,6,1,2"; //4
		//string defaultField = "2,1,6,1,4"; //4
		//string defaultField = "1,4,1,6,1,2,1"; //4
		//string defaultField = "1,2,3,3,4,1,1,2,1,6,1,2,1"; //12
		
		cout << "Uses default field configuration " << defaultField << endl;
		convertStringToContainer(defaultField, fieldConfiguration);
	}
	else
	{
		cout << "Uses user field configuration " << argv[1] << endl;
		convertStringToContainer(string(argv[1]), fieldConfiguration);
	}

	const FieldHandler fieldHandler;
	size_t filled = fieldHandler.GetFilledOutAmount(fieldConfiguration);
	
	cout << "Amount of filled out fields is " << filled << endl;
	
	return EXIT_SUCCESS;
}
