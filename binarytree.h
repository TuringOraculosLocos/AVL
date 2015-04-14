typedef struct vertice{
    int height;
    int  value;
    struct vertice * left;
    struct vertice * right;
    struct vertice * dad;
} vertex;

vertex * nuevoVertice(int  value);
vertex *  add(int t, vertex*a);
void removeVer(vertex * a, vertex * v);
vertex * setLeft(vertex * v,vertex * w);
vertex * setRight(vertex * v, vertex *w);
int size(vertex * root);
int height(vertex * root);
void updateHeight(vertex*r);
void leftRotation(vertex * r);
void rightRotation(vertex * r);
void rebalance(vertex*v);
void printInOrder(vertex * root);
