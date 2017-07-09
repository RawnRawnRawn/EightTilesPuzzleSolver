#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
struct node
{
    int data[3][3];
    int level;
    int pro;
    struct node *next;
    struct node *parent;
};
typedef struct node * list;
struct c//it is used in calculating the priority value of a node for comparative checking
{
    int row;
    int col;
};
struct c check[9];
int flag;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void assign()
{
    int goal[3][3]={{1,2,3},{4,5,6},{7,8,0}};
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
    {
        check[goal[i][j]].row=i;
        check[goal[i][j]].col=j;

    }
}
int getinversion(int a[])
{
    int i,j,k;
    int inv=0;
    int goal[9]={1,2,3,8,0,4,7,6,5};
    for(i=0;i<8;i++)
        for(j=i+1;j<9;j++)
    {
        if(a[i]&&a[j]&&a[i]>a[j])
        {
            inv++;

        }
    }
    return inv;
}
int solvable(int a[3][3])
{
    int inv=getinversion((int *)a);
    if(inv%2==0)
        return 1;
    else
        return 0;
}
void priority(list t)
{
    int i,j;
    t->pro=t->level;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
    {
        t->pro=t->pro+abs(check[t->data[i][j]].row-i)+abs(check[t->data[i][j]].col-j);
    }
}
void display(int x[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {for(j=0;j<3;j++)
        {
            if(x[i][j]==0)
                printf("  ");
            else
                printf("%d ",x[i][j]);
        }
        if(i!=2)
        printf("\n");
    }
    printf("\n\n");

}
void result(list t)
{
    if(t!=NULL)
    {
        result(t->parent);
        //printf("\n");
        //system("clear");
        display(t->data);
        delay(1000);

    }
}
int compare(int x[3][3],int y[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(x[i][j]!=y[i][j])
                break;
        }
        if(j!=3)
            break;
    }
    if(i==3&&j==3)
        return 1;
    else
        return 0;
}
int goaltest(list t)
{
    int i,j;
    int test[3][3]={{1,2,3},{4,5,6},{7,8,0}};

        if(compare(test,t->data))
            return 1;
        else
            return 0;
}
list insert(list head,list parent,int plev,int temp[3][3])
{
    list t=head;
    list tnode;
    int i,j;
    if(t!=NULL)
    {
        t->next=insert(t->next,parent,plev,temp);
    }
    else
    {
       tnode=malloc(sizeof(struct node));
       for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            tnode->data[i][j]=temp[i][j];
       tnode->level=plev+1;
       tnode->parent=parent;
       tnode->next=NULL;
       priority(tnode);
       t=tnode;
    }
    return t;
}
list movegen(list t)
{

    list head,p,q;
    int i,j,temp[3][3],x;
    head=NULL;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            temp[i][j]=t->data[i][j];
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(temp[i][j]==0)
                break;
        }
        if(j!=3)
            break;
    }
    if((i-1)>=0)
    {
        temp[i][j]=temp[i-1][j];
        temp[i-1][j]=0;
        head=insert(head,t,t->level,temp);
        temp[i-1][j]=temp[i][j];
        temp[i][j]=0;
    }
    if((i+1)<3)
    {
        temp[i][j]=temp[i+1][j];
        temp[i+1][j]=0;
        head=insert(head,t,t->level,temp);
        temp[i+1][j]=temp[i][j];
        temp[i][j]=0;
    }
    if((j-1)>=0)
    {
        temp[i][j]=temp[i][j-1];
        temp[i][j-1]=0;
        head=insert(head,t,t->level,temp);
        temp[i][j-1]=temp[i][j];
        temp[i][j]=0;
    }
    if((j+1)<3)
    {
        temp[i][j]=temp[i][j+1];
        temp[i][j+1]=0;
        head=insert(head,t,t->level,temp);
        temp[i][j+1]=temp[i][j];
        temp[i][j]=0;
    }
    t=head;
    return t;
}
list proenqueue(list head,list temp)
{
    list t=head;
    if(t!=NULL)
    {
        if(flag==0)
        {
        if(t->pro>temp->pro)
        {
            temp->next=t;
            return temp;
        }
        else if(t->pro==temp->pro)
        {
            if(t->level<=temp->level)
            {
                temp->next=t;
                return temp;
            }
            else
                flag=1;
        }
        else
            flag=1;
    }
    if(t->next!=NULL)
    {
        if(t->next->pro<temp->pro)
        {
        t->next=proenqueue(t->next,temp);
    }
    else if(t->next->pro==temp->pro)
    {
        if(t->next->level<=temp->level)
        {
            temp->next=t->next;
            t->next=temp;
        }
        else
            t->next=proenqueue(t->next,temp);
    }
    else
    {

        temp->next=t->next;
        t->next=temp;
    }
    }
    else
    {
        if(t->pro<temp->pro)
        {
            t->next=temp;
        }
        else if(t->pro==temp->pro)
        {
            if(t->level<temp->level)
            {
                temp->next=t;
            return temp;
            }
            else
            {
                t->next=temp;
            }
        }
        else
        {
            temp->next=t;
            return temp;
        }
    }
    }
    else
        {
            return temp;
        }
    return t;

}
list dequeue(list t)
{
    return t->next;
}
int main()
{
    int i,j,k;
    list open,closed,t,temp,p,q;//p is for temporaraly handling closed,t is for holding open,temp is return movgen,q for temporarily holding movgen
    int m[3][3];
    closed=open=NULL;
    assign();//used in calculating the hash value

   // printf("\ninput");
    q:for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        scanf("%d",&m[i][j]);
    if(solvable(m))
    {open=insert(open,NULL,0,m);
    while(open!=NULL)
    {
    	if(!goaltest(open))
    	{

        temp=movegen(open);
    	t=open;
    	//display(t);
    	//printf("\n");
    	open=dequeue(open);
    	t->next=NULL;
    	if(closed==NULL)
    	{
    		closed=t;
    	}
    	else
    	{
    		p=closed;
    		while(p->next!=NULL)
    			p=p->next;
    		p->next=t;
    	}
    	while(temp!=NULL)
    	{
    		q=temp;
    		temp=dequeue(temp);
    		q->next=NULL;
    		t=open;
    		while(t!=NULL)
    		{
    			if(compare(t->data,q->data))
    				break;
    			t=t->next;
    		}
    		if(t==NULL)
    		{
    			p=closed;
    			while(p!=NULL)
    			{
    				if(compare(p->data,q->data))
    					break;
    				p=p->next;
    			}
    			if(p==NULL)
    			{
    				if(solvable(q->data))
    				{flag=0;
    				open=proenqueue(open,q);}
    			}
    		}
    	}

    	}
    	else
    	{
    		result(open);
    		//system("pause");
    		break;
    	}


    }
    }
    else
    {
        printf("\nnot solvable ");
        //system("pause");
        //system("clear");
        goto q;
    }

}
