#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef int DataType;

typedef struct TreeNode
{
	DataType data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode *CreateNode(DataType data)
{
	TreeNode *node = (TreeNode *)malloc(sizeof (TreeNode));
	assert(node);
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

typedef int DataType;

typedef struct SListNode
{
	DataType data;
	struct SListNode *next;
}SListNode;

typedef struct Queue
{
	SListNode *head;
	SListNode *tail;
}Queue;

SListNode *BuyNewNode(DataType data)
{
	SListNode *NewNode = (SListNode *)malloc(sizeof(SListNode));
	assert(NewNode);
	NewNode->data = data;
	NewNode->next = NULL;
	return NewNode;
}

//队列的初始化
void QueueInit(Queue *q)
{
	assert(q);
	q->head = q->tail = BuyNewNode(0);   //带头结点的单链表
}

//入队列
void QueuePush(Queue *q, DataType data)
{
	SListNode *node = BuyNewNode(data);
	q->tail->next = node;
	q->tail = q->tail->next;
}

//出队列
void QueuePop(Queue *q)
{
	SListNode *DelNode = NULL;
	assert(q);
	DelNode = q->head->next;
	if (DelNode != NULL)
	{
		q->head->next = DelNode->next;
		free(DelNode);
	}
}

//判空
int QueueEmpty(Queue *q)
{
	return (q->head->next == NULL);
}

//取队头元素
DataType QueueFront(Queue *q)
{
	if (q->head->next != NULL)
	{
		return q->head->next->data;
	}
	return NULL;
}

//创建二叉树
TreeNode *CreateTree(DataType preorder[], int size, int *pused)
{
	if (size == 0)
	{
		*pused = 0;
		return NULL;
	}
	if (preorder[0] == -1)   //空结点
	{
		*pused = 1;
		return NULL;
	}

	int leftused = 0;
	int rightused = 0;
	TreeNode *root = CreateNode(preorder[0]);
	root->left = CreateTree(preorder + 1, size - 1, &leftused);
	root->right = CreateTree(preorder + 1 + leftused, size - 1 - leftused, &rightused);
	*pused = 1 + leftused + rightused;
	return root;
}


//前序遍历二叉树(递归)
void PreOrder(TreeNode *root)
{
	if (root == NULL)
	{
		return ;
	}
	printf("%d -> ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

//中序遍历二叉树（递归）
void InOrder(TreeNode *root)
{
	if (root == NULL)
	{
		return ;
	}
	InOrder(root->left);
	printf("%d -> ", root->data);
	InOrder(root->right);
}


//后序遍历二叉树（递归）
 void PostOrder(TreeNode *root)
{
	if (root == NULL)
	{
		return ;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d -> ", root->data);
}

//层序遍历二叉树
 void LevelOrder(TreeNode *root)
 {
	 Queue q;
	 TreeNode *pFront;
	 if (root == NULL)
	 {
		 return;
	 }
	 QueueInit(&q);
	 QueuePush(&q, root);   //入队列的是结点地址，而不是结点数据（data）
	 while (!QueueEmpty(&q))
	 {
		 pFront = QueueFront(&q);   //取队头元素
		 if (pFront->left != NULL)
		 {
			 QueuePush(&q, pFront->left);
		 }
		 if (pFront->right != NULL)
		 {
			 QueuePush(&q, pFront->right);
		 }
		 QueuePop(&q);     //队头元素出队列
		 printf("%d-> ", pFront->data);  //打印结点数据
	 }
 }

//前序遍历二叉树(递归)求结点个数
int PreOrderNode(TreeNode *root)
{
	static n = 0;
	if (root == NULL)
	{
		return 0;
	}
	n = n + 1;
	PreOrderNode(root->left);
	PreOrderNode(root->right);
	return n;
}

//二叉树的高度
int GetHeight(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}

	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	int m = GetHeight(root->left);
	int n = GetHeight(root->right);
	return ((m > n) ? m : n) + 1;
}


//第k层结点个数
int GetKNode(TreeNode *root, int k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return GetKNode(root->left, k - 1) + GetKNode(root->right, k - 1);
}

//求叶结点个数
int LeafNode(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return LeafNode(root->left) + LeafNode(root->right);
}


//判断一个结点是否在一颗二叉树中
int IsInTree(TreeNode *root,DataType data)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->data == data)
	{
		return 1;
	}
	if (IsInTree(root->left, data) == 1)
	{
		return 1;
	}
	return IsInTree(root->right, data);
}

//求二叉树中两个结点的最近公共祖先结点
TreeNode *GetAncestorNode(TreeNode *root,TreeNode *node1,TreeNode *node2)
{
	if (root == NULL)
	{
		return NULL;
	}
	int n1InLeft = IsInTree(root->left, node1->data);
	int n2InLeft = IsInTree(root->left, node2->data);
	if (n1InLeft != 0 && n2InLeft == 0)   //node1在左树，node2不在左树
	{
		return root;
	}
	if (n1InLeft == 0 && n2InLeft != 0)   //node1不在左树，node2在左树
	{
		return root;
	}
	if (n1InLeft != 0)   
	{
		return GetAncestorNode(root->left, node1, node2);
	}
	else
	{
		return GetAncestorNode(root->right, node1, node2);
	}
}

//判断一棵二叉树是否是平衡二叉树
int IsBalanceTree(TreeNode *root)
{
	if (root == NULL)
	{
		return 1;
	}
	int LeftHeight = GetHeight(root->left);
	int RightHeight = GetHeight(root->right);
	int diff = LeftHeight - RightHeight;
	if (!(diff >= -1 && diff <= 1))
	{
		return 0;
	}
	int LeftBalance = IsBalanceTree(root->left);
	if (LeftBalance == 0)
	{
		return 0;
	}
	return IsBalanceTree(root->right);
}

int Max_3(int a, int b, int c)
{
	if (a >= b && a >= c)
		return a;
	if (c >= a && c >= b)
		return c;
	return b;
}

//求二叉树中最远的两个结点之间的距离
int GetDistance(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	int LeftHeight = GetHeight(root->left);
	int RightHeight = GetHeight(root->right);
	int LeftMaxDistance = GetDistance(root->left);
	int RightMaxDistance = GetDistance(root->right);
	return Max_3(LeftMaxDistance, RightMaxDistance, LeftHeight + RightHeight);
}

//判断一棵二叉树是否是完全二叉树
int IsCompleteTree(TreeNode *root)
{
	Queue q;
	TreeNode *pFront;
	if (root == NULL)
	{
		return 1;
	}
	QueueInit(&q);
	QueuePush(&q, root);
	while (1)
	{
		pFront = QueueFront(&q);
		if (pFront == NULL)
		{
			break;
		}
		QueuePush(&q, pFront->left);
		QueuePush(&q, pFront->right);
		QueuePop(&q);
	}
	while (!QueueEmpty(&q))
	{
		pFront = QueueFront(&q);
		QueuePop(&q);
		if (pFront != NULL)
		{
			return 0;
		}
	}
	return 1;
}

//求二叉树的镜像
TreeNode *Mirror(TreeNode *root)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return root;
	}
	TreeNode *temp = root->left;
	root->left = root->right;
	root->right = temp;
	Mirror(root->left);
	Mirror(root->right);
	return root;
}

void test()
{
	//DataType preorder[] = { 1, 2, 4, -1, -1, -1, 3, 5, -1, -1, 6 };
	//DataType preorder[] = { 1, 2, 4, -1, -1, -1, 3 };
	DataType preorder[] = { 1, 2, 2, -1, 3, -1, 3 };
	int size = sizeof(preorder) / sizeof(DataType);
	int pused = 0;
	TreeNode *root = CreateTree(preorder, size, &pused);
	assert(pused == size);
	PreOrder(root);
	printf("NULL\n");

	InOrder(root);
	printf("NULL\n");

	PostOrder(root);
	printf("NULL\n");

	LevelOrder(root);
	printf("NULL\n");

	printf("二叉树的结点个数为：");
	printf("%d\n",PreOrderNode(root));

	printf("二叉树的高度为：");
	printf("%d\n", GetHeight(root));
	
	printf("二叉树第1层结点个数为：");
	printf("%d\n", GetKNode(root,1));

	printf("二叉树第2层结点个数为：");
	printf("%d\n", GetKNode(root, 2));

	printf("二叉树第3层结点个数为：");
	printf("%d\n", GetKNode(root, 3));

	printf("二叉树的叶结点个数为：");
	printf("%d\n", LeafNode(root));

	if (IsInTree(root, 7) == 1)
	{
		printf("找到了\n");
	}
	else
	{
		printf("没找到\n");
	}

	if (IsBalanceTree(root) != 0)
	{
		printf("该二叉树是平衡二叉树\n");
	}
	else
	{
		printf("该二叉树不是平衡二叉树\n");
	}

	printf("二叉树中最远的两个结点之间的距离为：");
	printf("%d\n", GetDistance(root));

	if (IsCompleteTree(root) != 0)
	{
		printf("该二叉树是完全二叉树\n");
	}
	else
	{
		printf("该二叉树不是完全二叉树\n");
	}

	Mirror(root);

	if (IsCompleteTree(root) != 0)
	{
		printf("该二叉树是完全二叉树\n");
	}
	else
	{
		printf("该二叉树不是完全二叉树\n");
	}

}