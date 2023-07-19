#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left,*right;
};

struct node *root = NULL, *n, *temp;

void insert();
void inorder(struct node *temp);
void preorder(struct node *temp);
void postorder(struct node *temp);
// non recursive traversal
void inorder_non_recursive();
void preorder_non_recursive();
void postorder_non_recursive();

int main(){
    int ch;
    printf("Menu : 1.insert 2.inorder 3.preorder 4.postorder\n");
    printf("       non-recursive 5.inorder 6.preorder 7.postorder\n");

    do{
        printf("\n");
        printf("Enter choice : ");
        scanf("%d",&ch);

        switch(ch){
            case 1 : insert(); break;
            case 2 : inorder(root); break;
            case 3 : preorder(root); break;
            case 4 : postorder(root); break;
            case 5 : inorder_non_recursive(root); break;
            case 6 : preorder_non_recursive(root); break;
            case 7 : postorder_non_recursive(root); break;

            default : printf("Choice Again !! or enter - 0 to exit\n");
        }
    }while(ch!=0);

    return 0;
}

void insert(){
    n = (struct node*)malloc(sizeof(struct node));

    printf("Enter data : ");
    scanf("%d",&n->data);

    n->left = NULL;
    n->right = NULL;

    if(root == NULL){
        root = n;
    }else{
        temp = root;
        
        while(1){
            if(n->data < temp->data){
                if(temp->left == NULL){
                    temp->left = n; break;
                }else{
                    temp = temp->left;
                }
            }else{
                if(temp->right == NULL){
                    temp->right = n; break;
                }else{
                    temp = temp->right;
                }
            }
        }
    }

}

// inorder traversal

void inorder(struct node *temp){
    if(temp != NULL){
        inorder(temp->left);
        printf("%d \t",temp->data);
        inorder(temp->right);
    }
    
}

void preorder(struct node *temp){
    if(temp!=NULL){
        printf("%d \t",temp->data);
        preorder(temp->left);
        preorder(temp->right);
    }
}

void postorder(struct node *temp){
    if(temp!=NULL){
        postorder(temp->left);
        postorder(temp->right);
        printf("%d \t",temp->data);
    }
}

// non recursive traversals

void inorder_non_recursive(struct node *temp){
    struct node *stack[100];
    int top = -1;
    while(temp != NULL || top != -1){
        while(temp != NULL){
            stack[++top] = temp;
            temp = temp->left;
        }
        temp = stack[top--];
        printf("%d ",temp->data);
        temp = temp->right;
    }
}

void preorder_non_recursive(struct node *temp){
    struct node *stack[100];
    int top = -1;
    while(temp != NULL || top != -1){
        while(temp != NULL){
            printf("%d ",temp->data);
            stack[++top] = temp;
            temp = temp->left;
        }
        temp = stack[top--];
        temp = temp->right;
    }
}

// function for postorder without recursion
void postorder_non_recursive(struct node *temp){
    struct node *stack[100];
    int top = -1;
    do{
        while(temp != NULL){
            if(temp->right != NULL){
                stack[++top] = temp->right;
            }
            stack[++top] = temp;
            temp = temp->left;
        }
        temp = stack[top--];
        if(temp->right != NULL && stack[top] == temp->right){
            stack[top--];
            stack[++top] = temp;
            temp = temp->right;
        }else{
            printf("%d ",temp->data);
            temp = NULL;
        }
    }while(top != -1);
}
