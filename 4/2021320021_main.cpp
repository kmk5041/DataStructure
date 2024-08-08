/** 
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 11. 21
  *
  */
  
#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <iostream>
 
using namespace std;

int main()
{
	typedef Entry<int, float> EntryType;

	LinkedBinaryTree<EntryType> t;
	
	std::cout << "Size : " << t.size() << std::endl;
	
	t.addRoot();
	
	std::cout << "Size : " << t.size() << std::endl;
	
	
	//
	//
	//
	SearchTree<EntryType>	st;
	
	// random test
	int nElem = 100;
	
	std::srand(std::time(0)); // use current time as seed for random generator
   
		  
	// initialize

	for(int hh=0; hh<3; hh++){
		nElem*=10;
		int *key=new int[nElem];
		float *val = new float[nElem];

		int *keykey=new int[nElem];
		float *valval = new float[nElem];
		for(int i=0; i<nElem; i++)
		{
			key[i] = (std::rand()%nElem) +1;
			val[i]=(float)std::rand() / RAND_MAX * 2000;
		}
		for(int i=0; i<nElem; i++)
		{
			keykey[i]=i;
			valval[i]=(float)std::rand() / RAND_MAX * 2000;
		}
   
    SearchTree<EntryType>	st;
    AVLTree<EntryType> avl;
    SearchTree<EntryType>	st2;
    AVLTree<EntryType> avl2;
  //
  // AVL tree Insert test
  //	
  		
		clock_t tm;
		
		tm=clock();
		printf("%d elements\n",nElem);
		for(int i=0; i<nElem; i++)
		{
			st.insert(key[i], val[i]);
		}
		tm =clock() - tm;
		printf("BST Insert(random) took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);

 		tm = clock();
		for(int i=0; i<nElem; i++)
		{
			avl.insert(key[i], val[i]);
		}
		tm = clock() - tm;
		printf ("AVL Insert(random) took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
		

  //
  // AVL tree Find test
 		tm =clock();
		for(int i=0; i<nElem; i++)
		{
			st.find(key[i]);
		}
		tm=clock() - tm;
		printf("BST find(random) took me %f seconds. \n", ((float)tm)/(float)CLOCKS_PER_SEC);

		tm = clock();
		for(int i=0; i<nElem; i++)
		{
			avl.find(key[i]);
		}
		tm = clock() - tm;
		printf ("AVL find(random) took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
		
		tm=clock();
		for(int i=0; i<nElem; i++)
		{
			st2.insert(keykey[i],valval[i]);
		}
		tm=clock()-tm;
		printf("BST Insert(skewed) took me %f seconds. \n",((float)tm)/(float)CLOCKS_PER_SEC);

		tm=clock();
		for(int i=0; i<nElem; i++)
		{
			avl2.insert(keykey[i], valval[i]);
		}
		tm=clock()-tm;
		printf("AVL Insert(skewed) took me %f seconds. \n",((float)tm)/(float)CLOCKS_PER_SEC);

		tm=clock();
		for(int i=0; i<nElem; i++)
		{
			st2.find(keykey[i]);
		}
		tm=clock()-tm;
		printf("BST find(skewed) took me %f seconds. \n", ((float)tm)/(float)CLOCKS_PER_SEC);

		tm=clock();
		for(int i=0; i<nElem; i++)
		{
			avl2.find(keykey[i]);
		}
		tm=clock()-tm;
		printf("AVL find(skewed) took me %f seconds. \n", ((float)tm)/(float)CLOCKS_PER_SEC);


		delete [] key;
		delete [] val;
		delete [] keykey;
		delete [] valval;

	}
		

	return 0;
}