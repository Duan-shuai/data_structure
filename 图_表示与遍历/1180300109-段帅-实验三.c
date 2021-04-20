#include<stdio.h>
#include<stdlib.h>

typedef struct Graph1
{
	char vexs[100];  //顶点 
	int arc[100][100];   //邻接矩阵 
	int numvex,numedge;   //边数和顶点数 
	int flag;   //图类型 
 }graph1;
 
typedef struct Edgenode  //边表的结点 
{
	int adjvex;  //顶点的下标
	int weight;  //边权值 
	struct Edgenode *next;   
}edge; 
typedef struct  Vexnode  //顶点集 
{
	char data;  //顶点信息
	edge *frist;  //边表的头指针 
}vex;
typedef struct Graph2 
{
	int flag;
	int numvex,numedge;
	vex vexs[100];  //顶点表：每个表项是一个边表链表 
}graph2;
int visit[100]={0};
int visit1[100]={0};
int visit2[100]={0};
int count = 0;
int count1 =0;
int dfsn[100] = {0};
int bfsn[100] = {0};

int locatevex1(char ch,graph1 *g);  
void creategraph1(graph1 *g);
void creategraph2(graph2 *g);
int locatevex2(graph2 *g,char ch);
//邻接矩阵 
void dfsx1(graph1 *g,int n);//递归 
void dfsx2(graph1 *g,int n);//非递归
void bfsx(graph1 *g,int n);
//邻接表 
void dfsy1(graph2 *g,int n);//递归
void dfsy2(graph2 *g,int n);
void bfsy(graph2 *g,int n); 

int main()
{
	graph1 gx;
	graph2 gy;
	int x=0,y;
	int i;
	
	while(x != 1 && x != 2)
	{
        printf("1.邻接矩阵建立图\n");
	    printf("2.邻接表建立图\n");
	    scanf("%d",&x);
	    while(getchar()!='\n');
	}
	if(x == 1)
	{
		creategraph1(&gx);
		printf("1.1深度优先搜素序列(邻接矩阵-递归)\n");
		for(i=0;i<gx.numvex;i++)  //对各个连通分量 
	    {
		    if(visit[i] == 0)  
		    dfsx1(&gx,i); 
	    }
	    printf("\n");
		printf("1.2深度优先搜素序列(邻接矩阵-非递归)\n");
		for(i=0;i<gx.numvex;i++)  //对各个连通分量 
	    {
		    if(visit1[i] == 0)  
		    dfsx2(&gx,i); 
	    }
	    printf("\n");
		printf("1.3深度优先搜索编号\n");
		for(i=0;i<gx.numvex;i++)
		{
			printf("%c : ",gx.vexs[i]);
			printf("%d   ",dfsn[i]);
			if(i%5==0 && i>0)
			printf("\n"); 
		}
		printf("\n");
		printf("2.1广度优先搜素序列(邻接矩阵)\n");
		for(i=0;i<gx.numvex;i++)  //对各个连通分量 
	    {
		    if(visit2[i] == 0)  
		    bfsx(&gx,i); 
	    }
	    printf("\n");
		printf("2.2广度度优先搜索编号\n");
		for(i=0;i<gx.numvex;i++)
		{
			printf("%c : ",gx.vexs[i]);
			printf("%d   ",bfsn[i]);
			if(i%5==0 && i>0)
			printf("\n"); 
		}
	}
	else
	{
		creategraph2(&gy);
		printf("1.1深度优先搜素(邻接表-递归)\n");
		for(i=0;i<gy.numvex;i++)
	    {  
		    if(visit[i] == 0)
			    dfsy1(&gy,i);
	    }
	    printf("\n");
		printf("1.2深度优先搜素序列(邻接表-非递归)\n");
		for(i=0;i<gy.numvex;i++)
	    {  
		    if(visit1[i] == 0)
			    dfsy2(&gy,i);
	    }
	    printf("\n");
		printf("1.3深度优先搜索编号\n");
		for(i=0;i<gy.numvex;i++)
		{
			printf("%c : ",gy.vexs[i].data);
			printf("%d   ",dfsn[i]);
			if(i%5==0 && i>0)
			printf("\n"); 
		}
		printf("\n");
		printf("2.1广度优先搜素序列(邻接表)\n");
		for(i=0;i<gy.numvex;i++)  //对各个连通分量 
	    {
		    if(visit2[i] == 0)  
		    bfsy(&gy,i); 
	    }
		printf("\n");
		printf("2.2广度优先搜索编号\n");
		for(i=0;i<gy.numvex;i++)
		{
			printf("%c : ",gy.vexs[i].data);
			printf("%d   ",bfsn[i]);
			if(i%5==0 && i>0)
			printf("\n"); 
		} 
	}
	printf("\n");
	printf("(a)----(b)----(c)----(d)\n");
	printf("-        -    -       -\n");
	printf("-          -          -\n");
	printf("-        -   -        -\n");
	printf("(e)----(f)----(g)----(h)\n");
	printf("-        -    -       -\n");
	printf("-          -          -\n");
	printf("-        -   -        -\n");
	printf("(i)----(j)----(k)----(l)\n");
	return 0;
}

void creategraph1(graph1 *g)
{
	FILE *fp=NULL;
	fp=fopen("lab_three.txt","r+");
	int i,j,k,w;
	int x;
	char p,q;
//初始化边	
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			g->arc[i][j] = 0;
		}
	 }
//确定图的种类
    while(1)
	{
		printf("选择图的种类\n");
		printf("1.有向图\n");
		printf("2.无向图\n");
		printf("3.带权有向图\n");
		printf("4.带权无向图\n");
	    scanf("%d",&g->flag);
	    if(g->flag == 1 || g->flag ==2 || g->flag == 3 || g->flag==4)
	    break;
	}	 
//确定边的数量和点的数量	
	printf("input numvex and numedge\n");
	scanf("%d%d",&g->numvex,&g->numedge);
    while(getchar()!='\n');  //等待回车并读入 
    printf("是否从文件读入\n");
    scanf("%d",&x);
    while(getchar()!='\n'); 
if(x == 0)
{
    	//为点赋值
    printf("初始化点\n");
	for(k=0;k<g->numvex;k++)
	{
		printf("input vex %d\n",k); 
		g->vexs[k] = getchar();
		while(getchar()!='\n');
	}
//为边赋权值
    printf("初始化边\n");
    for(k=0;k<g->numedge;k++)
	{
		printf("input edge %d\n",k);
		p=getchar();
		i=locatevex1(p,g); 
		q=getchar();
		j=locatevex1(q,g);
		while(getchar()!='\n');
		if(g->flag == 1)
		    g->arc[i][j]=1;
		else if(g->flag == 2)
		{
			g->arc[i][j]=1;
			g->arc[j][i]=1;
		}
		else if(g->flag == 3)
		{
			printf("input the weight\n");
		    scanf("%d",&w);
		    g->arc[i][j]=w;
		    while(getchar()!='\n');
		}
		else if(g->flag == 4)
		{
			printf("input the weight\n");
		    scanf("%d",&w);
		    g->arc[i][j]=w;
		    g->arc[j][i]=w;        //无向图 
		    while(getchar()!='\n');
		}
		else
		printf("error\n");
	}	 
}
else
{
	for(k=0;k<g->numvex;k++)
	{ 
	    printf("input vex %d\n",k);
		g->vexs[k] = fgetc(fp);
		while(fgetc(fp)!='\n');
	}
	for(k=0;k<g->numedge;k++)
	{
		printf("input edge %d\n",k);
		p=fgetc(fp);
		i=locatevex1(p,g); 
		q=fgetc(fp);
		j=locatevex1(q,g);
		while(fgetc(fp)!='\n');
		g->arc[i][j]=1;
		g->arc[j][i]=1;
    }
}
}
int locatevex1(char ch,graph1 *g)   
{
	int i;
	for(i=0;i<g->numvex;i++)
	{
		if(g->vexs[i] == ch)
		return i;
	}
	printf("not find vex\nerror\n");
	return -1;
} 

void creategraph2(graph2 *g)
{
	int i,j,k,x;
	char p,q;
	edge *s,*pre;
	int y;
	FILE *fp=NULL;
	fp=fopen("lab_three.txt","r+");
//选择图的类型
    while(1)
	{
		printf("选择图的种类\n");
		printf("1.有向图\n");
		printf("2.无向图\n");
		printf("3.带权有向图\n");
		printf("4.带权无向图\n");
	    scanf("%d",&g->flag);
	    if(g->flag == 1 || g->flag ==2 || g->flag == 3 || g->flag==4)
	    break;
	}	
	printf("input numvex and numedge\n");
	scanf("%d%d",&g->numvex,&g->numedge);
	while(getchar()!='\n');	
//创建顶点
    printf("是否从文件读入\n");
    scanf("%d",&y);
    while(getchar()!='\n');
if(y==0)
{
    printf("创建顶点\n");	
	for(i=0;i<g->numvex;i++)
	{
		printf("input vex %d\n",i);
		g->vexs[i].data=getchar();
		while(getchar()!='\n');
	}
//创建边
    for(k=0;k<g->numedge;k++)
	{
		i=-1;
		j=-1;
		while(i<0 || j<0)
		{
			printf("input edge %d\n",k);
		    p=getchar();
		    i=locatevex2(g,p);
		    q=getchar();
		    j=locatevex2(g,q);
		    while(getchar()!='\n');
		}
		if(g->flag == 1)
		{
			s=(edge*)malloc(sizeof(edge));
			s->adjvex=j;
//头插法			
			s->next=g->vexs[i].frist;  //vexs[i].frist始终指向边表的第一个元素  			
			g->vexs[i].frist = s;  //更新vexs[i].frist 			 
		}
		else if(g->flag == 2)
		{
			s=(edge*)malloc(sizeof(edge));
			s->adjvex=j;
									
			s->next=g->vexs[i].frist;    			
			g->vexs[i].frist = s;  //更新vexs[i].frist
			
			s=(edge*)malloc(sizeof(edge));
			s->adjvex=i;
			
			s->next=g->vexs[j].frist;
			g->vexs[j].frist = s; 
		}
		else if(g->flag == 3)
		{
			printf("input weight\n");
			scanf("%d",&x);
			while(getchar()!='\n');
			s=(edge*)malloc(sizeof(edge));
			s->adjvex=j;
			s->weight=x;
			
			s->next=g->vexs[i].frist;  			
			g->vexs[i].frist = s;  		
		}
		else if(g->flag == 4)
		{
			printf("input weight\n");
			scanf("%d",&x);
			while(getchar()!='\n');
			
			s=(edge*)malloc(sizeof(edge));
			s->adjvex=j;
			s->weight=x;
			
			s->next=g->vexs[i].frist;    			
			g->vexs[i].frist = s;  
			
			s=(edge*)malloc(sizeof(edge));
			s->adjvex=i;
			s->weight=x;
 
			s->next=g->vexs[j].frist;
			g->vexs[j].frist = s; 
		} 
	}	 	
}
else
{
	for(i=0;i<g->numvex;i++)
	{
		printf("input vex %d\n",i);
		g->vexs[i].data=fgetc(fp);
		while(fgetc(fp)!='\n');
	}
	for(k=0;k<g->numedge;k++)
	{
		printf("input edge %d\n",k);
		p=fgetc(fp);
		i=locatevex2(g,p);
		q=fgetc(fp);
		j=locatevex2(g,q);
		while(fgetc(fp)!='\n');
		s=(edge*)malloc(sizeof(edge));
		s->adjvex=j;
									
		s->next=g->vexs[i].frist;    			
		g->vexs[i].frist = s;  //更新vexs[i].frist
			
		s=(edge*)malloc(sizeof(edge));
		s->adjvex=i;
			
		s->next=g->vexs[j].frist;
		g->vexs[j].frist = s; 
    }
}
    
}
int locatevex2(graph2 *g,char ch)
{
	int i;
	for(i=0;i<g->numvex;i++)
	{
		if(ch == g->vexs[i].data)
		return i;
	}
	printf("no find vex\nerror\n");
	return -1;
}

void dfsx1(graph1 *g,int n)
{
	int i;
	dfsn[n] = count++;
	printf("%c ",g->vexs[n]);
	visit[n] = 1;
	for(i=1;i<g->numvex;i++)
	{
		if(g->arc[n][i] > 0 && visit[i] == 0)
		{
			dfsx1(g,i);
		} 
	}
}
void dfsx2(graph1* g,int n)
{
	int stack[100];
	int top=0;
	int data,i;
	printf("%c ",g->vexs[n]);
	visit1[n] = 1;
	stack[top++] = n;
	data = n;
	while(top != 0)
	{
		for(i=0;i<g->numvex;i++)
		{
			if(g->arc[data][i]!=0 && visit1[i] == 0) 
			{
				printf("%c ",g->vexs[i]);
			    visit1[i] = 1;
			    stack[top++] = i;
			    data = i;
			    break;
			}
		}
		if(i == g->numvex)
		{
			data = stack[--top];
		}
	}
}

void dfsy1(graph2 *g,int n)
{
	dfsn[n] = count++;
	edge *p;
	printf("%c ",g->vexs[n].data);
	visit[n] = 1;
	p=g->vexs[n].frist;
	while(p)
	{
		if(visit[p->adjvex] == 0)
		dfsy1(g,p->adjvex);
		
		p=p->next;
	}
}
void dfsy2(graph2 *g,int n)
{
	int stack[100]; 
    edge *p;
    int top = 0;
    int x;
    
    visit1[n] = 1;
    printf("%c ", g->vexs[n].data);
	stack[top++] = n;   

    p = g->vexs[n].frist;
	x = n; 
    while(top != 0)  
    {  
        p = g->vexs[x].frist; 
        while(p)  
        {  
            if(visit1[p->adjvex] == 0) 
            {                               
                printf("%c ",g->vexs[p->adjvex].data);
				visit1[p->adjvex] = 1;  
                stack[top++] = p->adjvex; 
                p = g->vexs[p->adjvex].frist; 
            }  
            else  
                p = p->next;  
        }
        if(p == NULL)
        {
            x = stack[--top];  
        }
     }   
}

void bfsx(graph1 *g,int n)
{
	int i,p;
	int que[100];
	int front,rear;
	front=rear=0;
	que[rear++] = n;
	visit2[n] = 1;
	while(front != rear)
	{
		p=que[front++];
		printf("%c ",g->vexs[p]);
		bfsn[p] = count1++;
		for(i=0;i<g->numvex;i++)
		{
			if(g->arc[p][i] > 0 && visit2[i] == 0)
			{	
			    que[rear++] = i;
				visit2[i] = 1;
			}
		}
	}
	return;
}
void bfsy(graph2 *g,int n)
{
	int que[100];
	int p;
	int front,rear;
	edge *q;
	front = rear =0;
	que[rear++] = n;
	visit2[n] = 1;
	while(front != rear)
	{
		p=que[front++];
		printf("%c ",g->vexs[p].data);
		bfsn[p] = count1++;
		q = g->vexs[n].frist;
		while(q)
		{
			if(visit2[q->adjvex] == 0)
			{
				que[rear++] = q->adjvex;
			    visit2[q->adjvex] = 1;
			}
			q = q->next;
		}
	}
} 
