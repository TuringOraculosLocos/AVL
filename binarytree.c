#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binarytree.h"

vertex * 
newVertex(int  value)
{
    vertex * n = (vertex*) malloc(sizeof(vertex));
    assert(n != NULL);
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
    
}

vertex *  
add(int  e,vertex*a)
{
    if (a == NULL){
        a = newVertex(e);
        return a;
    }
    if (e > a->value){
        if(a->right == NULL){
            a->right = newVertex(e);
            a->right->dad = a;
            return a->right;
        }
    else
        add(e,a->right);   
	}
    else{
        if (a->left == NULL){
            a->left = newVertex(e);
            a->left->dad = a;
            return a->left;
        }
        else
            add(e,a->left);   
    }
    rebalance(a);
    updateHeight(a);
    
}

vertex *
search(vertex * a, vertex * v)
{
    if(a == NULL)
        return NULL;
    if (v->value < a->value)  	
            return search(a->left,v);       
    if (v->value > a->value)
        return search(a->right,v);
    else
        return v;
}

void
removeVer(vertex * a,vertex * v)
{
	vertex * aux;
	if(v->value < a->value)
		removeVer(a->left,v);
	else if (v->value > a->value);
		removeVer(a->right,v):
	else
	{
		if (v->left == NULL && v->right == NULL)
			free(v);
		else if (v->left == NULL)
		{
			aux = v;
			v = v->right;
			free(aux);
		}
		else if (v->right == NULL)
		{
			aux = v;
			v = v->left;
			free(aux);
		}
		else
		{
			v->value = removeMin(v->right);
		}
	}
	rebalance(v);
	updateHeight(v);
}

int
removeMin(vertex * v)
{
	if(v == NULL)
		return 0;
	else 
	{
		if (v->left != NULL)
		{
			int x = removeMin(&(v->left));
			rebalance(v);
			updateHeight(v);
			return x;
		}
		else
		{
			vertex * aux = v;
			int x = aux->value;
			free(aux);
			rebalance(v);
			updateHeight(v);
			return x;
		}
	}
}

vertex * 
setLeft(vertex * v, vertex * w)
{
    if(v->left == NULL){
    v->left = w;
    w->dad = v;
    }
    w->left = w->dad->left;
    w->right = w->dad;
    w->dad = v;
    v->left = w;
}

vertex * 
setRight(vertex * v, vertex * w)
{
    if(v->right == NULL){
    v->right = w;
    w->dad = v;
    }
    w->right = w->dad->right;
    w->left = w->dad;
    w->dad = v;
    v->right = w;
}

int 
size(struct vertice * b)
{
    if(b == NULL)
        return 0;
    int s = 0;
    size(b->left);
    s++;
    size(b->right);
    return s;

}

int 
height(vertex * b)
{
    if (b == NULL)
        return -1;
    return b->height;
}

void 
updateHeight(vertex * a)
{
    if (a != NULL)
        a->height = (a->left->height > a->right->height) ?  a->left->height: a->right->height;
}

void 
leftRotation(vertex * a)
{
    vertex * a1;
    a1 = a->left;
    a->left = a1->right;
    a1->right = a;
    updateHeight(a);
    updateHeight(a1);
    a = a1; //Update root
}
void rightRotation(vertex * a)
{
    vertex * a1;
    a1 = a->right;
    a->right = a1->left;
    a1->left = a;
    updateHeight(a);
    updateHeight(a1);
    a = a1;
}

void rebalance(vertex * v)
{   
    int balance;
    if(v == NULL)
        return;
    balance = height(v->left) - height (v->right);
    if (balance == 0){
        rebalance(v->dad);
        return;
    }
    else if(balance == -2){
        vertex * b = v->right;
        if(height(b->left)-height(b->right) == 1)
            rightRotation(b);
        leftRotation(v);
    }
    else if (balance == 2){
        vertex * c = v->left;
        if(height(c->left)-height(c->right) == -1)
            leftRotation(c);
        rightRotation(v);
    }
    rebalance(v->dad);
}

void 
printInOrder(vertex * root)
{
    if (root == NULL)
        return;
    printInOrder(root->left);
    printf("%d",root->value);
    printInOrder(root->right);    
}
