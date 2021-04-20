#include<stdio.h>
#include<stdlib.h>

typedef struct Linklist
{
	float co;    //��ϵ�� 
	int exp;   //ָ�� 
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
	printf("1.����ʽ��������\n");
	printf("2.����ʽ��������\n");
	printf("3.��������ʽ���\n");
	printf("4.��������ʽ���\n");
	printf("5.�������ʽ��x0����ֵ\n");
	printf("6.����ʽ����k�׵�\n");
	printf("7.����ʽ�Ļ���\n"); 
	printf("8.��������ʽ���\n");
	printf("9.��������ʽ���\n");
	printf("\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			printf("�������ʽ\n");
			sortcreatlist(head);
			displaylist(head);
			break;
		case 2:
            printf("�������ʽ\n");
			sortcreatlist(head);
			converselist(head);
			displaylist(head);
			break;
		case 3:
			printf("��һ������ʽ(��coef==0ʱ��������)\n");
	        sortcreatlist(head1);
	        printf("�ڶ�������ʽ(��coef==0ʱ��������)\n");
	        sortcreatlist(head2);
	
            head=addlist(head1,head2);
            displaylist(head); 
            break;
        case 4:
        	printf("��һ������ʽ\n");
	        sortcreatlist(head1);
	        printf("�ڶ�������ʽ\n");
	        sortcreatlist(head2);
	
	        mexp1=head1->next->exp;
	        mexp2=head2->next->exp;
	        mexp3=mexp1+mexp2; 
	
	        converselist(head2);
	
	        p1=head1;
	        p2=head2;       //case�в��ܶ����µı��� 
	        head=multiplylist(head1,head2,mexp3);
	        displaylist(head); 
			break;
        case 5:
			printf("�������ʽ\n");
			sortcreatlist(head);
			printf("����x0��ֵ\n");
			scanf("%d",&x0);
			result=horner(head,x0);
			printf("result is %lf",result);
			break;
		case 6:
			printf("�������ʽ\n");
			sortcreatlist(head);
			head=qiudao(head);
			displaylist(head);
		case 7:
			printf("�������ʽ\n");
			sortcreatlist(head);
			head=jifen(head);
			displaylist(head);
        case 8:
		    printf("��һ������ʽ(��coef==0ʱ��������)\n");
	        sortcreatlist(head1);
	        printf("�ڶ�������ʽ(��coef==0ʱ��������)\n");
	        sortcreatlist(head2);
	
            head = sublist(head1,head2);
            displaylist(head);
            break;
        case 9:
        	printf("��һ������ʽ(��coef==0ʱ��������)\n");
	        sortcreatlist(head1);
	        printf("�ڶ�������ʽ(��coef==0ʱ��������)\n");
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
	linklist *p,*pre;  //����ָ�� 
	linklist *s;  //ָ�����ڵ��ָ��
//whileѭ���������������洢����ʽ
    printf("�Ƿ���ļ�����(����1��0)\n");
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
		    if(coef<-0.001||coef>0.001)          //��coefΪfloat���ͣ�ע���ж�  coef==0  Ӧд��  -0.001<coef<0.001�� 
		    {
			    while(p!=NULL&&expn<p->exp)     //��expn<p->expʱ��������p��pre 
			    {
				    pre=p;
				    p=p->next;                  //ʹ��pre��pָ����� 
			    }					
			    if(p!=NULL&&expn==p->exp)       //expn==expʱ    
			    {
				    p->co=p->co+coef;
			    }
			    else                            //expn>p->expʱ 
			    {
				    s=(linklist*)malloc(sizeof(linklist));
				    s->co=coef;
				    s->exp=expn;
				
				    pre->next=s;
				    s->next=p; 
			     } 
		    }    
		    else
		    break; //ѭ����ֹ����������Ϊ0��
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
		    if(coef<-0.001||coef>0.001)          //��coefΪfloat���ͣ�ע���ж�  coef==0  Ӧд��  -0.001<coef<0.001�� 
		    {
			    while(p!=NULL&&expn<p->exp)     //��expn<p->expʱ��������p��pre 
			    {
				    pre=p;
				    p=p->next;                  //ʹ��pre��pָ����� 
			    }					
			    if(p!=NULL&&expn==p->exp)       //expn==expʱ    
			        {
				    p->co=p->co+coef;
			    }
			    else                            //expn>p->expʱ 
			    {
				    s=(linklist*)malloc(sizeof(linklist));
				    s->co=coef;
				    s->exp=expn;
				
				    pre->next=s;
				    s->next=p; 
			     } 
		    }    
		    else
		    break; //ѭ����ֹ����������Ϊ0��
	    }
	 }
	else
	{
		printf("��������\n");
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
			p=pre;  //��Ҫ�Ĳ��� 
		 } 
	}
	return head;
}
void converselist(linklist *headnode)
{
	linklist *p,*q;
	p=headnode->next;    //��������ĵ�һ���ڵ� 
	headnode->next=NULL;     //�����������ͷ�ڵ� 
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
//��p1��p2ָ���һ���ڵ�		
		p1=head1->next;
		p2=head2->next;
//����exp==kʱ�ĳ���coef		
//p1��p2��β��ʱ��������		
		while(p1&&p2)
		{
			exp=p1->exp+p2->exp;   //ָ���� 	
			if(exp==k)       //�ҵ�exp==k����ʱ��coef=co1+co2  ��  p1,p2������ƶ�һλ 
			{
				coef+=p1->co*p2->co;
				p1=p1->next;
				p2=p2->next;
			}
			else if(exp<k)  //exp<kʱ��p1����ƶ�һλ 
		    p2=p2->next;
			else       //exp>kʱ��p2����ƶ�һλ 
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
		 printf("\n�Ƿ�д���ļ�\n(����0��1)");
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
double horner(linklist *head,int x)  //��6x^4+x^3+xΪ�� == x( x^2( 6x+1) +1)
{
	int i,k;
	linklist *p;
	double result = head->next->co*x;
	for(p=head->next;p->next!=NULL;p=p->next)
	{
		k = p->exp - p->next->exp;  //��������ݴβ� 
		result+=p->next->co;   //�ڲ����ŵĽ�� 
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
	printf("����k(k>=1)\n");
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
			p=pre;    //���ɾ����ע��Ҫ��֤�������� 
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
    float co2=head2->next->co;   //������ ϵ�� �� ����ݴ� 
    linklist *t,*s,*pre,*p;   //tΪ�洢�м�˻��ı�����sΪ�´����Ľڵ㣻 
    linklist *headx=initlist();  //�м�˻�������ͷ�ڵ� 
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
