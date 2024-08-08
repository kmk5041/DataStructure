//
// - Implementation -
//

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
	capacity=c;
	divisor=5;
	mapsize=0;
	ht= new HashMapElemType*[capacity];
	for(int i=0; i<capacity; i++){
		ht[i]= NULL;
	}
	
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	HashMapElemType* p;
	HashMapElemType* cur;
	for(int i=0; i<capacity;i++){
	cur=ht[i];	
	if(cur==NULL){
		break;
	}
	p=cur->link;
	while(p!=NULL){
		delete cur;
		cur=p;
		p=p->link;
	}
	delete cur;
	}
	delete[] ht;
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{ 
	HashMapElemType* pair;
	int key=hashfunction(k);
	pair=ht[key];
	while(pair!=NULL){
		if(pair->key==k){
			return pair;
		}
		else{
		pair=pair->link;
		}
	}
	return pair;	
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
	int key=hashfunction(k);
	HashMapElemType* pair=ht[key];
	HashMapElemType* pre=pair;
	while(pair!=NULL){
	if(pair->key==k){
		pair->val=v;
		return;
		}
	else{
		pre=pair;
		pair=pair->link;
	}
	}

	HashMapElemType* newnew=new HashMapElemType;
	if(pre==NULL){
		ht[key]=newnew;
		newnew->key=k;
		newnew->val=v;
		newnew->link=NULL;
		mapsize++;
		return;
		}	
	pre->link=newnew;
	newnew->key=k;
	newnew->val=v;
	newnew->link=NULL;
	mapsize++;
	
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
	int key=hashfunction(k);
	HashMapElemType* pair=ht[key];
	HashMapElemType* pre=pair;
	while(pair!=NULL){

		if(pair->key==k){
			pre->link=pair->link;
			delete pair;
			mapsize--;
			return true;
		}
		else{
			pre=pair;
			pair=pair->link;
		}
	}
	return false;
		
}

template <class HashMapElemType>
unsigned int HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	int number=0;
	int index=0;
	while(index<k.length()){
		number+= int(k[index]) <<8*(index%4);
		index++;
		}
	number=number%divisor;
	return number;
}

template <class HashMapElemType>
void HashMap<HashMapElemType>::print()
{
	for(int i=0; i<divisor; i++){
		HashMapElemType* pair=ht[i];
		while(pair!=NULL){
			std::cout<<pair->key<<":"<<pair->val<<std::endl;
			pair=pair->link;
		}
	}

}
