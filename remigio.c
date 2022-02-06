//
// AED, January 2022
//
// Solution of the second practical assignement (multi-ordered tree)
//
// Place your student numbers and names here
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AED_2021_A02.h"


//
// the custom tree node structure
//
// we want to maintain three ordered trees (using the same nodes!), so we need three left and three right pointers
// so, when inserting a new node we need to do it three times (one for each index), so we will end upo with 3 three roots
//


typedef struct tree_node_s
{
  char name[MAX_NAME_SIZE + 1];                         // index 0 data item
  char zip_code[MAX_ZIP_CODE_SIZE + 1];                 // index 1 data item
  char telephone_number[MAX_TELEPHONE_NUMBER_SIZE + 1]; // index 2 data item
  char security_number[MAX_SECURITY_NUMBER_SIZE + 1];
  struct tree_node_s *left[4];                          // left pointers (one for each index) ---- left means smaller
  struct tree_node_s *right[4];                         // right pointers (one for each index) --- right means larger
  int height;                                           // heigth of the tree from node for AVL trees
}
tree_node_t; 

int max(int a, int b)
{
    return (a > b)? a : b;
}


// queue implementation

typedef struct node {
    tree_node_t* val;
    struct node *next;
} node_q;

typedef struct queue
{
    node_q* head;
    node_q* tail;
} queue;


void init_queue(queue* q){
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(queue* q, tree_node_t* value) {
    // create new node
    node_q * new_node = malloc(sizeof(node_q));
    if (new_node==NULL) { return;}    //if malloc fails
    new_node->val = value;
    new_node->next = NULL;
    
    // if there is a tail we just connect that tail to this node
    if (q->tail != NULL){
        q->tail->next = new_node;
    }
    q->tail = new_node;

    // if there is no head we set this one also as head
    if (q->head == NULL) {
        q->head = new_node;
    }
    return;
}

tree_node_t* dequeue(queue* q) {
    if (q->head == NULL) {return NULL;}
    node_q * tmp = q->head;
    tree_node_t* result = tmp->val;
    q->head = q->head->next;
    if (q->head == NULL){
        q->tail = NULL;
    }
    free(tmp);
    return result;
}






//
// the node comparison function (do not change this)
//

  int compare_tree_nodes(tree_node_t *node1,tree_node_t *node2,int main_idx){
  
    int i,c;

    for(i = 0;i < 4;i++)
    {
      if(main_idx == 0)
        c = strcmp(node1->name,node2->name); // compara nome
      else if(main_idx == 1)
        c = strcmp(node1->zip_code,node2->zip_code); // compara zip
      else if(main_idx == 2)
        c = strcmp(node1->telephone_number,node2->telephone_number); // compara numero
      else
        c = strcmp(node1->security_number,node2->security_number); // compara sec numero
      if(c != 0)
        return c; // different on this index, so return (sao diferentes, retorna c)
      main_idx = (main_idx == 3) ? 0 : main_idx + 1; // advance to the next index (sao iguais, bora para o prox)
    }
    return 0;
  }

// 
// ALL THE STUFF FOR AVL TREES
//

int height(tree_node_t *node){
  if (node == NULL){
    return 0;
  }
  return node->height;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
tree_node_t *rightRotate(tree_node_t *y,int main_idx)
{
    tree_node_t *x = y->left[main_idx];
    tree_node_t *T2 = NULL;
     if (x ){
       T2 = x->right[main_idx];
     }

    // Perform rotation

    if (x){
       x->right[main_idx] = y;
     }
    y->left[main_idx] = T2;

    y->height = max(height(y->left[main_idx]),height( y->right[main_idx]))+1;
    if (x){
      x->height = max(height(x->left[main_idx]), height(x->right[main_idx]))+1;
     }


    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
tree_node_t *leftRotate(tree_node_t *x,int main_idx)
{
    tree_node_t *y = x->right[main_idx];
    tree_node_t *T2 = NULL;
     if (y){
       T2 = y->left[main_idx];
     }
    // Perform rotation
    if (y){
       y->left[main_idx] = x;
     }
    x->right[main_idx] = T2;



    x->height = max(height(x->left[main_idx]), height(x->right[main_idx]))+1;
    if (y){
       y->height = max(height(y->left[main_idx]), height(y->right[main_idx]))+1;
     }
    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(tree_node_t *N, int main_idx)
{
    if (N == NULL)
        return 0;
    return height(N->left[main_idx]) - height(N->right[main_idx]);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
tree_node_t* insert(tree_node_t* node, tree_node_t* person, int main_idx)
{

    if (node == NULL){
      return person;
    }
    int *c;
    c = (int *) malloc(sizeof(int));
    *c = compare_tree_nodes(node,person,main_idx);

    if (*c > 0)
    {
       node->left[main_idx]  = insert(node->left[main_idx], person, main_idx);
    }
    else
    {
      node->right[main_idx]  = insert(node->right[main_idx], person,main_idx);
    }

    // increase the height of the tree

    node->height = 1 + max( height(node->right[main_idx]) ,height( node->left[main_idx]));
    

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int *balance;
    balance = (int *) malloc(sizeof(int));
    *balance = getBalance(node,main_idx);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (*balance > 1 && compare_tree_nodes(person,node->left[main_idx],main_idx) < 0)
    {   
        return rightRotate(node,main_idx);
    }
    // Right Right Case
    if (*balance < -1 && compare_tree_nodes(person,node->right[main_idx],main_idx)> 0)
        return leftRotate(node,main_idx);

    // Left Right Case
    if (*balance > 1 && compare_tree_nodes(person,node->left[main_idx],main_idx) > 0)
    {

        node->left[main_idx] =  leftRotate(node->left[main_idx],main_idx);
        return rightRotate(node,main_idx);
    }

    // Right Left Case
    if (*balance < -1 && compare_tree_nodes(person,node->right[main_idx],main_idx)< 0)
    {   
        node->right[main_idx] = rightRotate(node->right[main_idx],main_idx);
        return leftRotate(node,main_idx);
    }
    /* return the (unchanged) node pointer */
    free(c);
    free(balance);
    return node;
}



//
// tree insertion routine (place your code here)
//

void tree_insert( tree_node_t** rootp, tree_node_t* node,int main_idx)
{
  if ( *rootp == NULL){
    *rootp = node;
    return;
  }
  int c = compare_tree_nodes(*rootp,node,main_idx);
  if (c < 0)
  {
    tree_insert(&((*rootp)->right[main_idx]), node,main_idx);
    return;
  }
  else
  {
    tree_insert(&((*rootp)->left[main_idx]), node,main_idx);
    return;
  }
  return;

}


//
// tree search routine (place your code here)
//

tree_node_t* find(tree_node_t** rootp,int main_idx,tree_node_t* person)
{
  if ((*rootp) == NULL){
    printf("here");
    return NULL;
  }
  if (compare_tree_nodes(*rootp,person,main_idx)==0)
  {
    return *rootp;
  }
  else if (compare_tree_nodes(*rootp,person,main_idx) > 0)
  {
    return find(&((*rootp)->left[main_idx]),main_idx,person);
  }
  else
  {
    return find(&((*rootp)->right[main_idx]),main_idx,person);
  }
  return NULL;
}


//
// tree depdth
//

int tree_depth(tree_node_t** root, int main_idx)
{
  if ( *root == NULL){
    return 0;
  }
  int leftheight = tree_depth(&((*root)->left[main_idx]),main_idx);
  int rightheight = tree_depth(&((*root)->right[main_idx]),main_idx);

  if (leftheight > rightheight) 
  {
    return leftheight + 1;
  }
  else{
    return rightheight + 1 ;
  }
}


//
// list, i,e, traverse the tree (place your code here)
//
void visit_node(tree_node_t* node)
{
  printf("----------------------\n");
  printf("----------------------\n");
  printf("Name ----------------- %s\n",node->name);
  printf("ZipCode ----------------- %s\n",node->zip_code);
  printf("Telephone Number ----------------- %s\n",node->telephone_number);

  return;
}

void traverse_breadth_first(tree_node_t *link,int main_idx)
{
  queue q1;
  init_queue(&q1);
  enqueue(&q1,link);
  while(q1.head != NULL)
  {
    link = dequeue(&q1);
    if(link != NULL)
    {
      visit_node(link);
      enqueue(&q1,link->left[main_idx]);
      enqueue(&q1,link->right[main_idx]);
    }
  }
}


int list_in_order(tree_node_t* node,int main_idx)
{

  if (node !=NULL){
    if (node->left[main_idx] != NULL){
      list_in_order(node->left[main_idx],main_idx);
    }
        visit_node(node);
    if (node->right[main_idx] != NULL){

      list_in_order(node->right[main_idx],main_idx);
    }

  }
  return 1;

} 



int list_pre_order(tree_node_t* node,int main_idx)
{

  if (node !=NULL){
    visit_node(node);
    if (node->left[main_idx] != NULL){
      list_pre_order(node->left[main_idx],main_idx);
    }
    if (node->right[main_idx] != NULL){

      list_pre_order(node->right[main_idx],main_idx);
    }

  }
  return 1;

} 


//
// Find depth of node
//

tree_node_t* node_depth(tree_node_t** rootp,int main_idx,tree_node_t* person,int rights, int lefts)
{
  if (compare_tree_nodes(*rootp,person,main_idx)==0)
  {
    printf("found it\n");
    printf("the position is at %d rigths and %d lefts, and has depth %d",rights,lefts,rights + lefts);
    return *rootp;
  }
  else if (compare_tree_nodes(*rootp,person,main_idx) > 0)
  {
    return node_depth(&((*rootp)->left[main_idx]),main_idx,person,rights,lefts+1);
  }
  else
  {
    return node_depth(&((*rootp)->right[main_idx]),main_idx,person,rights +1,lefts);
  }
  return NULL;
}

//
//  how many nodes
//

int numberNodes(tree_node_t** root, int main_idx)
{
  if ( *root == NULL){
    return 0;
  }
  int leftnodes= numberNodes(&((*root)->left[main_idx]),main_idx);
  int rightnodes = numberNodes(&((*root)->right[main_idx]),main_idx);

    return rightnodes + leftnodes+ 1 ;
}

//
//  how many nodes is each level
//

int deapthNodes(tree_node_t** rootp, int main_idx,int depth)
{
  if ( *rootp == NULL){
    return 0;
  }
  if (depth == 0){
    return 1;
  }
  return deapthNodes(&(*rootp)->left[main_idx],main_idx,depth-1) + deapthNodes(&(*rootp)->right[main_idx],main_idx,depth-1);
}


//
//  how many leaf nodes
//
int leafCount(tree_node_t** rootp,int main_idx)
{
  if ( *rootp == NULL){
    return 0;
  }
  if ((*rootp)->left[main_idx] == NULL && (*rootp)->right[main_idx] == NULL)
  {
    return 1;
  }
  else 
  {
    return leafCount(&(*rootp)->left[main_idx],main_idx) + leafCount(&(*rootp)->right[main_idx],main_idx);
  }
}

// number with same camp 

int compareCamp(char *camp,tree_node_t* node,int main_idx){
  switch (main_idx)
  {
  case 0:
      return strcmp((node)->name,camp);
    break;
  case 1:
      return strcmp((node)->zip_code,camp);
    break;
  case 2:
      return strcmp((node)->telephone_number,camp);
    break;

  }

}




void sameType(tree_node_t** rootp,char * camp,int main_idx){

  if ((*rootp)==NULL){return;}
  int c = compareCamp(camp,*rootp,main_idx);
  if (c == 0)
  {
    visit_node(*rootp);
    if ((*rootp)->left[main_idx] != NULL){
      if (compareCamp(camp,((*rootp)->left[main_idx]),main_idx) == 0){
         sameType(&((*rootp)->left[main_idx]),camp,main_idx);
      }
    }
    if ((*rootp)->right[main_idx] != NULL){
      if (compareCamp(camp,((*rootp)->right[main_idx]),main_idx) == 0){
        sameType(&((*rootp)->right[main_idx]),camp,main_idx);
      }
    }
  }
  else if (c > 0)
  {
    sameType(&((*rootp)->left[main_idx]),camp,main_idx);
  }
  else
  {
    sameType(&((*rootp)->right[main_idx]),camp,main_idx);
  }
  return;
}


//
// main program
//

int main(int argc,char **argv)
{
  
    double dt;

    // process the command line arguments
      if(argc < 3)
      {
        fprintf(stderr,"Usage: %s student_number number_of_persons [options ...]\n",argv[0]);
        fprintf(stderr,"Recognized options:\n");
        fprintf(stderr,"  -list[N]              # list the tree contents, sorted by key index N (the default is index 0)\n");
        // place a description of your own options here
        return 1;
      }
      int student_number = atoi(argv[1]);
      if(student_number < 1 || student_number >= 1000000)
      {
        fprintf(stderr,"Bad student number (%d) --- must be an integer belonging to [1,1000000{\n",student_number);
        return 1;
      }
      int n_persons = atoi(argv[2]);
      if(n_persons < 3 || n_persons > 10000000)
      {
        fprintf(stderr,"Bad number of persons (%d) --- must be an integer belonging to [3,10000000]\n",n_persons);
        return 1;
      }
    //

    // generate all data
      tree_node_t *persons = (tree_node_t *)calloc((size_t)n_persons,sizeof(tree_node_t));
      if(persons == NULL)
      {
        fprintf(stderr,"Output memory!\n");
        return 1;
      }
      aed_srandom(student_number);
      for(int i = 0;i < n_persons;i++)
      {
        random_name(&(persons[i].name[0]));
        random_zip_code(&(persons[i].zip_code[0]));
        random_telephone_number(&(persons[i].telephone_number[0]));
        random_security_number(&(persons[i].security_number[0]));
        for(int j = 0;j < 4;j++)
          persons[i].left[j] = persons[i].right[j] = NULL; // make sure the pointers are initially NULL
      }
    // 

    // create the ordered binary trees


      tree_node_t *roots[4]; // three indices, three roots

      for(int main_index = 0;main_index < 4;main_index++){
        roots[main_index] = NULL;
      }

      for(int main_index = 0;main_index < 1;main_index++){
              dt = cpu_time();

        
        for(int i = 0;i < n_persons;i++){
          
          tree_insert(&(roots[main_index]), &(persons[i]), main_index); // place your code here to insert &(persons[i]) in the tree with number main_index
          
        }
        dt = cpu_time() - dt;
       // printf("Tree creation time (%d persons): %.3es\n",n_persons,dt);
      }
      
      
    //
    
    // search the tree
/*       for(int main_index = 0;main_index < 4;main_index++){



        dt = cpu_time();
        for(int i = 0;i < n_persons;i++){
        
          tree_node_t n = persons[i]; // make a copy of the node data
          if(find(&roots[main_index],main_index,&n) != &(persons[i])){ // place your code here to find a given person, searching for it using the tree with number main_index
            return 1;
          }

        }
        dt = cpu_time() - dt;
        printf("Tree search time (%d persons, index %d): %.3es\n",n_persons,main_index,dt);
      } */
    //

    // compute the largest tree depdth
/*       for(int main_index = 0;main_index < 1;main_index++)
      {
        dt = cpu_time();
        int depth = tree_depth(&roots[main_index],main_index); // place your code here to compute the depth of the tree with number main_index
        dt = cpu_time() - dt;
        //printf("Tree depth for index %d: %d (done in %.3es)\n",main_index,depth,dt);
        //printf("%d  %d  %f\n", n_persons, depth,dt);
      } */
    //
    printf("%d %d\n",n_persons,leafCount(&roots[0],0));
    
    // process the command line optional arguments
       
      if(argc == 4){
        printf("\n\n");
        if(strcmp(argv[3],"-list0") == 0){   
          printf("List of persons:\n");
          list_in_order(roots[0], 0); // place your code here to traverse, in order, the tree with number main_index
        }else if(strcmp(argv[3],"-list1") == 0){   
          printf("List of persons:\n");
          list_in_order(roots[1], 1); // place your code here to traverse, in order, the tree with number main_index
        }else if(strcmp(argv[3],"-list2") == 0){   
          printf("List of persons:\n");
          list_in_order(roots[2], 2); // place your code here to traverse, in order, the tree with number main_index
        }
        else if(strcmp(argv[3],"-list3") == 0){   
          printf("List of persons:\n");
          list_in_order(roots[3], 3); // place your code here to traverse, in order, the tree with number main_index
        }
        printf("\n\n");   
      }
    //
    

     
    /*
    // Some more prints
      printf("how many nodes is ---> %d\n", numberNodes(&roots[2],2));
      node_depth(&roots[2],2,&persons[2],0,0);
      printf("\nleaf count is -------> %d\n",leafCount(&roots[2],2));
      printf("nodes with depth 10  =  %d\n",deapthNodes(&roots[2],2, 10));
    //
    */
    
    // clean up --- don't forget to test your program with valgrind, we don't want any memory leaks
  // process the command line optional arguments
 /*  for(int i = 3;i < argc;i++)
  {
    if(strncmp(argv[i],"-list",5) == 0)
    { // list all (optional)
      int main_index = atoi(&(argv[i][5]));
      if(main_index < 0)
        main_index = 0;
      if(main_index > 2)
        main_index = 2;
      printf("List of persons:\n");
      (void)list( ... ); // place your code here to traverse, in order, the tree with number main_index
    }
    // place your own options here
  } */
  // clean up --- don't forget to test your program with valgrind, we don't want any memory leaks


/*   printf("yooo %d\n",tree_depth(&roots[2],2));
  list(roots[2],2);                                             my tests
  node_depth(&roots[2],2,&persons[2],0,0); */

/*   printf("how many nodes is ---> %d\n", numberNodes(&roots[2],2));
  node_depth(&roots[2],2,&persons[2],0,0);
  printf("\nleaf count is -------> %d\n",leafCount(&roots[2],2));
  printf("nodes with depth 10  =  %d\n",deapthNodes(&roots[2],2, 10));

  traverse_breadth_first(roots[2],2);
  
  printf("\n\n\n");

  char * zip = "77449 Katy (Harris county)";

  sameZip(&roots[1],zip); */



  //sameType(&roots[1],"10002 New York City (New York county)",1);
 // create the ordered binary trees
/*   for(int i = 0;i < n_persons;i++)
  { 
    for(int j = 0;j < 4;j++)
    {
      persons[i].left[j] = persons[i].right[j] = NULL; // make sure the pointers are initially NULL
    }
    persons[i].height =1 ;
  }


  tree_node_t* roots2[4]; // three indices, three roots
  for(int main_index = 0;main_index < 4;main_index++)
    roots2[main_index] = NULL;

  for (int main_index = 0; main_index <4;main_index++){
  double dt2 = cpu_time();
  for(int i = 0;i < n_persons;i++)
  {
       roots2[main_index] = insert(roots2[main_index],&persons[i],main_index); // place your code here to insert &(persons[i]) in the tree with number main_index
  }
  dt2 = cpu_time() - dt;
  printf("Tree creation time (%d persons): %.3es\n",n_persons,dt2);
  }
    for(int main_index = 0;main_index < 4;main_index++)
  {
    dt = cpu_time();
    int depth = tree_depth(&roots2[main_index],main_index); // place your code here to compute the depth of the tree with number main_index
    dt = cpu_time() - dt;
    printf("Tree depth for index %d: %d (done in %.3es)\n",main_index,depth,dt);
  } 

  list_in_order(roots2[2],2);

    // search the tree
      for(int main_index = 0;main_index < 4;main_index++){
        dt = cpu_time();
        for(int i = 0;i < n_persons;i++){
          if(find(&roots2[0],1,&(persons[i])) != &(persons[i])){ // place your code here to find a given person, searching for it using the tree with number main_index
            return 1;
          }
          
        }
        dt = cpu_time() - dt;
        printf("Tree search time (%d persons, index %d): %.3es\n",n_persons,main_index,dt);
      }


  //list_in_order(roots2[1],1); */
  free(persons);

  return 0;
}
