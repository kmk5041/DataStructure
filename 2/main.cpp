#include "stack.h"
#include "calculator.h"
#include <iostream>

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

// stack & calculator test

int main()
{
	// Stack test
	Stack<int> s;
	
	s.Push(23);
	s.Push(102);
	s.Print();
	printf("--\n");
	
	s.Push(345);
	s.Push(77);
	s.Print();
	printf("--\n");
	
	s.Pop();
	s.Push(678);
	s.Push(91011);
	s.Print();
	printf("--\n");
	
	for(int i=0; i<6; i++)
	{
		try {
			s.Pop();
			std::cout << "Pop() is called" << std::endl;
		}
		catch(const char* message)
		{
			std::cout << message << std::endl;
		}		
	}

	// Calculator test
	char str1[] ="3+9+(8/2)";
	// The correct result is 101372
	double res1 = Eval(str1);
	std::cout << "Result : " << res1 << std::endl;

	char str3[] = "10*5*-2";
	double res3 = Eval(str3);
	std::cout<< "Result : "<<res3 << std::endl;
	
	
	char str2[] = "1.2 + 2.4 + 3.0*2";
	// The correct result is 9.6
	double res2 = Eval(str2);
	std::cout << "Result : " << res2 << std::endl;
		
	return 0;
}
