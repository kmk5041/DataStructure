//
// Implementation
//
template <typename E>               // constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>               // node height utility
  int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>               // set height utility
  void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));         // max of left & right
  }

template <typename E>               // is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {   
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>               // get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))         // left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else                   // right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


//
// ToDo
//

template <typename E>               // remove key k entry
  void AVLTree<E>::erase(const K& k) {
       TPos v = ST::finder(k, ST::root()); // find in base tree
   if (Iterator(v) == ST::end()) // not found?
      throw "Erase of nonexistent";
   TPos w = ST::eraser(v); // remove it
   rebalance(w); 
    
  }

template <typename E>               // insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
   TPos v = ST::inserter(k, x); // insert in base tree
   setHeight(v); // compute its height
   rebalance(v); // rebalance if needed
   return Iterator(v);

    
  }
  
template <typename E>               // rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
   TPos z = v;
   while (!(z == ST::root())) { // rebalance up to root
      z = z.parent();
      setHeight(z); // compute new height
      if (!isBalanced(z)) { // restructuring needed
         TPos x = tallGrandchild(z);
         z = restructure(x); // trinode restructure
         setHeight(z.left()); // update heights
         setHeight(z.right());
         setHeight(z);
      }
   }
    
  }

template <typename E>            // Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v){

   TPos z=v;
   TPos vparent=z.v->par;
   TPos Gparent=vparent.v->par;
   

   //LL & LR
   if(Gparent.v->left==vparent.v){

      //LL
      if(vparent.left()==v){
      
         
         if(Gparent.v->par->left==Gparent.v){
            Gparent.v->par->left=vparent.v;
         }
         else if(Gparent.v->par->right==Gparent.v){
            Gparent.v->par->right=vparent.v;
         }
         Gparent.v->left=vparent.v->right;
         vparent.v->right=Gparent.v;
         vparent.v->par=Gparent.v->par;
         Gparent.v->par=vparent.v;
         Gparent.v->left->par=Gparent.v;
         
         return vparent;
         
         
      }


      //LR
      else{
        vparent.v->right=z.v->left;
	z.v->par=Gparent.v;
	Gparent.v->left=z.v;
	vparent.v->par=z.v;
	z.v->left=vparent.v;
	vparent.v->right->par=vparent.v; 
	if(Gparent.v->par->left==Gparent.v){
            Gparent.v->par->left=z.v;
         }
         else if(Gparent.v->par->right==Gparent.v){
            Gparent.v->par->right=z.v;
         }
	z.v->par=Gparent.v->par;
	Gparent.v->left=z.v->right;
	z.v->right->par=Gparent.v;
	z.v->right=Gparent.v;
	Gparent.v->par=z.v;
	
	return z;
         
      }
   }


   else if(Gparent.right()==vparent){
      //RR
      if(vparent.right()==v){
      
         if(Gparent.v->par->left==Gparent.v){
            Gparent.v->par->left=vparent.v;
         }
         else if(Gparent.v->par->right==Gparent.v){
            Gparent.v->par->right=vparent.v;
         }
         Gparent.v->right=vparent.v->left;
         vparent.v->left=Gparent.v;
         vparent.v->par=Gparent.v->par;
         Gparent.v->par=vparent.v;
         Gparent.v->right->par=Gparent.v;

         return vparent;
      }

      //RL
      else{
	vparent.v->left=z.v->right;
	z.v->par=Gparent.v;
	Gparent.v->right=z.v;
	vparent.v->par=z.v;
	z.v->right=vparent.v;
	vparent.v->left->par=vparent.v;
        if(Gparent.v->par->left==Gparent.v){ 
            Gparent.v->par->left=z.v;
        }
        else if(Gparent.v->par->right==Gparent.v){ 
        	Gparent.v->par->right=z.v;
        } 
	z.v->par=Gparent.v->par;
	Gparent.v->right=z.v->left;
	z.v->left->par=Gparent.v;
	z.v->left=Gparent.v;
	Gparent.v->par=z.v;
	return z;

      }

   }

  }
