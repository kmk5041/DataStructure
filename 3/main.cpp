#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * 2021. 11. 1   Won-Ki Jeong
  *
  */
HashMap<MapElem<std::string,int>> dic;

void spellcheck(std::string s)
{
	std::cout << "> " << s;
	if(dic.find(s)!=NULL){
		std::cout<<" is in the dictionary"<<std::endl;
	}
	else{
		std::cout<<" is NOT in the dictionary"<<std::endl;
		std::cout<<"> "<<s<<" : ";
		std::string ss;
		ss=s;
		std::string print="";
		int numbering=0;
		for(int i=0; i<s.length(); i++){
			for(int k=97; k<123; k++)
			{
				ss[i]=k;
				if(dic.find(ss)!=NULL){
					numbering++;
					print+=ss;
					print+=", ";
				}
			}
			ss=s;
		}
		if(numbering==0){
			std::cout<<"no suggestion"<<std::endl;
			return;
		}
		print.erase(print.length()-2);
		std::cout<<print<<std::endl;
	}

}


int main()
{
	// load dictionary
	char filename[] = "dictionary.txt";
	std::ifstream ifs(filename, std::ifstream::in);
	std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	std::transform(s.begin(), s.end(),
				   s.begin(), ::tolower);

	std::string token;	
	unsigned int len = s.length();
		
	for(int i=0; i<len; i++)
	{
		int ascii = s[i];
		
		if(ascii < 97 || ascii > 127) 
		{
			if(token.length() > 0) 
			{
				// ToDo
				dic.insert(token,1);
				token.clear();
			}
			continue;
		}
		token.push_back(s[i]);
	}
	
	
	//
	// infinite loop to accept user input word
	//
	while(1)
	{
		std::string s;
		std::cout << "> ";
		std::cin >> s;
		std::string lll="book";
		for(int i=0; i<s.length(); i++){
			if(s[i]>=65&&s[i]<=90){
				s[i]=s[i]+32;
			}
		}
		
		if(s.compare("q") == 0) break;	
		
		spellcheck( s );
	}
	
	
	return 0;
}
