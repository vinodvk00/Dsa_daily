#include<stdio.h>
#include<stdlib.h>

struct node{
    int key;
    struct node *left,*right;
    int height;
};
struct node *root = NULL,*n,*temp;

int max(int x,int y){
    return (x>y ? x : y);
}

int getHeight(struct node *node){
    if(node == NULL) return 0;
    return node->height;
}
void update_heights(struct node* root){ //to calculate the height of each
    if(root == NULL) return;
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    update_heights(root->left);
    update_heights(root->right);
}

int getBalance(struct node *node){
    if(node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct node* createNode(int key){
    n = (struct node*)malloc(sizeof(struct node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

struct node* rightRotate(struct node *y){
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;
    update_heights(y);
    update_heights(x);

    return x;
}

struct node* leftRotate(struct node *x){
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;
    update_heights(y);
    update_heights(x);

    return y;
}

struct node * insert(struct node* root, int key){
    if(root == NULL) return createNode(key);
    if(key < root->key) root->left = insert(root->left,key);
    else if(key > root->key) root->right = insert(root->right,key);
    else return root;

    update_heights(root);
    int balance = getBalance(root);

    if(balance > 1 && key < root->left->key) return rightRotate(root);
    if(balance < -1 && key > root->right->key) return leftRotate(root);
    if(balance > 1 && key > root->left->key){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && key < root->right->key){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct node* search(struct node* root, int key){
    if (root == NULL || root->key == key)
        return root;
 
    // Key is greater than root's key
    if (key>root->key )
        return search(root->right, key);
 
    // Key is smaller than root's key
    return search(root->left, key);
}

struct node * minValueNode(struct node* node){
	struct node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

struct node* delete(struct node* root, int data){
    if(root == NULL) return root;
    else if(data < root->key) root->left = delete(root->left, data);
    else if(data > root->key) root->right = delete(root->right, data);
    else{
        // node found
        if(root->left == NULL || root->right == NULL){
            temp = root->left ? root->left : root->right;
            // no child
            if(temp == NULL){
                free(root);
                root = NULL;
            } 
            // one chile
            else{
                *root = *temp;
                free(temp);
            }
        }else{
            // two child i.e internal node

            // get the inorder successor
            temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }
    if(root == NULL) return root;

    update_heights(root);
    int balance = getBalance(root);

    if(balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if(balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if(balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;

}


void inorder(struct node* root){
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ",root->key);
    inorder(root->right);
}

void preorder(struct node* root){
    if(root == NULL) return;
    printf("%d ",root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node* root){
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->key);
}

int main(){
    int ch, data;
    struct node* result = NULL;
        printf("\n\n------- AVL TREE --------\n");
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n4. Inorder");
        printf("\n5. Preorder");
        printf("\n6. Postorder");
        printf("\n7. EXIT");
   do
    {
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &ch);
        
         switch(ch)
        {
            case 1:
                printf("\nEnter data: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
 
            case 2:
                printf("\nEnter data: ");
                scanf("%d", &data);
                root = delete(root, data);
                break;
 
            case 3:
                printf("\nEnter data: ");
                scanf("%d", &data);
                result = search(root, data);
                if (result == NULL)
                {
                    printf("\nNode not found!");
                }
                else
                {
                    printf("\n Node found");
                }
                break;
            case 4:
                inorder(root);
                break;
 
            case 5:
                preorder(root);
                break;
 
            case 6:
                postorder(root);
                break;
 
            }
 
    }while(ch<=6);
 
    return 0;
}


