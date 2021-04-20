#include<stdio.h>
#include<stdlib.h>

typedef struct Linklist
{
	float co;    //常系数 
	int exp;   //指数 
	struct Linklist *next;
}linklist;
linklist* initlist()
{
	linklist *head;
	head=(linklist*)malloc(sizeof(linklist));
	head->next=NULL;
	return head;
}
void sortcreatlist(linklist *headnode);
void converselist(linklist *headnode);
linklist* addlist(linklist *head1,linklist *head2);
linklist* sublist(linklist *head1,linklist *head2);
linklist* multiplylist(linklist *head1,linklist *head2,int mexp);
linklist* divlist(linklist *head1,linklist *head2);
double horner(linklist *headnode,int x);
linklist* qiudao(linklist *headnode);
linklist* jifen(linklist *headnode);
void displaylist(linklist *head);
int main()
{
	int x,mexp1,mexp2,mexp3,x0;
	double result;
	linklist *head1=initlist();
	linklist *head2=initlist();
	linklist *head=initlist();
	linklist *p1,*p2;
	
	printf("choose your operation\n");
	printf("1.多项式降幂排序\n");
	printf("2.多项式升幂排序\n");
	printf("3.两个多项式相加\n");
	printf("4.两个多项式相乘\n");
	printf("5.计算多项式在x0处的值\n");
	printf("6.多项式的求k阶导\n");
	printf("7.多项式的积分\n"); 
	printf("8.两个多项式相减\n");
	printf("9.两个多项式相除\n");
	printf("\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			printf("输入多项式\n");
			sortcreatlist(head);
			displaylist(head);
			break;
		case 2:
            printf("输入多项式\n");
			sortcreatlist(head);
			converselist(head);
			displaylist(head);
			break;
		case 3:
			printf("第一个多项式(当coef==0时结束输入)\n");
	        sortcreatlist(head1);
	        printf("第二个多项式(当coef==0时结束输入)\n");
	        sortcreatlist(head2);
	
            head=addlist(head1,head2);
            displaylist(head); 
            break;
        case 4:
        	printf("第一个多项式\n");
	        sortcreatlist(head1);
	        printf("第二个多项式\n");
	        sortcreatlist(head2);
	
	        mexp1=head1->next->exp;
	        mexp2=head2->next->exp;
	        mexp3=mexp1+mexp2; 
	
	        converselist(head2);
	
	        p1=head1;
	        p2=head2;       //case中不能定义新的变量 
	        head=multiplylist(head1,head2,mexp3);
	        displaylist(head); 
			break;
        case 5:
			printf("输入多项式\n");
			sortcreatlist(head);
			printf("输入x0的值\n");
			scanf("%d",&x0);
			result=horner(head,x0);
			printf("result is %lf",result);
			break;
		case 6:
			printf("输入多项式\n");
			sortcreatlist(head);
			head=qiudao(head);
			displaylist(head);
		case 7:
			printf("输入多项式\n");
			sortcreatlist(head);
			head=jifen(head);
			displaylist(head);
        case 8:
		    printf("第一个多项式(当coef==0时结束输入)\n");
	        sortcreatlist(head1);
	        printf("第二个多项式(当coef==0时结束输入)\n");
	        sortcreatlist(head2);
	
            head = sublist(head1,head2);
            displaylist(head);
            break;
        case 9:
        	printf("第一个多项式(当coef==0时结束输入)\n");
	        sortcreatlist(head1);
	        printf("第二个多项式(当coef==0时结束输入)\n");
	        sortcreatlist(head2);
	
            head = divlist(head1,head2);
            displaylist(head);
            break;
	}
}
void sortcreatlist(linklist *headnode)
{
	int x;
	char ax[20];
	int expn;
	float coef;
	FILE *fp=NULL;
	fp=fopen("abc.txt","r+");
	linklist *p,*pre;  //遍历指针 
	linklist *s;  //指向插入节点的指针
//while循环：创建链表来存储多项式
    printf("是否从文件读入(输入1或0)\n");
	scanf("%d",&x);
	if(x==1)
	{
        while(1)
	    {
		    p=headnode->next;
		    pre=headnode; 
		    printf("input coef\n");
		    fgets(ax,20,fp);
			coef=atof(ax);
		    printf("input expn\n");
		    fgets(ax,20,fp);
			expn=atoi(ax);
		    if(coef<-0.001||coef>0.001)          //若coef为float类型：注意判断  coef==0  应写成  -0.001<coef<0.001； 
		    {
			    while(p!=NULL&&expn<p->exp)     //若expn<p->exp时：向后更新p和pre 
			    {
				    pre=p;
				    p=p->next;                  //使用pre和p指针遍历 
			    }					
			    if(p!=NULL&&expn==p->exp)       //expn==exp时    
			    {
				    p->co=p->co+coef;
			    }
			    else                            //expn>p->exp时 
			    {
				    s=(linklist*)malloc(sizeof(linklist));
				    s->co=coef;
				    s->exp=expn;
				
				    pre->next=s;
				    s->next=p; 
			     } 
		    }    
		    else
		    break; //循环终止条件：常数为0；
	    }
	}
	else if(x==0) 
	 {
	 	while(1)
	    {
		    p=headnode->next;
		    pre=headnode; 
		    printf("input coef\n");
		    scanf("%f",&coef);
		    printf("input expn\n");
		    scanf("%d",&expn);
		    if(coef<-0.001||coef>0.001)          //若coef为float类型：注意判断  coef==0  应写成  -0.001<coef<0.001； 
		    {
			    while(p!=NULL&&expn<p->exp)     //若expn<p->exp时：向后更新p和pre 
			    {
				    pre=p;
				    p=p->next;                  //使用pre和p指针遍历 
			    }					
			    if(p!=NULL&&expn==p->exp)       //expn==exp时    
			        {
				    p->co=p->co+coef;
			    }
			    else                            //expn>p->exp时 
			    {
				    s=(linklist*)malloc(sizeof(linklist));
				    s->co=coef;
				    s->exp=expn;
				
				    pre->next=s;
				    s->next=p; 
			     } 
		    }    
		    else
		    break; //循环终止条件：常数为0；
	    }
	 }
	else
	{
		printf("错误输入\n");
		sortcreatlist(headnode);
	  }  
	
}
linklist* addlist(linklist *head1,linklist *head2)
{
	linklist *head=initlist();
	linklist *pre=head;
	linklist *p1,*p2,*s;
	p1=head1->next;
	p2=head2->next;		
	while(p1&&p2)
	{
		s=(linklist*)malloc(sizeof(linklist));
		if(p1->exp > p2->exp)
		{
			s->co=p1->co;
			s->exp=p1->exp;		
			p1=p1->next;
		}
		else if(p1->exp == p2->exp)
		{
			s->co=p1->co+p2->co;
			s->exp=p1->exp;
			p1=p1->next;
			p2=p2->next;
		}
		else
		{
			s->co=p2->co;
			s->exp=p2->exp;	
			p2=p2->next;
		}
		pre->next=s;
		pre=s;	
		s->next=NULL;
	}
    if(p1==NULL)
	{
		pre->next=p2;
	}	
	else
	pre->next=p1;
	return head;
}
linklist* sublist(linklist *head1,linklist *head2)
{
	linklist *p,*pre;
	linklist *head=initlist();
	p=head2;
	while(p->next)
	{
		p=p->next;
		p->co=-p->co;
	}
	head=addlist(head1,head2);
	p=head;
	while(p->next)
	{
		pre=p;
		p=p->next;
		if(p->co==0)
		{
			pre->next=p->next;
			free(p);
			p=pre;  //重要的步骤 
		 } 
	}
	return head;
}
void converselist(linklist *headnode)
{
	linklist *p,*q;
	p=headnode->next;    //操作链表的第一个节点 
	headnode->next=NULL;     //排序后的链表的头节点 
	while(p)
	{
		q=p;
		p=p->next;	
		q->next=headnode->next;
		headnode->next=q;
	}
}
linklist* multiplylist(linklist *head1,linklist *head2,int mexp)
{
	int k,exp;
	float coef=0;
	linklist *head,*p1,*p2,*s,*pre;
	head=initlist();
	pre=head;
	for(k=mexp;k>=0;k--)
	{
		coef=0;
//将p1，p2指向第一个节点		
		p1=head1->next;
		p2=head2->next;
//查找exp==k时的常数coef		
//p1或p2到尾部时结束查找		
		while(p1&&p2)
		{
			exp=p1->exp+p2->exp;   //指数和 	
			if(exp==k)       //找到exp==k的项时，coef=co1+co2  且  p1,p2各向后移动一位 
			{
				coef+=p1->co*p2->co;
				p1=p1->next;
				p2=p2->next;
			}
			else if(exp<k)  //exp<k时，p1向后移动一位 
		    p2=p2->next;
			else       //exp>k时，p2向后移动一位 
			p1=p1->next;
		}
		if(coef>0.0001||coef<-0.0001)
		{
			s=(linklist*)malloc(sizeof(linklist));
			s->co=coef;
			s->exp=k;
			s->next=NULL;	
			pre->next=s;
			pre=s;
		}
	}
	return head;
}
void displaylist(linklist *head)
{
	int x;
	FILE *fp=NULL;
	fp=fopen("abc.txt","w+");
	linklist *p;
	p=head;
	while(p->next->next!=NULL)
		{
		    p=p->next;
			printf("%.2fX^%d + ",p->co,p->exp);
		 }
		 p=p->next;
		 printf("%.2f X^%d",p->co,p->exp);
		 printf("\n是否写入文件\n(输入0或1)");
		 scanf("%d",&x);
		 if(x==1)
		 {
		 	p=head;
	        while(p->next->next!=NULL)
		    {
		        p=p->next;
			    fprintf(fp,"%.2fX^%d + ",p->co,p->exp);
		    }
		     p=p->next;
		     fprintf(fp,"%.2f X^%d",p->co,p->exp);
		}
}
double horner(linklist *head,int x)  //以6x^4+x^3+x为例 == x( x^2( 6x+1) +1)
{
	int i,k;
	linklist *p;
	double result = head->next->co*x;
	for(p=head->next;p->next!=NULL;p=p->next)
	{
		k = p->exp - p->next->exp;  //相邻项的幂次差 
		result+=p->next->co;   //内部括号的结果 
		for(i=0;i<k;i++)
		{
			result=result*x;
		 } 
	}
	return result;
}
linklist* qiudao(linklist *headnode)
{
	linklist *p,*pre,*head,*s;
	int x,i;
	printf("输入k(k>=1)\n");
	scanf("%d",&x); 
	head=initlist();
	pre=head;
	p=headnode;
	if(x > headnode->next->exp)
	{
		s=(linklist*)malloc(sizeof(linklist));
	    s->co=0;
	    s->exp=0;
	    head->next=s;
	    s->next=NULL;
	    return head;
	}
	while(p->next!=NULL)
	{
		p=p->next;	
		s=(linklist*)malloc(sizeof(linklist));
		s->next=NULL;	
		if(p->exp!=0)
		{
			s->co=p->co;
			for(i=1;i<=x;i++)
			{
				s->co=s->co*p->exp;
				p->exp--;
			}
			s->exp=p->exp;
		}
		else
		free(s);	
		pre->next=s;
		pre=s;
	}
	p=head;
	while(p->next!=NULL)
	{
		pre=p;
		p=p->next;
		if(p->exp<0)
		{
			pre->next=p->next;
			free(p);
			p=pre;    //逐个删除后注意要保证链接仍在 
		 } 
	}

	return head;
}
linklist* jifen(linklist *headnode)
{
	linklist *p,*pre,*head,*s;
	head=initlist();
	pre=head;
	p=headnode;
	while(p->next!=NULL)
	{
		p=p->next;	
		s=(linklist*)malloc(sizeof(linklist));
		s->next=NULL;	
		if(p->exp!=0)
		{
			s->co=p->co/(p->exp+1);
			s->exp=p->exp+1;
		}
		else
		free(s);	
		pre->next=s;
		pre=s;
	}
	return head;
}
linklist* divlist(linklist *head1,linklist *head2)
{
    int exp2=head2->next->exp;
    float co2=head2->next->co;   //除数的 系数 与 最高幂次 
    linklist *t,*s,*pre,*p;   //t为存储中间乘积的变量；s为新创建的节点； 
    linklist *headx=initlist();  //中间乘积变量的头节点 
    linklist *head=initlist(); 
    pre=head;
    printf("%d",pre->exp); 
	while(head1->next!=NULL && head1->next->exp >= exp2)
	{
		s=(linklist*)malloc(sizeof(linklist));
		s->co=head1->next->co / co2;
		s->exp=head1->next->exp - exp2;
		s->next=NULL;
		headx->next=s;	
		t=multiplylist(headx, head2, exp2 + s->exp);		
		pre->next=s;
		pre=s;		
		head1=sublist(head1,t);
	 }
	return head;
}
