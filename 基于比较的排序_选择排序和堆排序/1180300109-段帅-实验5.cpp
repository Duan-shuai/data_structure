#include<stdio.h>
#include<stdlib.h> 
#include<time.h>

void selection_sort(int a[],int n);
void createheap(int a[],int n);
void heapsort(int a[],int n);
void display(int a[],int n);
void swap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

int a[1000005];
int b[1000005];
int c[1000005];

int main()
{
	int i;
	int n;
	int x1,x2; 
	clock_t start,stop;
	double duration;
	for(i = 0 ; i < 1000000 ; i++)
	{
		a[i] = i;
		b[i] = i;
		c[i] = 1000000-i; 
	}
	srand((unsigned)time(NULL));
	for(i = 0 ; i < 1000000 ; i++)
	{
		x1 = rand()%1000000;
        x2 = rand()%1000000;
        swap(&b[x1],&b[x2]);  //随机交换两个数 
	}
	n = 1000000;
	printf("10000~100000规模 : 步长10000\n"); 
	printf("1.正序\n");
	printf("1.1选择排序\n");
	for(n = 10000 ; n <= 100000 ; n+=10000)
	{
		start=clock();
	    selection_sort(a,n);
	    stop=clock();
	    duration = ((double)(stop-start))/CLK_TCK;
	    printf("%lf    ",duration);
	}
	printf("1.2堆排序\n");
	for(n = 10000 ; n <= 100000 ; n+=10000)
	{
		for(i = 0 ; i < 1000000 ; i++)
	    {
		    c[i] = 1000000-i;
	    }
		start=clock();
	    heapsort(c,n);
	    stop=clock();
	    duration = ((double)(stop-start))/CLK_TCK;
	    printf("%lf    ",duration);
	} 
	printf("2.乱序\n");
	printf("2.1选择排序\n");
	for(n = 10000 ; n <= 100000 ; n+=10000)
	{
		for(i = 0 ; i < 1000000 ; i++)
	    {
		    b[i] = i;
	    }
	    srand((unsigned)time(NULL));
	    for(i = 0 ; i < 1000000 ; i++)
	    {
		    x1 = rand()%1000000;
            x2 = rand()%1000000;
            swap(&b[x1],&b[x2]);  //随机交换两个数 
	    }
		start=clock();
	    selection_sort(b,n);
	    stop=clock();
	    duration = ((double)(stop-start))/CLK_TCK;
	    printf("%lf    ",duration);
	}
	printf("2.2堆排序\n");
	for(n = 10000 ; n <= 100000 ; n+=10000)
	{
		for(i = 0 ; i < 1000000 ; i++)
	    {
		    b[i] = i;
	    }
	    srand((unsigned)time(NULL));
	    for(i = 0 ; i < 1000000 ; i++)
	    {
		    x1 = rand()%1000000;
            x2 = rand()%1000000;
            swap(&b[x1],&b[x2]);  //随机交换两个数 
	    }
		start=clock();
	    heapsort(b,n);
	    stop=clock();
	    duration = ((double)(stop-start))/CLK_TCK;
	    printf("%lf    ",duration);
	} 
	printf("3.倒序\n");
	printf("3.1选择排序\n");
	for(n = 10000 ; n <= 100000 ; n+=10000)
	{
		for(i = 0 ; i < 1000000 ; i++)
	    {
		    c[i] = 1000000-i;
	    }
		start=clock();
	    selection_sort(c,n);
	    stop=clock();
	    duration = ((double)(stop-start))/CLK_TCK;
	    printf("%lf    ",duration);
	}
	printf("3.2堆排序\n");
	for(n = 10000 ; n <= 100000 ; n+=10000)
	{
		start=clock();
	    heapsort(a,n);
	    stop=clock();
	    duration = ((double)(stop-start))/CLK_TCK;
	    printf("%lf    ",duration);
	} 
	return 0;
}
void selection_sort(int a[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<=n-1;j++)
		{
			if(a[j]<a[i])
			{
				a[j]=a[i]^a[j];
				a[i]=a[i]^a[j];
				a[j]=a[i]^a[j];
			}
		}
	}
}
void createheap(int a[],int n)
{
	int i,t,m;
	for(i=n/2-1;i>=0;i--)
	{
		if(2*i+2>n-1)
		{
			if(a[i]>a[2*i+1])
			{
				t=a[i];
				a[i]=a[2*i+1];
				a[2*i+1]=t;
			}
		}
		else
		{
			if(a[i]>a[2*i+1]||a[i]>a[2*i+2])
		    {
			    if(a[2*i+1]<a[2*i+2])
			    {
				    t=a[i];
				    a[i]=a[2*i+1];
				    a[2*i+1]=t;
			    }
			    else
			    {
				    t=a[i];
				    a[i]=a[2*i+2];
				    a[2*i+2]=t;
		        }
            }
		}
	}
}
void heapsort(int a[],int n)
{
	int t; 
	while(n>=1)
	{
	createheap(a,n);
    t=a[0];
    a[0]=a[n-1];
    a[n-1]=t;
    n--;
	}
	return ;
 }
