//��׺ת��׺
//1.����һ��ջ����1������ǲ�������ֱ�����
//              ��2���������������Ƚ�ջ��������͵�ǰ����������ȼ�
//                         ���������ջ�����������ջ
//                         ���������ջ�����������ջֱ����ǰ���������ջ������� 
//       ��֤ջ��������������ȼ���� 

//��׺���ʽ��ֵ 
//1.���� ���� ����ջ
//2.�������������ջ��Ԫ�����㣬�ٽ������ջ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

typedef struct STACk
{
	float data[20];
	int top;
}stack;

void pushstack(stack *s,float x);
float popstack(stack *s);
float computeexpress(char a[]);
void translateexpress(char in[],char post[]);

int main()
{
	int x;
	FILE *fp=NULL;
	fp=fopen("abc.txt","r+");
	char a[20],b[20];
	float result;
	printf("����һ���������ʽ:\n");
	printf("�Ƿ�ʹ���ļ�����(����1ѡ��ʹ���ļ�����)");
	scanf("%d",&x);
	while(getchar()!='\n');
	if(x==1)
	{
		fgets(a,20,fp);
    }
	else 
	gets(a);
	translateexpress(a,b);
	result=computeexpress(b);
	printf("������: %f \n",result);
} 

void pushstack(stack *s,float x)
{
	if(s->top > 20 )
	printf("ջ��\n");
	else
	{
		s->data[s->top]=x;
		s->top++;
		printf("push stack  :%1.1f\n",x);
	}
}
float popstack(stack *s)
{
	float x;
	if(s->top<=0)
	printf("ջ��\n");
	else
	{
		s->top--;
		x=s->data[s->top];
		printf("pop stack   :%1.1f\n",x);
	}
	return x;
}
void translateexpress(char in[],char post[])
{
	int i=0,j=0,k=0;
	char stack1[20];
	char ch;//��ʱ���� 
	while(in[i]!='\0')
	{
		ch=in[i];
		switch(ch)
		{
			case '(':
				stack1[k++]='(';
				printf("push stack: %c\n",ch);
				break;
			case ')':
				while(stack1[k]!='(')
				{
					post[j++]=stack1[--k];
					printf("pop stack: %c\n",stack1[k]);
				}
				
		    case '+':
		    case '-':
		    	//������ȼ�
		    	if(ch=='-'&&(i==0||in[i]=='('))
				{
					post[j++]=ch;
					post[j++]=' ';
					break;
				}
				else
				{
					while(k!=0 && stack1[k] != '(')   //��������'('������һֱ��ջ 
				    {
					    post[j++]=stack1[--k];
					    printf("pop stack: %c\n",stack1[k]);
				    }
				    stack1[k++] = ch;
				    printf("push stack: %c\n",ch);
				    break; 
				}
			case '*':
			case '/':
			    //��ջ�е� * / ���ȼ���
				while(k!=0 && (stack1[k]=='/'||stack1[k]=='*'))   //���� * / ʱ��ջ 
				{
					post[j++]=stack1[--k];
					printf("pop stack: %c\n",stack1[k]);
				 }
				 stack1[k++]=ch;
				 printf("push stack: %c\n",ch);
				 break;
			case ' ':
			     break;
			default:
			    while(ch>='0' && ch<='9')
				{
					post[j++]=ch;
					
					i++;
					ch = in[i];
				 }
				 i--;
				 post[j++]=' ';
	    }
	    i++;
    }
    while(k!=0)
	{
		post[j++]=stack1[--k];
		printf("pop stack: %c\n",stack1[k]);
	 }
	 post[j++]='\0';
     printf("��׺���ʽ\n");
	 printf("%s\n",post);
}
float computeexpress(char a[])
{
	int i=0,value,flag=0;
	stack s;
	s.top=0;
	float x1,x2;
	float result; 
    while(a[i]!='\0')
    {
    	if(a[i]>='0' && a[i]<='9')  //�������־���ջ 
    	{
    		
    		value=0;    
			while(a[i]!=' ')   // �ַ���ת���� 
    		{
    			value = 10*value+a[i]-'0';
    			i++;
			}
			if(flag==1)
			{
				value=-value; 
				flag=0;
			}
			pushstack(&s,value); 
		}
		else
		{
			switch(a[i])
			{
				case '+':
					x1=popstack(&s);
					x2=popstack(&s);
					result=x1+x2;
					pushstack(&s,result);
					break;
				case '-':
					if(a[i+1]==' ')
					{
						flag=1;    //��Ǹ��� 
						break;
					}
					else
					{
						x1=popstack(&s);
					    x2=popstack(&s);
					    result=x2-x1;        //x2-x1
					    pushstack(&s,result);
					    break;
					}
				case '*':
					x1=popstack(&s);
					x2=popstack(&s);
					result=x1*x2;
					pushstack(&s,result);
					break;
				case '/':
					x1=popstack(&s);
					x2=popstack(&s);
					result=x2/x1;
					pushstack(&s,result);
					break;
			}
			i++;
		 } 
	}
	if(s.top==1)
	{
		result=popstack(&s);
		return result;
	}
	else
	printf("���ʽ����\n");
}
