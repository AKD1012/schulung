#include <stdio.h>
#include <iostream>
#include <string>
#include <map>


int main()
{
	std::map<int, std::string> myMap;
	// @Step1: Implement and call fillMapWithRandomObjects function
	//  it should be possible to specify the amount of elements to be added via function parameter
	//  the functions signature should be void
	//  for each element added to the map, the string member should be generated with "randomStrGen" (see generate_randomstring.h)
	//   the map's key should be an index (counter)
	// void fillMapWithRandomObjects(...)
	// @Step2: Implement and call cStylePrintMap function to print the content of the map using printf to generate output to console
	//  the function signature should be void
	// void cStylePrintMap(..);
	// @Step3: Implement and call removeElementByKey function to remove the element of the map for the given key
	//  the function signature should be void
	// void removeElementByKey(...)
	// @Step4: Implement and call cppStylePrintMap function to print the content of the map using std::cout to generate output to console
	//  the function signature should be void
	// void cppStylePrintMap(...);
	// @Step5: Implement and call addElementToMap function that adds a new Element to the map with given key and string. 
	//  note: if there is already an existing element for the given key, print an error msg and do not add the given id and string
	//  the function signature should be void
	// void addElementToMap(..., int, std::string)
	// @Step6: Print the content of the map using either cStylePrintMap or cppStylePrintMap function

	std::cin.get();
	return 0;
}
