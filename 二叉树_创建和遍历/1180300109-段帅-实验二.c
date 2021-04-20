#include<stdio.h>
#include<stdlib.h>

typedef struct TREE
{
	int data;
	struct TREE *lchild,*rchild;
}bitnode;
typedef struct QUE
{
	bitnode *queue[20];
	int front,rear;
	int flag;
}seqque;
typedef struct STACK
{
	bitnode *stack[20];
	int top;
}seqstack;

bitnode* createtree();
bitnode* createtree1(int pre[],int in[],int n);
void pushstack(seqstack *s,bitnode *t);
bitnode* popstack(seqstack *s);
void enqueue(seqque *q,bitnode *t);
bitnode* dequeue(seqque *q);
void preorder1(bitnode *t);
void preorder2(bitnode *t);
void inorder1(bitnode *t);
void inorder2(bitnode *t);
void postorder1(bitnode *t);
void postorder2(bitnode *t);
void levelorder(bitnode *t);
void treeprint(bitnode *t,int level1);
int levelprint(bitnode *t);
void wanquantree(bitnode *t); 

int main()
{
	int a,y;
	int i=0,x;
	int pre[20],in[20];
	printf("1.按先序序列构建二叉树(输入0表示空节点)\n");
	printf("2.给定中序和先序序列构建二叉树\n");
	
	bitnode *t;
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			t=createtree();
			break;
		case 2:
            while(getchar()!='\n');
	        printf("输入前序遍历序列(输入0表示停止)\n");
	        while(1)
	        {
		        scanf("%d",&pre[i]);
		        while(getchar()!='\n'); 
		        if(pre[i]==0)
		        break;
		        i++;
	        }
	        i=0; 
	        printf("输入中序遍历序列(输入0表示停止)\n");
	        while(1)
	        {
		        scanf("%d",&in[i]);
		        while(getchar()!='\n');
		        if(in[i]==0)
		        break;
		        i++;
	        }
	        x=i;		
			t=createtree1(pre,in,x);
			break;
	    }
	printf("\n先序遍历（递归）\n");
	preorder1(t);
	printf("\n先序遍历（非递归）\n");
	preorder2(t);
	printf("\n中序遍历（递归）\n");
	inorder1(t);
	printf("\n中序遍历（非递归）\n");
	inorder2(t);
	printf("\n后序遍历（递归）\n");
	postorder1(t);
	printf("\n后序遍历（非递归）\n");
	postorder1(t); 
	printf("\n层序遍历\n");
	levelorder(t);
	printf("\n层序打印(纵向)\n");
	y=levelprint(t);
	printf("\n树状输出(横向)\n");
	treeprint(t,1);
	printf("\n二叉树宽度 :  %d \n ",y);
	wanquantree(t);
	
}
bitnode* createtree()
{
	bitnode *t;
	int x;
	scanf("%d",&x);
	if(x==0)
	t=NULL;
	else
	{
		t=(bitnode*)malloc(sizeof(bitnode));
		t->data=x;
		t->lchild=createtree();
		t->rchild=createtree(); 
	}
	return t;
}
bitnode* createtree1(int pre[],int in[],int n)
{
	int i=0,m;
	bitnode *t;
    t=(bitnode*)malloc(sizeof(bitnode));
	while(i<n)              //遍历寻找根节点 
	{
		if(pre[0]==in[i])   //找到根节点 
		{
			m=i;
			break;
		}
		i++;
	 }
	if(i>=n)              //节点为空 
	{
		return NULL;
	}
	t->data=pre[0];
	t->lchild=createtree1(pre+1,in,m);      
	t->rchild=createtree1(pre+m+1,in+m+1,n-m-1);
	return t; 
}
void enqueue(seqque *q,bitnode *t)
{
	if(q->front==q->rear&&q->flag==1)
	{
		printf("队满\n");
	}
	else
	{
		q->queue[q->rear]=t;
		q->rear=(q->rear+1)%20;
		q->flag=1;
	}
}
bitnode* dequeue(seqque *q)
{
	bitnode *t;
	if(q->front==q->rear&&q->flag==0)
	{
		printf("队空\n");
		return NULL;
	}
	else
	{
		t=q->queue[q->front];
		q->front=(q->front+1)%20;
		q->flag=0;
	}
	return t;
}
void pushstack(seqstack *s,bitnode *t)
{
	if(s->top>=19)
	printf("栈满\n");
	else
	{
		s->top++;
		s->stack[s->top] = t; 
	}
}
bitnode* popstack(seqstack *s)
{
	bitnode *t;
	if(s->top<=-1)
	printf("栈空\n");
	else
	{
		t = s->stack[s->top];
		s->top--;
	}
	return t;
}
void preorder1(bitnode *t)
{
	if(t)
	{
			printf("%d ",t->data);  //根节点 
		    preorder1(t->lchild);   //左节点 
		    preorder2(t->rchild);   //右节点 
	}
}
void preorder2(bitnode *t)       //t始终指向当前要处理的节点 
{
	seqstack s;
	s.top=-1;
	while(s.top!=-1 || t!=NULL)  //遍历结束条件：t指向空&&栈空 
	{
		while(t)
		{
			printf("%d ",t->data);  //访问根节点
			pushstack(&s,t);        //栈保存遍历的 节点 
			t=t->lchild;            //遍历左子树 
		}
		if(s.top>-1)                //下一个要访问的节点 : 栈顶元素的右子节点 
		{
			t = popstack(&s);
			t = t->rchild;        
		}  
	}
}
void inorder1(bitnode *t)
{
	if(t)
	{
		inorder1(t->lchild);
		printf("%d ",t->data);
		inorder1(t->rchild);
	}
}
void inorder2(bitnode *t)   //t始终为正在处理的节点 
{
	seqstack s;
	s.top=-1;
	while(s.top!=-1 || t!=NULL)
	{
		while(t)
		{
			pushstack(&s,t);
			t=t->lchild;      //左子树入栈，不访问 
		}
		if(s.top>-1)
		{
			t=popstack(&s);
			printf("%d ",t->data);  //访问左节点 和 根节点 
			t=t->rchild;    //遍历右子树 
		}
	}
}
void postorder1(bitnode *t)
{
	if(t)
	{
		postorder1(t->lchild);
		postorder1(t->rchild);
		printf("%d ",t->data);
	}
 }
void postorder2(bitnode *t)
{
	bitnode *q; //标记已经访问过的节点 
	seqstack s;
	s.top=-1;
	while(s.top!=-1 || t!=NULL)
	{
		while(t)
		{
			pushstack(&s,t);
			t=t->lchild;
		}
		if(s.top>-1)
		{
			t=popstack(&s);
			if(t->rchild==NULL || t->rchild==q)//若无右子节点  或   右子节点已经访问过
			{
				q=t;
				printf("%d ",t->data);
				t=NULL;
			}
			else   //否则先访问右子节点，再访问根节点 
			t=t->rchild; 
		}
	}
 } 
void levelorder(bitnode *t)
{
	seqque q;
	q.flag=0;
	q.front=q.rear=0;
	enqueue(&q,t);                       //根节点入队 
	while(q.front!=q.rear || q.flag!=0)  //如果t有左右孩子节点，t出队，左右孩子节点入队列。否则，t出队 
	{
		t=dequeue(&q);                   //t出队 
		printf("%d ",t->data);           
//判断入队元素 
		if(t->lchild)
		enqueue(&q,t->lchild);
		if(t->rchild)
		enqueue(&q,t->rchild);
	}
}
void treeprint(bitnode *t,int level1)   //桉树状打印二叉树 (节点指针，层次)
{
	int i;
	if(t==NULL)
	return ;                           //若t==NULL 返回上一层递归 
	treeprint(t->rchild,level1+1);     //打印右子树，层次加一 
	for(i=0;i<=level1;i++)             //打印层次 
	{
		printf("  ");           
	}
	printf("%d\n",t->data);           //打印根节点 
	treeprint(t->lchild,level1+1);    //打印右子树 
}
int levelprint(bitnode *t)
{
	int cur,next,wide=0; //当前行未打印的元素 和 下一行要打印的元素
	seqque q;
	q.flag=0;
	q.front=q.rear=0;
	enqueue(&q,t);
	cur=1;
	next=0;
	while(q.front!=q.rear || q.flag!=0)
	{
		t=dequeue(&q);
		printf("%d  ",t->data);
		cur--;
		if(t->lchild)
		{
			enqueue(&q,t->lchild);
			next++;
		}
		if(t->rchild)
		{
			enqueue(&q,t->rchild);
			next++;
		}
		if(cur==0)          //打印完一行 
		{
			printf("\n");
			cur=next;       //下一行初始化
			wide=wide>cur?wide:cur; 
			next=0;          
		}
	}
	return wide; 
}
void wanquantree(bitnode *t)
{
	int flag=0;
	seqque q;
	q.flag=0;
	q.front=q.rear=0;
	enqueue(&q,t);                       //根节点入队 
	while(q.front!=q.rear || q.flag!=0)  //如果t有左右孩子节点，t出队，左右孩子节点入队列。否则，t出队 
	{
		t=dequeue(&q);                   //t出队 
		if(t!=NULL)
		{           
		    enqueue(&q,t->lchild);
		    enqueue(&q,t->rchild);
		}
		else
		{
            break;
		}
	}
	while(q.front!=q.rear || q.flag!=0)
	{
		t=dequeue(&q);
		if(t!=NULL)
		{
			flag=1;
			printf("非完全二叉树\n");
			break;
		}
	}
	if(flag==0)
	{
		printf("完全二叉树\n");
	}
}
