#include<stdio.h>
#include<stdlib.h> 
#include<time.h>
typedef struct NODE 
{
	int data;
	struct NODE *lchild,*rchild;
}bitnode;
bitnode* initnode(bitnode *t)
{
	t = (bitnode*)malloc(sizeof(bitnode));
	t->data = 0;
	t->lchild=NULL;
	t->rchild=NULL;
	return t;
} 
void swap(int *x,int *y)
{
	int t = *x;
	*x = *y;
	*y =t;
}
void insert_tree(bitnode *t,int x);
void delete_tree(bitnode *t,int x);
void print_tree(bitnode *t);
void findnode(bitnode *t,int x);
int midsearch1(int a[],int low,int high,int x);  //�ݹ� 
int midsearch2(int a[],int low,int high,int x);  //�ǵݹ� 
int main()
{
	while(1)
	{ 
		bitnode *t,*root,*root1,*t1;
	    int i,j = 0,x1,x2,x[1024];
	    int n,a1[100],a1x,xxx;
	    root = initnode(t);   //��ʼ�� 
	    root1 = initnode(t1);
	    int xy;
	    clock_t start,stop;
		printf("ѡ�����\n");
		printf("1.  BST�Ľ��������롢ɾ�������ҡ��������\n");
		printf("2.  �۰����ʵ��\n"); 
		printf("3.  BST �� �۰���ҵ����ܱȽ�\n");
		scanf("%d",&xy);
		while(getchar() != '\n');
		switch(xy)
		{
			case 1:
				printf("����(����) ����������\n");
				scanf("%d",&n);
				while(getchar() != '\n');
				for(i = 0 ;i < n ; i++)
				{
					printf("������%d : \n",i+1);
					scanf("%d",&a1[i]);
					while(getchar() != '\n');
					insert_tree(root,a1[i]);
				}
				t = root->lchild;
				printf("������������� : \n");                      
	            print_tree(t);
				printf("\n����Ҫɾ���Ľ��\n");
				scanf("%d",&a1x);
				while(getchar()!= '\n');
				delete_tree(t,a1x);
				print_tree(t);
				printf("\n");
				break;
			case 2:
				printf("����������\n");
				scanf("%d",&n);
				while(getchar()!='\n');
				for(i=0 ; i < n ; i++)
				{
					printf("�����㣨��˳��\n");
					scanf("%d",&a1[i]);
				}
				printf("����Ҫ���ҵĽ��\n");
				scanf("%d",&a1x);
				while(getchar()!='\n');
				printf("�ݹ�\n");
				x1=midsearch1(a1,0,n-1,a1x);
				printf("�����±� : %d\n",x1);
				printf("�ǵݹ�\n");
				x2=midsearch2(a1,0,n-1,a1x);
				printf("�����±� : %d\n",x2);
				break;
			case 3:
				printf("˳�������������\n");
				for(i = 1 ; i < 2048 ; i+=2)
	            {
		            insert_tree(root,i);
	            }
	                t = root->lchild;
	                print_tree(t);
	            //����������� 
	            printf("\n������н������������\n"); 
				for(i = 0 ; i < 1024 ; i++)
	            {
		            x[i] = 2*i+1;  //��ʼ�� 
	            }
		        srand((unsigned)time(NULL)); 
	            for(i = 0 ; i < 1024 ; i++)
	            {
		            x1 = rand()%1024;
		            x2 = rand()%1024;
		            swap(&x[x1],&x[x2]);  //������������� 
	            }
	            
	            for(i = 0 ;i < 1024 ; i++)
	            {
		            printf("%d ",x[i]);
		            insert_tree(root1,x[i]);
	            }
	            while(getchar()!= '\n');
	            t1 = root1->lchild;
	            print_tree(t1);
				printf("\n");
				//�����ٶ�
				for(i = 0 ; i < 1024 ; i++)
	            {
		            x[i] = 2*i+1;  //��ʼ�� 
	            }
				printf("����Ҫ���ҵ�Ԫ��\n");
				scanf("%d",&a1x);
				start=clock();
	            for(i=0;i<1000000;i++)
	            {
	                findnode(t,a1x);
                }
                stop=clock();
                double duration=((double)(start-stop))/CLK_TCK;
                printf("\n���������˳��ʱ�䣺%lf",duration);
				
				start=clock();
	            for(i=0;i<1000000;i++)
	            {
	                findnode(t1,a1x);
                }
                stop=clock();
                duration=((double)(start-stop))/CLK_TCK;
                printf("\n��������������ʱ�䣺%lf",duration);
				
				start=clock();
	            for(i=0;i<1000000;i++)
	            {
	                xxx=midsearch2(x,0,1023,a1x);
                }
                stop=clock();
                duration=((double)(start-stop))/CLK_TCK;
                printf("\n�۰����ʱ�䣺%lf",duration);
				printf("\ns�����±� %d\n",xxx);
				break;    				 
		}
	}
}
void findnode(bitnode *t,int x)
{
	bitnode *p=t,*pre = NULL;
	while(p!=NULL && x!=p->data)
	{
		if(x<p->data)
		{
			pre=p;
			p=p->lchild;
		}
		else
		{
			pre=p;
			p=p->rchild;
		}
	}
	if(p==NULL)
	{
		printf("δ�ҵ�Ԫ��\n");
		return;
	}
}
void insert_tree(bitnode *root , int x)
{
	bitnode *p;//���õ�ǰ��� 
	bitnode *s;
	if(root->lchild == NULL && root->rchild == NULL)
	{
		s= (bitnode*)malloc(sizeof(bitnode));
		root->lchild = root->rchild = s;
		s->data = x;
		s->lchild = s->rchild = NULL; 
		return ;
	}
	p = root->lchild;
	while(p)
	{
		if(x < p->data)
		{
			if(p->lchild)
				p = p->lchild;
			else
			{
				s = (bitnode*)malloc(sizeof(bitnode));
			    s->data = x;
			    s->lchild=s->rchild=NULL;
			    p->lchild = s;
			    p = NULL;
			}
		}
		else if(x > p->data)
		{
			if(p->rchild)
			    p = p->rchild;
			else
			{
				s = (bitnode*)malloc(sizeof(bitnode));
			    s->data = x;
			    s->lchild=s->rchild=NULL;
			    p->rchild = s;
			    p = NULL;
			}
		}
	}
}
void print_tree(bitnode *t)
{
	if(t)
	{
		print_tree(t->lchild);
		printf("%d ",t->data);
		print_tree(t->rchild);
	}
}
void delete_tree(bitnode *t,int x)
{
	int flag=0,flag1=1;//�жϲ��ҽ���Ǹ������/���ӽ�㣿 
	bitnode *p=t,*pre = NULL;
	bitnode *pnext,*pre1;
	bitnode *txx;
	while(p!=NULL && x!=p->data)
	{
		if(x<p->data)
		{
			pre=p;
			p=p->lchild;
			flag=0;
		}
		else
		{
			pre=p;
			p=p->rchild;
			flag=1;
		}
	}
	if(p==NULL)
	{
		printf("δ�ҵ�Ԫ��\n");
		return ;
	 }
	 else
	 {
	    if(p->lchild==NULL && p->rchild==NULL)
	 	{
	 		if(flag==0)
	 		pre->lchild=NULL;
	 		else
	 		pre->rchild=NULL;
		 }
        else if(p->lchild!=NULL && p->rchild==NULL)
		{
			if(flag==0)
				pre->lchild=p->lchild;
			else
				pre->rchild=p->lchild;
		}
		else if(p->lchild==NULL && p->rchild!=NULL)
		{
			if(flag==0)
				pre->lchild=p->rchild;
			else
				pre->rchild=p->rchild;
		}
		else if(p->lchild!=NULL && p->rchild!=NULL)
		{
//Ѱ�Һ�̽�㣬���ҵ���̽��ĸ���㣬��Ǳ�����̽��ʱ��������ڵ㻹���ҽڵ� 
				pre1=p;
				pnext=p->rchild;
				while(pnext->lchild!=NULL)
				{
					flag1 = 0;
					pre1 = pnext;
					pnext = pnext->lchild;
				}
				if(flag==0)
				pre->lchild=pnext; //��̽�㸲��Ҫɾ���Ľ��
				else
				pre->rchild=pnext;
				 
				pnext->lchild=p->lchild;
				
				if(flag1==0)
				{
				 	if(pnext->rchild==NULL)
				 	{
				 		pnext->rchild=p->rchild;
					}
					else
					{
					 	pre1->lchild=pnext->rchild;
					 	pnext->rchild=p->rchild;
					}
				}
		}
		free(p);
	 } 
}

int midsearch1(int a[],int low,int high,int x)
{
	int mid = (low + high)/2;
	if(x > a[mid])
	midsearch1(a,mid,high,x);
	else if(x < a[mid])
	midsearch1(a,low,mid,x);
	else
	return mid;
}
int midsearch2(int a[],int low,int high,int x)
{
	int mid;
	while(low != high)
	{
		mid = (low + high)/2;
		if(x > a[mid])
	    {
	    	low = mid + 1;
		}
	    else if(x < a[mid])
	    {
	    	high = mid - 1;
		}
	    else
	    return mid;
	}
} 
