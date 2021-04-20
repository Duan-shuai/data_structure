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
	printf("1.���������й���������(����0��ʾ�սڵ�)\n");
	printf("2.����������������й���������\n");
	
	bitnode *t;
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			t=createtree();
			break;
		case 2:
            while(getchar()!='\n');
	        printf("����ǰ���������(����0��ʾֹͣ)\n");
	        while(1)
	        {
		        scanf("%d",&pre[i]);
		        while(getchar()!='\n'); 
		        if(pre[i]==0)
		        break;
		        i++;
	        }
	        i=0; 
	        printf("���������������(����0��ʾֹͣ)\n");
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
	printf("\n����������ݹ飩\n");
	preorder1(t);
	printf("\n����������ǵݹ飩\n");
	preorder2(t);
	printf("\n����������ݹ飩\n");
	inorder1(t);
	printf("\n����������ǵݹ飩\n");
	inorder2(t);
	printf("\n����������ݹ飩\n");
	postorder1(t);
	printf("\n����������ǵݹ飩\n");
	postorder1(t); 
	printf("\n�������\n");
	levelorder(t);
	printf("\n�����ӡ(����)\n");
	y=levelprint(t);
	printf("\n��״���(����)\n");
	treeprint(t,1);
	printf("\n��������� :  %d \n ",y);
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
	while(i<n)              //����Ѱ�Ҹ��ڵ� 
	{
		if(pre[0]==in[i])   //�ҵ����ڵ� 
		{
			m=i;
			break;
		}
		i++;
	 }
	if(i>=n)              //�ڵ�Ϊ�� 
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
		printf("����\n");
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
		printf("�ӿ�\n");
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
	printf("ջ��\n");
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
	printf("ջ��\n");
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
			printf("%d ",t->data);  //���ڵ� 
		    preorder1(t->lchild);   //��ڵ� 
		    preorder2(t->rchild);   //�ҽڵ� 
	}
}
void preorder2(bitnode *t)       //tʼ��ָ��ǰҪ����Ľڵ� 
{
	seqstack s;
	s.top=-1;
	while(s.top!=-1 || t!=NULL)  //��������������tָ���&&ջ�� 
	{
		while(t)
		{
			printf("%d ",t->data);  //���ʸ��ڵ�
			pushstack(&s,t);        //ջ��������� �ڵ� 
			t=t->lchild;            //���������� 
		}
		if(s.top>-1)                //��һ��Ҫ���ʵĽڵ� : ջ��Ԫ�ص����ӽڵ� 
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
void inorder2(bitnode *t)   //tʼ��Ϊ���ڴ���Ľڵ� 
{
	seqstack s;
	s.top=-1;
	while(s.top!=-1 || t!=NULL)
	{
		while(t)
		{
			pushstack(&s,t);
			t=t->lchild;      //��������ջ�������� 
		}
		if(s.top>-1)
		{
			t=popstack(&s);
			printf("%d ",t->data);  //������ڵ� �� ���ڵ� 
			t=t->rchild;    //���������� 
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
	bitnode *q; //����Ѿ����ʹ��Ľڵ� 
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
			if(t->rchild==NULL || t->rchild==q)//�������ӽڵ�  ��   ���ӽڵ��Ѿ����ʹ�
			{
				q=t;
				printf("%d ",t->data);
				t=NULL;
			}
			else   //�����ȷ������ӽڵ㣬�ٷ��ʸ��ڵ� 
			t=t->rchild; 
		}
	}
 } 
void levelorder(bitnode *t)
{
	seqque q;
	q.flag=0;
	q.front=q.rear=0;
	enqueue(&q,t);                       //���ڵ���� 
	while(q.front!=q.rear || q.flag!=0)  //���t�����Һ��ӽڵ㣬t���ӣ����Һ��ӽڵ�����С�����t���� 
	{
		t=dequeue(&q);                   //t���� 
		printf("%d ",t->data);           
//�ж����Ԫ�� 
		if(t->lchild)
		enqueue(&q,t->lchild);
		if(t->rchild)
		enqueue(&q,t->rchild);
	}
}
void treeprint(bitnode *t,int level1)   //����״��ӡ������ (�ڵ�ָ�룬���)
{
	int i;
	if(t==NULL)
	return ;                           //��t==NULL ������һ��ݹ� 
	treeprint(t->rchild,level1+1);     //��ӡ����������μ�һ 
	for(i=0;i<=level1;i++)             //��ӡ��� 
	{
		printf("  ");           
	}
	printf("%d\n",t->data);           //��ӡ���ڵ� 
	treeprint(t->lchild,level1+1);    //��ӡ������ 
}
int levelprint(bitnode *t)
{
	int cur,next,wide=0; //��ǰ��δ��ӡ��Ԫ�� �� ��һ��Ҫ��ӡ��Ԫ��
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
		if(cur==0)          //��ӡ��һ�� 
		{
			printf("\n");
			cur=next;       //��һ�г�ʼ��
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
	enqueue(&q,t);                       //���ڵ���� 
	while(q.front!=q.rear || q.flag!=0)  //���t�����Һ��ӽڵ㣬t���ӣ����Һ��ӽڵ�����С�����t���� 
	{
		t=dequeue(&q);                   //t���� 
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
			printf("����ȫ������\n");
			break;
		}
	}
	if(flag==0)
	{
		printf("��ȫ������\n");
	}
}
