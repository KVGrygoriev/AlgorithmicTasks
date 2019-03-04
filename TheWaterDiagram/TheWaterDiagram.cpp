#include <iostream>
#include <sstream>

#include <vector>

using namespace std;

const int NO_PARAMS_PASS = 1;

template <class Container>
void splitStringFillContainer(const string & _srcStr, Container & _dstContainer, char _delimeter = ',')
{
    stringstream ss(_srcStr);
    string token;
    
    while (getline(ss, token, _delimeter)) {
		try
		{
			_dstContainer.push_back(stoi(token));
			
			if (_dstContainer.back() < 0)
			{
				errno = ERANGE;
				throw std::out_of_range("Value should be positive, according to task description");
			}
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
		splitStringFillContainer(defaultField, fieldConfiguration);
	}
	else
	{
		cout << "Uses user field configuration " << argv << endl;
		splitStringFillContainer(string(argv[1]), fieldConfiguration);
	}

	
	//for(auto x : fieldConfiguration)
	//	cout << x;
	
	return 0;
}
