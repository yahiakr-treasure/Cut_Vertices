#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/********************/

struct _Node{
    int name;
    int parent;
    struct _ListNode *children;
}typedef Node;

struct _ListNode{
    Node *node;
    struct _ListNode *nextNode;
}typedef ListNode;

/********************/

bool *visited; // keeps tract of visited vertices
int *order;
int *low;
bool *ap; // Store articulation points

int cpt = 0 ;
static unsigned int NUMBER_OF_ELEMENTS = 7;

bool mat[7][7] = {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 1, 0}
};

/********************/

Node* creatNode(int name){
    Node* n = malloc(sizeof(Node));
    n->name = name;
    n->parent = -1;
    n->children= NULL;
    return n;
}

void append(Node* parent, Node *child){

    if(parent != NULL){
        ListNode *list = malloc(sizeof(ListNode));
        list->node=child;
        list->nextNode = NULL;

        if(parent->children != NULL)
            list->nextNode = parent->children;

        parent->children = list;
        child->parent = parent->name;
    }

}

int min(int a,int b){
    if(a > b){
        return b;
    } else {
        return a;
    }
}

void printTree(Node* js){
    ListNode *child ;
    if(js!=NULL){
        printf("\n[%u", js->name);
        child = js->children;
        if(child == NULL)
            printf("->NULL]");
        else
            printf("->");

        while(child != NULL){
            printf("%u", child->node->name);
            if(child->nextNode != NULL) {
                printf(",");
            }
            else {
                printf("]");
            }
            child = child->nextNode;
        }
        child = js->children;
        while(child != NULL){
            printTree(child->node);
            child = child->nextNode;
        }
    }
}

Node* DFS(Node* parent,unsigned int vertex){
    Node* root = creatNode(vertex);
    append(parent, root);

    int children = 0;
    visited[vertex] = true;
    order[vertex] = cpt ;
    low[vertex] = cpt ;
    cpt++;

    for(int i = 0; i < NUMBER_OF_ELEMENTS;i++){
        if((mat[vertex][i])){

            if(!visited[i]){

                children++;
                DFS(root,i);

                low[vertex] = min(low[vertex], low[i]);

                if (root->parent == -1 && children > 1)
                    ap[vertex] = true;

                if (root->parent != -1 && low[i] >= order[vertex])
                    ap[vertex] = true;

            } else if(i != root->parent) {
                low[vertex] = min(low[vertex], order[i]);
            }
        }
    }
    return root;
}

int main(){

    visited = calloc(NUMBER_OF_ELEMENTS, sizeof(bool));
    order = calloc(NUMBER_OF_ELEMENTS, sizeof(int));
    low = calloc(NUMBER_OF_ELEMENTS, sizeof(int));
    ap = calloc(NUMBER_OF_ELEMENTS, sizeof(bool));

    printf("\nThe DFS Tree : [i.e: Parent -> Child_1 ,Child_2 ...]\n");

    int i=0;
    Node* aRoot;
    while(i < NUMBER_OF_ELEMENTS){
        if(!visited[i]){
            aRoot = DFS(NULL,i);
            printTree(aRoot);
        }
        i++;
    }

    printf("\n\nThe order of visits : ");

    for(int j = 0 ; j < NUMBER_OF_ELEMENTS ; j++){
        printf("%d, ",order[j]);
    }
    printf("\n\n");
    printf("Articulation point(s) : ");
    for(int j = 0 ; j < NUMBER_OF_ELEMENTS ; j++){
        if(ap[j]) printf("%d, ",j);
    }

    printf("\n\n");
    return 0;
}
