#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "generate_randomstring.h"

struct MyStruct
{
	int iIdx;
	std::string strVal;
};

int main()
{
	// create a std::vector of type MyStruct 
	std::vector<MyStruct> vec;
	// @Step1: Implement and call fillVectorWithRandomObjects function
	//  it should be possible to specify the amount of elements to be added via function parameter
	//  the functions signature should be void
	//  for each element added to the vector, the string member should be generated with "randomStrGen" (see generate_randomstring.h)
	//   the int value should be an index (counter)
	// void fillVectorWithRandomObjects(...)
	// @Step2: Implement and call cStylePrintVector function to print the content of the vector using printf to generate output to console
	//  the function signature should be void
	// void cStylePrintVector(..);
	// @Step3: Implement and call sortObjectsAlphabetically function to sort the elements inside the vector in alphabetic order using the member strVal
	//  the function signature should be void
	// void sortObjectsAlphabetically(...)
	// @Step4: Implement and call cppStylePrintVector function to print the content of the vector using std::cout to generate output to console
	//  the function signature should be void
	// void cppStylePrintVector(...);
	// @Step5: Implement and call sortObjectsByIdxDesc function to sort the elements inside the vector in Descending order using the member iIdx
	//  the function signature should be voi
	// void sortObjectsByIdxDesc(...)
	// @Step6: Print the content of the vector using either cStylePrintVector or cppStylePrintVector function

	std::cin.get();
	return 0;
}
