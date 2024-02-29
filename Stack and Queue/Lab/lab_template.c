//////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//////////////////////////////////   linked list //////////////////////////////////////////////

typedef struct _listnode{
  int item;
  struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
  int size;
  ListNode *head;
  ListNode *tail;
} LinkedList;

////////////////////////////////// stack    //////////////////////////////////////////////
typedef struct stack{
  LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////

typedef struct _queue{
  LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////
void printList(ListNode *head);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////////////////////////////

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

//////////////////////////////////////////////////

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////////////
// four questions
void removeUntil(Stack *s, int value);
void recursiveReverse(Queue *q);
int palindrome(char *word);
int balanced(char *expression);

//////////////////////////////////////////////////////////////////
/////

int main()
{
  Stack s;
  Queue q;
  int item[] = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
  int i;
  char *word1 = "A man a plan a canal Panama";
  char *word2 = "Superman in the sky";

  //for question 1
  //initialize the stack
  s.ll.head = NULL;
  s.ll.size = 0;
  s.ll.tail = NULL;

  for (i = 0; i<11; i++)
    push(&s, item[i]);

  printList(s.ll.head);
  removeUntil(&s, 5);
  printList(s.ll.head);

  //for question 2
  //initialize the queue
  q.ll.head = NULL;
  q.ll.size = 0;
  q.ll.tail = NULL;

  for (i = 0; i<10; i++)
    enqueue(&q, i);
  printList(q.ll.head);
  recursiveReverse(&q);
  printList(q.ll.head);

  //for question 3
  palindrome(word1); //*word1="A man a plan a canal Panama";
  palindrome(word2);// *word2="Superman in the sky";


  //for question 4
  if (balanced("()")) printf("not balanced!\n");
  else
    printf("balanced!\n");

  if (balanced("[()]")) printf("not balanced!\n");
  else
    printf("balanced!\n");

  if (balanced("{[]()[]}")) printf("not balanced!\n");
  else
    printf("balanced!\n");

  if (balanced("[({{)])")) printf("not balanced!\n");
  else
    printf("balanced!\n");

  return 0;
}

////////////////////////////////////////////////////////////////
//Question 1

void removeUntil(Stack *s, int value){
  /* My Answer
    while(peek(s) != value){
        pop(s);
    }
    */

  // Model Answer
  while(!isEmptyStack(s)){
        if(peek(s) != value){
            pop(s);
        }else{
            break;
        }
  }
}

////////////////////////////////////////////////////////////
//Question 2

void recursiveReverse(Queue *q){

  // write your code here
    int item;
    if (isEmptyQueue(q)){ // recursive function terminating condition
        return;
    }
    item = dequeue(q);
    recursiveReverse(q);
    enqueue(q, item);

}

////////////////////////////////////////////////////////////
//Question 3

int palindrome(char *word){
  /* Answer not using stack and queues
  int size = strlen(word), start = 0, end = size-1;

  while(start < end){
        while(!isalpha(word[start]) && start < end){ // ignore spaces
            start++;
        }

        while(!isalpha(word[end]) && start < end){ // ignore spaces
            end--;
        }

        if(tolower(word[start]) != tolower(word[end])){ // if it does not match
            return -1;
        }

        start++;
        end--;
  }
  return 0; */

    /* Using one stack and one queue
  int size;
  Stack s;
  Queue q;
  s.ll.head = NULL;
  s.ll.tail = NULL;
  s.ll.size = 0;
  q.ll.head = NULL;
  q.ll.tail = NULL;
  q.ll.size = 0;

  // Put the whole string in a stack and queue, strip out spaces
  while(*word){
        if(*word != ' '){
            push(&s, tolower(*word));
            enqueue(&q, tolower(*word));
        }
        word++;
  }

  // divide size by 2, ignore the middle character in an odd-length string
  size = s.ll.size / 2;

  // pop first string from the stack and compare with last string by dequeueing
  while(size > 0){
        if(pop(&s) != dequeue(&q)){
            printf("The string is not a palindrome\n");
            return;
        }
        size--;
  }
  printf("The string is a palindrome\n");
  */

  /* Using 2 stacks */
  Stack s1;
  s1.ll.head = NULL;
  s1.ll.size = 0;

  Stack s2;
  s2.ll.head = NULL;
  s2.ll.size = 0;

  int midpoint = 0, odd = 0;

  printf("%s\n", word);

  while(*word){ // push all words into s1
    if(*word != ' '){ // REMEMBER TO CHECK FOR SPACES
        push(&s1, tolower(*word)); // REMEMBER TO SET TO ALL LOWERCASE OR ALL UPPERCASE
    }
    *word++;
  }

  midpoint = s1.ll.size /2;
  odd = s1.ll.size % 2; // 0 if even, any other than that means odd

  while(midpoint){ // push second half of list into s2
    push(&s2, pop(&s1));
    midpoint--;
  }

  if(odd){ // if word has odd length pop one character out from s1
    pop(&s1);
  }

  // check if palindrome
  while(!isEmptyStack(&s1)){
    if(pop(&s1) != pop(&s2)){
        printf("The string is not a palindrome\n");
        return 1;
    }
  }

  printf("The string is a palindrome\n");
  return 0;
}



////////////////////////////////////////////////////////////
//Question 4

int balanced(char *expression){
    // return 1 if not balanced
    // write your code here
    Stack s;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;

    while(*expression){ // loop until null terminator is reached
        if(*expression == '(' || *expression == '[' || *expression == '{'){ // if string starts with opening brackets then push into stack
            push(&s, *expression);
        }else if(*expression == ')'){ // if its closing bracket then pop the stack for opening brackets and see if it matches
            if(isEmptyStack(&s) || pop(&s) != '('){
                return -1;
            }
        }else if(*expression == ']'){
            if(isEmptyStack(&s) || pop(&s) != '['){
                return -1;
            }
        }else if(*expression == '}'){
            if(isEmptyStack(&s) || pop(&s) != '{'){
                return -1;
            }
        }
        expression++;
    }

    if(isEmptyStack(&s)){
        return 0;
    }else{
        return -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
  insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
  int item;

  item = ((s->ll).head)->item;
  removeNode(&(s->ll), 0);
  return item;
}

int peek(Stack *s){
  return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
  if ((s->ll).size == 0)
    return 1;
  return 0;
}


////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item){
  insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
  int item;
  item = ((q->ll).head)->item;
  removeNode(&(q->ll), 0);
  return item;
}

int isEmptyQueue(Queue *q){
  if ((q->ll).size == 0)
    return 1;
  return 0;
}



////////////////////////////////////////////////////////////////////////////////

void printList(ListNode *head){

  ListNode *temp = head;

  if (temp == NULL)
    return;

  while (temp != NULL){
    printf("%d ", temp->item);
    temp = temp->next;
  }
  printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

  ListNode *temp;

  if (ll == NULL || index < 0 || index >= ll->size)
    return NULL;

  temp = ll->head;

  if (temp == NULL || index < 0)
    return NULL;

  while (index > 0){
    temp = temp->next;
    if (temp == NULL)
      return NULL;
    index--;
  }

  return temp;
}

int insertNode(LinkedList *ll, int index, int value){

  ListNode *pre, *cur;

  if (ll == NULL || index < 0 || index > ll->size + 1)
    return -1;

  // If empty list or inserting first node, need to update head pointer
  if (ll->head == NULL || index == 0){
    cur = ll->head;
    ll->head = malloc(sizeof(ListNode));
    ll->tail = ll->head;
    ll->head->item = value;
    ll->head->next = cur;
    ll->size++;
    return 0;
  }

  // Inserting as new last node
  if (index == ll->size){
    pre = ll->tail;
    cur = pre->next;
    pre->next = malloc(sizeof(ListNode));
    ll->tail = pre->next;
    pre->next->item = value;
    pre->next->next = cur;
    ll->size++;
    return 0;
  }

  // Find the nodes before and at the target position
  // Create a new node and reconnect the links
  if ((pre = findNode(ll, index - 1)) != NULL){
    cur = pre->next;
    pre->next = malloc(sizeof(ListNode));

    if (index == ll->size)
      ll->tail = pre->next;

    pre->next->item = value;
    pre->next->next = cur;
    ll->size++;
    return 0;
  }

  return -1;
}

int removeNode(LinkedList *ll, int index){

  ListNode *pre, *cur;

  // Highest index we can remove is size-1
  if (ll == NULL || index < 0 || index >= ll->size)
    return -1;

  // If removing first node, need to update head pointer
  if (index == 0){
    cur = ll->head->next;
    free(ll->head);
    ll->head = cur;
    ll->size--;

    if (ll->size == 0)
      ll->tail = 0;

    return 0;
  }

  // Find the nodes before and after the target position
  // Free the target node and reconnect the links
  if ((pre = findNode(ll, index - 1)) != NULL){

    // Removing the last node, update the tail pointer
    if (index == ll->size - 1){
      ll->tail = pre;
      free(pre->next);
      pre->next = NULL;
    }
    else{
      cur = pre->next->next;
      free(pre->next);
      pre->next = cur;
    }
    ll->size--;
    return 0;
  }

  return -1;
}
