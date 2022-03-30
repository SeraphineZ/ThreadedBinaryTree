#include<iostream>
using namespace std;

typedef char ElemType;

/*
线索存储标志位
Link(0)：表示指向左右孩子的指针
Thread(1):表示指向前驱后继的线索
*/
typedef enum {Link, Thread} PointerTag;

typedef struct BiThrNode{
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}BiThrNode, *BiThrTree;

//全局变量，始终指向刚刚访问过的节点
BiThrTree pre;

//创建一棵二叉树，约定用户遵照前序遍历方式输入数据
void createBiThrTree(BiThrTree *T){
    char c;
    scanf("%c", &c);
    if('#' == c){
        *T = NULL;
    }else{
        *T = (BiThrNode*)malloc(sizeof(BiThrNode));
        (*T)->data = c;
        (*T)->ltag = Link;
        (*T)->rtag = Link;
        createBiThrTree(&(*T)->lchild);
        createBiThrTree(&(*T)->rchild);
    }
}

//中序遍历线索化
void inThreading(BiThrTree T){
    if(T){
        inThreading(T->lchild);//递归左孩子线索华
        //节点处理
        if(!T->lchild){//处理前驱，什么时候能知道前驱，就是当前节点的时候，
//已经知道前一个是pre了，所以直接tag=thread，lchild=pre
            T->ltag = Thread;
            T->lchild = pre;
        }
        if(pre!=NULL && !pre->rchild){//处理后继，什么时候处理后继，只有访问到下一个的时候，
//才能知道下一个是谁，因为当访问下一个的时候，下一个是T，让pre的rchild指向T就好
            pre->rtag = Thread;
            pre->rchild = T;
        }
        pre = T;

        inThreading(T->rchild);//递归右孩子线索华
    }
}

//中序遍历线索二叉树---非递归
void InOrderThreading(BiThrTree T){
    BiThrTree p = T;
    while(p != NULL){
        //当ltag == Thread时，循环到中序序列第一个节点
        while(p->ltag == Link){
            p = p->lchild;
        }

        printf("%c ", p->data);
        while(p->rtag == Thread && p->rchild != NULL){
            p = p ->rchild;
            printf("%c ", p->data);
        }
        p = p->rchild;
    }

}

int main(){
    BiThrTree T = NULL;
    printf("请按前序序输入二叉树 (如:AB#CD##E##F#GH###)\n");
    createBiThrTree(&T);
    inThreading(T);
    pre->rtag = Thread;
    printf("中序遍历(输出)二叉线索树:\n");
    InOrderThreading(T);
    return 0;

}