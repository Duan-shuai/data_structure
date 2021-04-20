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
hfnode* createheap(hfnode *node,int n);  //������С�ѣ���������Сֵ 
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
	int i,j,cnt=0;  //����ʱʹ�� 
	hfnode node[1000];
	hfnode *root;
	 
	p = getfile(a);   //��ȡ�ַ����и����ַ�������
//��ȡ�����ַ����ɵ�����	
	for(i=0;i<=127;i++)    
	{
		if(p[i] != 0)
		{
			cnt++;
			node[cnt].weight=p[i];   //�����1��ʼ����
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
		while(2*i <= n)   //���µ��� 
		{
			if(2*i==n)  //ż����� 
			{
				if(node[2*i].weight < node[i].weight)
				swap(&node[i],&node[2*i]);  //node[i]  ->������ 
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
hfnode* buildhftree(hfnode *node,int n)  //���������� ���ڵ�node �� �ڵ�����n 
{
	int i;
	hfnode *rear;
	rear=&node[n]; 
/*   A B C D E 
         C D E F 
		     E F G  
		         G H
				     I
ÿ��ǰ��ȥ��������㣬���油һ����㣬ֱ��ֻʣһ�����
ͷָ�� ��node(��node+1��ʼ),βָ�� �� rear(ָ�����һ�����) 
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
	return rear; //���ĸ��ڵ� 
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
	printf("\n\n����������     %d\n",nx1); 
	printf("�ȳ�����       %d\n",nx2);
	printf("ѹ����         %f\n",xy);
	printf("�������ַ�     %d\n",k);
	printf("���µ��ַ����� %d\n",n);
	printf("�ļ���homework_twoΪԭ�ĵ�\n");
	printf("�ļ���homework_two1Ϊ�����ĵ�\n");
	printf("�ļ���homework_two2Ϊ�����ĵ�\n");
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
		printf("����\n");
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
void levelorder(hfnode *t)
{
	seqque q;
	hfnode *pre,*p;
	q.flag=0;
	q.front=q.rear=0;
	enqueue(&q,t);
	while(q.front!=q.rear||q.flag!=0)  //���t�����Һ��ӽڵ㣬t���ӣ����Һ��ӽڵ�����С�����t���� 
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
