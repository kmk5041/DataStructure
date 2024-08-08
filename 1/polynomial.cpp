#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	capacity=source.capacity;
	terms=source.terms;
	termArray=new Term[capacity];
	for (int i=0; i<terms; i++)
	{
		termArray[i]=source.termArray[i];
	}
}	

// Destructor
Polynomial::~Polynomial()
{
	delete [] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	if( this != &source){
		delete [] termArray;
		capacity=source.capacity;
		terms=source.terms;
		termArray=new Term[capacity];
		for(int i=0; i<capacity; i++){
			termArray[i]=source.termArray[i];
		}
	}
	return *this;

}



// Sum of *this and source polynomials
Polynomial Polynomial::operator + (const Polynomial& source)
{
	Polynomial c;
	for (int i=0; i<terms; i++){
		c.CreateTerm(termArray[i].coef, termArray[i].exp);
	}
	for(int i=0; i<source.terms; i++){
		c.CreateTerm(source.termArray[i].coef, source.termArray[i].exp);
	}
	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;
	for (int i=0; i<terms; i++){
		c.CreateTerm(termArray[i].coef, termArray[i].exp);
	}
	for(int i=0; i<source.terms; i++){
		c.CreateTerm((source.termArray[i].coef)*-1, source.termArray[i].exp);
	}

	
	return c;
	
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
	
	for(int i=0; i<terms; i++)
	{
		for(int k=0; k<source.terms; k++)
		{
			c.CreateTerm(termArray[i].coef * source.termArray[k].coef, termArray[i].exp+source.termArray[k].exp);
		}
	}
	
	return c;	
}

bool Polynomial::operator == (const Polynomial& right)
{
	bool ret;
	ret=true;
	if(terms!=right.terms){
		ret=false;
	}
	else{
		for(int i=0; i<terms; i++)
		{
			if(termArray[i].coef!=right.termArray[i].coef || termArray[i].exp!=right.termArray[i].exp)
				ret=false;
		}
	}

	
	return ret;
}

float Polynomial::Eval(float x)
{
	float ret = 0;
	for(int i=0; i<terms; i++)
	{
		float k=(termArray[i].coef)*pow(x,termArray[i].exp);
		ret+=k;
	}
	
	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;
	for(int i=0; i<terms; i++)
	{
		if(termArray[i].exp==0)
		{
			break;
		}
		else{
			float numnum=termArray[i].exp * termArray[i].coef;
			c.CreateTerm(numnum, termArray[i].exp-1);
		}
	}

	
	
	return c;	

}

void Polynomial::CreateTerm(const float coef, const int exp)
{
	if(coef==0)
		return;
	if(terms==0)
	{
		terms++;
		termArray[0].coef=coef;
		termArray[0].exp=exp;
		return;
	}
	int num=-1;
	for(int i=0; i<terms; i++)
	{
		if(exp==termArray[i].exp){
			num=i;
			break;
		}
		
		  
	}
	
	if(num!=-1)
	{
		(termArray+num)->coef+=coef;
		if (termArray[num].coef==0)
		{
			for(int i=num; i<terms-1; i++)
			{
				termArray[i].coef=termArray[i+1].coef;
				termArray[i].exp=termArray[i+1].exp;
			}
			terms--;
		}
	}
	else
	{
		terms++;
		if(terms<=capacity)
		{
			termArray[terms-1].coef=coef;
			termArray[terms-1].exp=exp;
		}
		else
		{
			capacity++;
			Term *newarray= new Term[capacity];
			for(int i=0; i<capacity-1; i++)
			{
				newarray[i].coef=termArray[i].coef;
				newarray[i].exp=termArray[i].exp;
			}
			newarray[capacity-1].coef=coef;
			newarray[capacity-1].exp=exp;
			delete [] termArray;
			termArray=new Term[capacity];
			for(int i=0; i<capacity; i++)
			{
				termArray[i].coef=newarray[i].coef;
				termArray[i].exp=newarray[i].exp;
			}
			delete [] newarray;

		}
		//sort
		for( int i=terms-1; i>0; i--)
		{
			for(int j=0; j<i; j++)
			{
				Term nn;
				if(termArray[j].exp<termArray[j+1].exp)
				{
					nn.exp=termArray[j].exp;
					nn.coef=termArray[j].coef;
					termArray[j].exp=termArray[j+1].exp;
					termArray[j].coef=termArray[j+1].coef;
					termArray[j+1].exp=nn.exp;
					termArray[j+1].coef=nn.coef;
				}
			}
		}

	}



}

