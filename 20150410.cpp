/*
	二叉树的基本操作
*/
#include <stdio.h>
#include <iostream>
using namespace std;
typedef struct BitNode
{
    char data;
    struct BitNode *lchild, *rchild;
} BiNode, *BiTree;

void CreatTree(BiTree &T) //创建树
{
    char data;
    //data = getchar();
    cin >> data;
    if (data == '#')
    {
        T = NULL;
    }
    else
    {
        T = new BiNode;
        T->data = data;
        CreatTree(T->lchild);
        CreatTree(T->rchild);
    }
}

void Preorder(BiTree &T) //先序遍历
{
    if (T)
    {
        cout << T->data << " ";
        Preorder(T->lchild);
        Preorder(T->rchild);
    }
}

void Inorder(BiTree &T) //中序遍历
{
    if (T)
    {
        Inorder(T->lchild);
        cout << T->data << " ";
        Inorder(T->rchild);
    }
}

void Postorder(BiTree &T) //后序遍历
{
    if (T)
    {
        Postorder(T->lchild);
        Postorder(T->rchild);
        cout << T->data << " ";
    }
}

void LevelOrder( BiTree &T) //层次遍历
{
    int maxsize = 50;
    BiTree queue[maxsize];
    int front, rear;
    front = rear = -1;
    rear++;
    queue[rear] = T;
    while (front != rear)
    {
        front = (front + 1) % maxsize;
        BiTree tree = queue[front];
        cout << tree->data << " ";
        if (tree->lchild != NULL)
        {
            rear = (rear + 1) % maxsize;
            queue[rear] = tree->lchild;
        }
        if (tree->rchild != NULL)
        {
            rear = (rear + 1) % maxsize;
            queue[rear] = tree->rchild;
        }
    }
}

int DepthBiTree(const BiTree &T)  //递归求树的深度
{
    int ldepth;
    int rdepth;
    if(T == NULL) //空树
    {
        return 0;
    }
    ldepth = DepthBiTree(T->lchild);
    rdepth = DepthBiTree(T->rchild);
    return (ldepth > rdepth) ? (ldepth+1) : (rdepth+1);
}

int LeafCountBiTree(const BiTree &T) //计算叶子数
{
    if (T == NULL)
    {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL)
    {
        return 1;
    }
    return LeafCountBiTree(T->lchild) + LeafCountBiTree(T->rchild);
}

int NumNode(BiTree T) //节点个数
{
    if(T == NULL)
    {
         return 0;
    }  
    else
    {
         return NumNode(T->lchild) + NumNode(T->rchild) + 1;
    }    
}

BiTree Locate(const BiTree T, char x)//查找,不能处理找不到的情况
{
    BiTree P = T, Q = T;
    if(P == NULL)
    {
        return NULL;
    }    
    else
    {
        if( P->data == x )
        {
             return P;
        }
        else
        {
            P = Locate(P->lchild, x);
            Q = Locate(Q->rchild, x);
            if(P)
            {
                return P;
            }
            else if (Q)
            {
                return Q;
            }
            else
            {
                return NULL;
            }
        }
    }
}

void ExchangeChild(BiTree &T) //交换左右子树
{
    if (T)
    {
        BiTree temp = NULL;
        if (T->lchild || T->rchild)
        {
            temp = T->lchild;
            T->lchild = T->rchild;
            T->rchild = temp;
            ExchangeChild(T->lchild);
            ExchangeChild(T->rchild);
        }
    }
}

void DestroyBiTree(BiTree &T) //递归销毁一棵二叉树
{
    if(T)
    {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        delete T;
        T = NULL;
    }
}

void PrintTree(BiTree &T) //打印树
{
    if (T)
    {
        cout << " " << T->data;
        if (T->lchild || T->rchild)
        {
            cout << "(";
            PrintTree(T->lchild);
            if (T->rchild)
            {
                cout << ",";
                PrintTree(T->rchild);
            }
            cout << ")";
        }
    }
}

int main()
{
    freopen("input", "r", stdin);
    BiTree T;

    cout << "please input the tree :";
    CreatTree(T);
    PrintTree(T);
    cout << endl;

    cout << "Preorder: ";
    Preorder(T);
    cout << endl;

    cout << "Inorder:  ";
    Inorder(T);
    cout << endl;

    cout << "Postorder:";
    Postorder(T);
    cout << endl;

    int depth = DepthBiTree(T);
    cout << "Depth: " <<  depth << endl;

    int leafcount = LeafCountBiTree(T);
    cout << "The tree leaf: " << leafcount << endl;

    cout << "LevelOrder: "; 
    LevelOrder( T);
    cout << endl;

    int numnode = NumNode(T);
    cout << "The tree node number: " << numnode << endl;

    char ch;
    cin >> ch;
    BiTree find = Locate(T, ch);
    if (find->data)
    {
        cout << "Find !" << endl;
    }
    else
    {
        cout << " Not find !" <<endl;
    }
    
    ExchangeChild(T);
    cout << "Exchange the child: ";
    PrintTree(T);
    cout << endl;

    DestroyBiTree(T);
    //PrintTree(T);
    return 0;
}
