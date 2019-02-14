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

//���еĳ�ʼ��
void QueueInit(Queue *q)
{
	assert(q);
	q->head = q->tail = BuyNewNode(0);   //��ͷ���ĵ�����
}

//�����
void QueuePush(Queue *q, DataType data)
{
	SListNode *node = BuyNewNode(data);
	q->tail->next = node;
	q->tail = q->tail->next;
}

//������
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

//�п�
int QueueEmpty(Queue *q)
{
	return (q->head->next == NULL);
}

//ȡ��ͷԪ��
DataType QueueFront(Queue *q)
{
	if (q->head->next != NULL)
	{
		return q->head->next->data;
	}
	return NULL;
}

//����������
TreeNode *CreateTree(DataType preorder[], int size, int *pused)
{
	if (size == 0)
	{
		*pused = 0;
		return NULL;
	}
	if (preorder[0] == -1)   //�ս��
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


//ǰ�����������(�ݹ�)
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

//����������������ݹ飩
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


//����������������ݹ飩
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

//�������������
 void LevelOrder(TreeNode *root)
 {
	 Queue q;
	 TreeNode *pFront;
	 if (root == NULL)
	 {
		 return;
	 }
	 QueueInit(&q);
	 QueuePush(&q, root);   //����е��ǽ���ַ�������ǽ�����ݣ�data��
	 while (!QueueEmpty(&q))
	 {
		 pFront = QueueFront(&q);   //ȡ��ͷԪ��
		 if (pFront->left != NULL)
		 {
			 QueuePush(&q, pFront->left);
		 }
		 if (pFront->right != NULL)
		 {
			 QueuePush(&q, pFront->right);
		 }
		 QueuePop(&q);     //��ͷԪ�س�����
		 printf("%d-> ", pFront->data);  //��ӡ�������
	 }
 }

//ǰ�����������(�ݹ�)�������
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

//�������ĸ߶�
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


//��k�������
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

//��Ҷ������
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


//�ж�һ������Ƿ���һ�Ŷ�������
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

//���������������������������Ƚ��
TreeNode *GetAncestorNode(TreeNode *root,TreeNode *node1,TreeNode *node2)
{
	if (root == NULL)
	{
		return NULL;
	}
	int n1InLeft = IsInTree(root->left, node1->data);
	int n2InLeft = IsInTree(root->left, node2->data);
	if (n1InLeft != 0 && n2InLeft == 0)   //node1��������node2��������
	{
		return root;
	}
	if (n1InLeft == 0 && n2InLeft != 0)   //node1����������node2������
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

//�ж�һ�ö������Ƿ���ƽ�������
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

//�����������Զ���������֮��ľ���
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

//�ж�һ�ö������Ƿ�����ȫ������
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

//��������ľ���
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

	printf("�������Ľ�����Ϊ��");
	printf("%d\n",PreOrderNode(root));

	printf("�������ĸ߶�Ϊ��");
	printf("%d\n", GetHeight(root));
	
	printf("��������1�������Ϊ��");
	printf("%d\n", GetKNode(root,1));

	printf("��������2�������Ϊ��");
	printf("%d\n", GetKNode(root, 2));

	printf("��������3�������Ϊ��");
	printf("%d\n", GetKNode(root, 3));

	printf("��������Ҷ������Ϊ��");
	printf("%d\n", LeafNode(root));

	if (IsInTree(root, 7) == 1)
	{
		printf("�ҵ���\n");
	}
	else
	{
		printf("û�ҵ�\n");
	}

	if (IsBalanceTree(root) != 0)
	{
		printf("�ö�������ƽ�������\n");
	}
	else
	{
		printf("�ö���������ƽ�������\n");
	}

	printf("����������Զ���������֮��ľ���Ϊ��");
	printf("%d\n", GetDistance(root));

	if (IsCompleteTree(root) != 0)
	{
		printf("�ö���������ȫ������\n");
	}
	else
	{
		printf("�ö�����������ȫ������\n");
	}

	Mirror(root);

	if (IsCompleteTree(root) != 0)
	{
		printf("�ö���������ȫ������\n");
	}
	else
	{
		printf("�ö�����������ȫ������\n");
	}

}