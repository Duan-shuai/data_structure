#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct 	TREE
{
	int weight;
	char data;
	struct TREE *lchild,*rchild,*parent;
}hfnode;

typedef struct QUE
{
	hfnode *queue[20];
	int front,rear;
	int flag;
}seqque;

int* getfile(int a[]);
hfnode* createheap(hfnode *node,int n);  //建立最小堆，并返回最小值 
void swap(hfnode *s1,hfnode *s2);
hfnode* buildhftree(hfnode *node,int n);
void getcode(hfnode *node,int n);
void ziprate(int p[],int n,hfnode *t); 
 
void enqueue(seqque *q,hfnode *t);
hfnode* dequeue(seqque *q);
void levelorder(hfnode *t);
char str[128][50]; 
 
int main()
{
	int a[128]={0};
	int *p;   
	int i,j,cnt=0;  //计数时使用 
	hfnode node[1000];
	hfnode *root;
	 
	p = getfile(a);   //获取字符串中各个字符的数量
//获取非零字符构成的数组	
	for(i=0;i<=127;i++)    
	{
		if(p[i] != 0)
		{
			cnt++;
			node[cnt].weight=p[i];   //数组从1开始计数
			node[cnt].data = i; 
		}
	}	
	
    createheap(node,cnt);
	root = buildhftree(node,cnt);
	levelorder(root);
	getcode(root,cnt);
	ziprate(p,cnt,root);
	return 0;
} 
int* getfile(int a[])
{
	FILE *fp;
	fp=fopen("homework_two.txt","r+");
	char ch;
	ch=getc(fp);
	while(ch !=-1)
	{
		a[ch]++;
		ch = getc(fp);
	}
	return a;
 } 
void swap(hfnode *s1,hfnode *s2)
{
	hfnode t=*s1;
	t.lchild = (*s1).lchild;
	t.rchild = (*s1).rchild;
	t.parent = (*s1).parent;
	*s1 = *s2;
	(*s1).lchild = (*s2).lchild;
	(*s1).lchild = (*s2).lchild;
	(*s1).parent = (*s2).parent;
	*s2 = t;
	(*s2).lchild = t.lchild;
	(*s2).rchild = t.rchild;
	(*s2).parent = t.parent;
} 
hfnode* createheap(hfnode *node,int n)
{
	int i;
	for(i=n/2;i>=1;i--)
	{
		while(2*i <= n)   //向下调整 
		{
			if(2*i==n)  //偶数结点 
			{
				if(node[2*i].weight < node[i].weight)
				swap(&node[i],&node[2*i]);  //node[i]  ->解引用 
				break;
			}
			else
			{
				if(node[2*i].weight < node[i].weight || node[2*i+1].weight < node[i].weight)
				{
					if(node[2*i].weight < node[2*i+1].weight)
					{
						swap(&node[2*i],&node[i]);
						i=2*i;
					}
					else
					{
						swap(&node[2*i+1],&node[i]);
						i=2*i+1;
					}
				}
				else
				break;
			}
		}
	}
	return &node[1];
} 
hfnode* buildhftree(hfnode *node,int n)  //哈夫曼树的 根节点node 和 节点数量n 
{
	int i;
	hfnode *rear;
	rear=&node[n]; 
/*   A B C D E 
         C D E F 
		     E F G  
		         G H
				     I
每次前面去掉两个结点，后面补一个结点，直到只剩一个结点
头指针 ：node(从node+1开始),尾指针 ： rear(指向最后一个结点) 
*/	
    while(node + 1 < rear)
    {
        (rear+1)->lchild = createheap(node,rear-node);
		(rear+1)->rchild = createheap(node+1,rear-node-1);
		rear[1].weight = rear[1].lchild->weight + rear[1].rchild->weight;
		
		rear = rear+1 ;
		node = node+2 ;	
    }
    levelorder(rear);
    rear->parent=NULL;
	return rear; //树的根节点 
}
void getcode(hfnode *node,int n)
{
	hfnode *que[300];
	hfnode *s;
	int front,rear,top=-1;
	char stack[300];
	char ch;
	int i,j;
	front=rear=0;
	
	que[rear++] = node;
	printf("\n");
	while(front != rear)
	{
		s = que[front++];
		if(s->lchild != NULL )
		{
			que[rear++] = s->lchild;
			que[rear++] = s->rchild;			
		}
		else 
		{
			i = s->data;
			ch = s->data;
			while(s->parent != NULL)
			{
				if(s == s->parent->lchild)
				stack[++top] = '0';
				else  
				stack[++top] = '1';
								
				s=s->parent;
			}
			printf("%c ",ch);
			j=0;
			while(top >= 0)
			{
				ch = stack[top--];
				printf("%c",ch);
				str[i][j++] = ch;
			}
			str[i][j] = '\0';
			printf("\n");
		} 
	}
}
void ziprate(int p[],int n,hfnode *t)
{
	FILE *fp,*fp1,*fp2,*fp3;
	fp=fopen("homework_two.txt","r+");
	fp1=fopen("homework_two1.txt","w");
	fp2=fopen("homework_two2.txt","w");
	fp3=fopen("homework_two.txt","r+");
	int i,j,k=1;
	int nx1=0,nx2=0;
	char ch;
	hfnode *root;
	ch=getc(fp);
	while(ch != -1)
	{
		j=0;
		while(str[ch][j]!='\0')
		{
			fputc(str[ch][j],fp1);
			j++;
		}
		nx1 = nx1 + j;
		ch = getc(fp);
		k++;
	}
	nx2 = (log(n)/log(2))*k;
	float xy=(float)nx1/nx2; 
	printf("\n\n哈夫曼编码     %d\n",nx1); 
	printf("等长编码       %d\n",nx2);
	printf("压缩率         %f\n",xy);
	printf("文章总字符     %d\n",k);
	printf("文章的字符种类 %d\n",n);
	printf("文件：homework_two为原文档\n");
	printf("文件：homework_two1为编码文档\n");
	printf("文件：homework_two2为译码文档\n");
	root = t;
	ch = fgetc(fp3);
	while(ch != -1)
	{
/*		if(t->lchild != NULL)
		{
			if(ch == '0')
		    t=t->lchild;
		    else if(ch == '1')
		    t=t->rchild;
		}
		else
		{
			fputc(t->data,fp2); 
			t = root;
		}
*/
	    fputc(ch,fp2);
		ch = fgetc(fp3);
	}
}

void enqueue(seqque *q,hfnode *t)
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
hfnode* dequeue(seqque *q)
{
	hfnode *t;
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
void levelorder(hfnode *t)
{
	seqque q;
	hfnode *pre,*p;
	q.flag=0;
	q.front=q.rear=0;
	enqueue(&q,t);
	while(q.front!=q.rear||q.flag!=0)  //如果t有左右孩子节点，t出队，左右孩子节点入队列。否则，t出队 
	{
		t=dequeue(&q);
		if(t->lchild)
		{
			t->weight = t->lchild->weight + t->rchild->weight;
		    t->lchild->parent = t;
		    t->rchild->parent = t;
		    enqueue(&q,t->lchild);
		}
		if(t->rchild)
		enqueue(&q,t->rchild);
	}
}
