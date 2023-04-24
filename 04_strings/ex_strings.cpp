#include <string.h>
#include <iostream>
#include <sstream>
#include <assert.h>

#define TEXT_ARRAY_LEN 20

//Ex1: 
std::string strExample1()
{
    char text[TEXT_ARRAY_LEN] = {};
    strcpy(text, "This is StrExample1!");
    std::cout << text << "\n";

    return text;
}

//Hint: Try not to replace the stringstream
std::string strExample2()
{
    std::stringstream ssText;
    ssText << "This is StrExample2!";

    const char *text = NULL;
    text = ssText.str().c_str();
    std::cout << text << "\n";

    return text;
}

std::string strExample3()
{
    char text[TEXT_ARRAY_LEN+2] = {};

    strcpy(text, "This is ");
    strcat(text, " StrExample3!");
    std::cout << text << "\n";

    return text;
}

//Example4: Try to get the desired String out of the existing 'sText'
std::string strExample4()
{
    std::string sText;
    sText = "This is [FILLER] StrExample4!";

    std::cout << sText << "\n";

    return sText;
}

//Example5: Try to put the Chunks together to form the desired String.
//Try to do it in C-Style!
std::string strExample5()
{
    char chunk1[TEXT_ARRAY_LEN] = {"This "};
    char chunk2[TEXT_ARRAY_LEN] = {"is "};
    char chunk3[TEXT_ARRAY_LEN] = {"StrExample5!"};

    
    char text[TEXT_ARRAY_LEN+1] = {};

    std::cout << text << "\n";
    return text;
}

//Example6: Try to put the Chunks together to form the desired String.
std::string strExample6()
{
    std::string chunk1 = "This ";
    std::string chunk2 = "is ";
    std::string chunk3 = "StrExample6!";

    std::string text;
    std::cout << text << "\n";

    return text;
}

const char* strExample7()
{
    std::string sText = "This is StrExample7!";
    const char *text = sText.c_str();

    std::cout << text << "\n";

    return text;
}

int main()
{
    //In this project, there are various errors with strings / char arrays - Find them, and provide better solutions for them
    //HINT: The examples will cause a Stack smash or will abort manually if data is wrong
    assert(strExample1().compare("This is StrExample1!") == 0);

    assert(strExample2().compare("This is StrExample2!") == 0);

    assert(strExample3().compare("This is StrExample3!") == 0);

    assert(strExample4().compare("This is StrExample4!") == 0);

    assert(strExample5().compare("This is StrExample5!") == 0);
    
    assert(strExample6().compare("This is StrExample6!") == 0);

    assert(strcmp(strExample7(), "This is StrExample7!") == 0);

    std::cin.get();

    return 1;
}