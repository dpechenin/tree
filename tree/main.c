#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} tree;

tree* addEl(tree *p, int v) {
    if (p == NULL) {
        p = (tree*)malloc(sizeof(tree));
        p->value = v;
        p->right = p->left = NULL;
    }
    else if (v < p->value) {
        p->left = addEl(p->left, v);
    }
    else {
        p->right = addEl(p->right, v);
    }
    return p;
}

void freeTree(tree *p) {
    if(p != NULL) {
        freeTree(p->left);
        freeTree(p->right);
//free(p->value); если строка какая-нибудь тут
        free(p);
    }
}

tree* search(tree *root, int v) {
        if (root == NULL || root->value == v) return root;
        if (v < root->value) return search(root->left, v);
        else return search(root->right, v);
}

tree* minEl(tree *root) {
    tree *l = root;
    while (l->left != NULL) l = l->left;
    return l;
}

tree *maxEl(tree *root) {
    tree *r = root;
    while (r->right != NULL) r = r->right;
    return r;
}

void treeprint(tree *p) {
    if(p != NULL) {
        treeprint(p->left);
        printf("%d\n", p->value);
        treeprint(p->right);
    }
}

void searchAll(tree * root, int val)
{
    tree *cur = NULL, *tmp = root;
    do {
        cur = search(tmp, val);
        if (!cur) break;
        printf("%d\n", cur->value);
        tmp = cur -> right;
    } while(tmp);
}

tree* DeleteEl(tree* root, int val){
    if(root == NULL)
        return root;
 
    if(val == root->value){
        tree* tmp;
        if(root->right == NULL) {
            tmp = root->left;
        }
        else {
            tree* ptr = root->right;
            if(ptr->left == NULL){
                ptr->left = root->left;
                tmp = ptr;
            } 
            else {
                tree* pmin = ptr->left;
                while(pmin->left != NULL) {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = root->left;
                pmin->right = root->right;
                tmp = pmin;
            }
        }
        free(root);
        return tmp;
    } 
    else if(val < root->value)
        root->left  = DeleteEl(root->left, val);
    else
        root->right = DeleteEl(root->right, val);
    return root;
}

int main(void) {
    tree *tr = NULL;
    tr = addEl(tr, 1);
    tr = addEl(tr, 5);
    tr = addEl(tr, 7);
    tr = addEl(tr, 2);
    tr = addEl(tr, 3);
    tr = addEl(tr, 3);
    printf("Tree:\n");
    treeprint(tr);
    tree *s, *min, *max;
    s = search(tr, 2);
    printf("Find elem 2:\n");
    printf("%d\n", s->value);
    min = minEl(tr);
    printf("Find min:\n");
    printf("%d\n", min->value);
    max = maxEl(tr);
    printf("Find max:\n");
    printf("%d\n", max->value);
    printf("one more search:\n");
    searchAll(tr, 3);
    printf("Delete elem 2 и 5\n");
    tr = DeleteEl(tr, 2);
    tr = DeleteEl(tr, 5);
    treeprint(tr);
    freeTree(tr);
    return 0;
}
