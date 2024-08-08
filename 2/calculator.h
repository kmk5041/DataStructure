#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"


Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators

double compute(char c, double a, double b){
	double num;
	if(c=='+')
		num=a+b;
	else if(c=='-')
		num=a-b;
	else if(c=='*')
		num=a*b;
	else if(c=='/')
		num=a/b;
	return num;
}


//
// Modify Eval() below to evaluate the given expression
//
double Eval(char* in)
{
	double out = 0;
	double a,b=0;
	
	char buf[1000]; // temp buffer
	char lastToken = '#';
	
	double operand;
	int i = 0, bi = 0, state = 0;
	char k;

	opt.Push('#');
		
	while(in[i] != '\0'){
		
		char c = in[i];
		for(int pp=i-1; pp>=0; pp--)
		{
			if(in[pp]!=' '){
				k=in[pp];
				break;
			}
			if(pp==0)
				k='$';
		
		}
		
		// Operators
		if(c == '+' || c == '-' ||
		   c == '*' || c == '/' ||
		   c == '(' || c == ')')
		{
			if(bi > 0)
			{
				buf[bi++] = '\0';
				operand = atof(buf);				
				bi = 0;
				if(state ==-1){
					operand*=-1;
					state =0;
				}
				
				// push operand
				opr.Push(operand);
			}

			if(c=='-')
			{
				if(i==0)
					state=-1;
				else if(k==')' || k=='0' || k=='1' || k=='2' || k=='3' || k=='4' || k=='5' || k=='6' || k=='7' || k=='8' || k=='9'){
					if(opt.Size()!=1)
					{
						if(opt.Top()=='(')
							opt.Push(c);
						else{
							a=opr.Top();
							opr.Pop();
							b=opr.Top();
							opr.Pop();
							opr.Push(compute(opt.Top(),b,a));
							opt.Pop();
							opt.Push(c);
						}
						
					}
					else{
						opt.Push(c);
					}
				}

				else{
					state=-1;
				}
			}

			else if(c=='+')
			{
				if(opt.Size()!=1)
				{
					if(opt.Top()=='(')
						opt.Push(c);
					else{
						a=opr.Top();
						opr.Pop();
						b=opr.Top();
						opr.Pop();
						opr.Push(compute(opt.Top(),b,a));
						opt.Pop();
						opt.Push(c);
					}
				}
				else{
					opt.Push(c);
				}
			}
			else if(c=='*' || c=='/'){

				if(opt.Size()!=1)
				{
					if(opt.Top()=='*' || opt.Top()=='/')
					{
						a=opr.Top();
						opr.Pop();
						b=opr.Top();
						opr.Pop();
						opr.Push(compute(opt.Top(),b,a));
						opt.Pop();
						opt.Push(c);
					}
					else
						opt.Push(c);
				}
				else
					opt.Push(c);
			}
			else if(c=='(')
				opt.Push(c);
			else if(c==')')
			{
				while(opt.Top()!='('){
					a=opr.Top();
					opr.Pop();
					b=opr.Top();
					opr.Pop();
					opr.Push(compute(opt.Top(),b,a));
					opt.Pop();
				}
				opt.Pop();
			}

		}
		// Operands
		else if(c == '0' || c == '1' ||
				c == '2' || c == '3' ||
				c == '4' || c == '5' ||
				c == '6' || c == '7' ||
				c == '8' || c == '9' ||
				c == '.')
		{
			buf[bi++] = c;
		}
		else {}
	
		i++;
	}
	
	// push the very last operand if exists
	if(bi > 0)
	{
		buf[bi++] = '\0';
		operand = atof(buf);
		bi = 0;
		if(state==-1)
		{
			operand*=-1;
			state=0;
		}
		
		// push operand
		opr.Push(operand);
	}

	if(opt.Size()!=1)
	{
		while(opt.Top()!='#')
		{
			a=opr.Top();
			opr.Pop();
			b=opr.Top();
			opr.Pop();
			opr.Push(compute(opt.Top(),b,a));
			opt.Pop();
		}
		out=opr.Top();
	}

	else{
		out=opr.Top();
	}
	opr.Pop();
	opt.Pop();
		
	return out;	
}

#endif
