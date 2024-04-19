#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

void DFS_I (Graph , int );

int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for DFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    DFS_I(g,i);

    return 0;
}

void DFS_I (Graph g, int v)
{
    // Time Complexity is V+E
    // 1. Ignore constant lines, initially complexity is V + V^2 but V^2 dominates so complexity is V^2
    // 2. Final answer (V+V*(E/V)) = V+E

    // Create a stack
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i, cur;

    // Initialise visited to keep track of visited vertex
    int* visited = (int*)malloc(sizeof(int)*g.V);
    for(i=0; i < g.V; i++){ // 1. Iterates V times
        visited[i] = 0;
    }

    // Push v into stack and mark as visited
    visited[v-1] = 1;
    push(&s, v);

    while(!isEmptyStack(s)){ // 1. Entire while loop iterates V times because we add V amount of elements
        cur = peek(s);
        // go through adj matrix and check if its visited
        for(i=0; i<g.V; i++){ // 1. Iterates V times
            if(g.matrix[cur-1][i] == 1 && visited[i] == 0){ // 2. However we only iterate through edges that are connected so (E/V)
                visited[i] = 1;
                push(&s, i+1);
                break;
            }
        }
        if(peek(s) == cur){
            pop(&s);
            printf("%d ", cur);
        }
    }
    printf("\n");
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
