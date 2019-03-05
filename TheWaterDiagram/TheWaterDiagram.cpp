#include <iostream>
#include <sstream>

#include <vector>
#include <map>

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
	vector<int> fieldConfiguration;
		
	if (NO_PARAMS_PASS == argc)
	{
		string defaultField = "5,2,1,1,0,1,1,2,2,4";	
		cout << "Uses default field configuration " << defaultField << endl;
		convertStringToContainer(defaultField, fieldConfiguration);
	}
	else
	{
		cout << "Uses user field configuration " << argv << endl;
		convertStringToContainer(string(argv[1]), fieldConfiguration);
	}

	
	//for(auto x : sortedFieldConfiguration)
	//	cout << x.first << " " << x.second << endl;
	
	return 0;
}
