//中缀转后缀
//1.设置一个栈：（1）如果是操作数，直接输出
//              （2）如果是运算符，比较栈顶运算符和当前运算符的优先级
//                         ①如果高于栈顶运算符，入栈
//                         ②如果低于栈顶运算符，出栈直到当前运算符高于栈顶运算符 
//       保证栈顶运算符总是优先级最高 

//后缀表达式求值 
//1.遇到 数字 就入栈
//2.遇到运算符就用栈顶元素运算，再将结果入栈 

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
	printf("输入一个算术表达式:\n");
	printf("是否使用文件输入(输入1选择使用文件读入)");
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
	printf("计算结果: %f \n",result);
} 

void pushstack(stack *s,float x)
{
	if(s->top > 20 )
	printf("栈满\n");
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
	printf("栈空\n");
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
	char ch;//临时变量 
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
		    	//最低优先级
		    	if(ch=='-'&&(i==0||in[i]=='('))
				{
					post[j++]=ch;
					post[j++]=' ';
					break;
				}
				else
				{
					while(k!=0 && stack1[k] != '(')   //除非遇到'('；否则一直出栈 
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
			    //比栈中的 * / 优先级低
				while(k!=0 && (stack1[k]=='/'||stack1[k]=='*'))   //遇到 * / 时出栈 
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
     printf("后缀表达式\n");
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
    	if(a[i]>='0' && a[i]<='9')  //遇到数字就入栈 
    	{
    		
    		value=0;    
			while(a[i]!=' ')   // 字符串转整形 
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
						flag=1;    //标记负数 
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
	printf("表达式错误\n");
}
