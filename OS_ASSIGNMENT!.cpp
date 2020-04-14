#include <bits/stdc++.h>
using namespace std;
int n;
int bursttime[20],arrivaltime[20],priority[20];
int processid[20];
int turnaroundtime[20],waitingtime[20],flag[20]={0},exec[20];
int wait,turn;
int a[20];
int display()
{
  	 cout<<"\nprocess_id   \tBurst Time\t   Arrival time\t  \tWaiting Time\tTurnaround Time";
	int i=0;
	for(i=0;i<n;i++)
	{
	 cout<<"\n"<<processid[i]<<"\t\t  "<<bursttime[i]<<"\t\t    "<<arrivaltime[i]<<"\t\t\t     "<<waitingtime[i]<<"\t\t\t"<<turnaroundtime[i];
	}
	
	cout<<"\nAverage Waiting Time= "<<wait*1.0/n; 
  cout<<"\nAvg Turnaround Time = "<<turn*1.0/n; 
}

int idel(int check[],int i)
{
	int j=0;
	for(j=0;j<i;j++)
	{
		if(exec[check[j]]==0)
			break;
	}
	return j;
}
void prioritysort()		
{
	int i=0,j=0,k=n-1,max,temp=-1;
	while(j<n)
	{
		max=-1;
		for(i=0;i<n;i++)
		{
			if(max<=priority[i] && flag[i]==0)
			{
				max=priority[i];
				a[k]=i;
				temp=i;
			}
		}
		flag[temp]=1;
		j++;
		k--;
	}
}
int isin(int c,int b)			
{
	int  i;
	i=-1;
	int j;
	if(b!=-1)
	{
	for(j=0;j<n;j++)
	{
		if(arrivaltime[j]==arrivaltime[b])
		{
			continue;
		}
		else
		{if(arrivaltime[j]==c)
		{
			return j;
		}
		}
		
	}
}
	else
	{
		for(j=0;j<n;j++)
	{
		if(arrivaltime[j]==c)
		{
			return j;
		
		}
	}
	
	}
	return i;
}
int min(int time)    
{
	int i,j=-1;
	for(i=0;i<n;i++)
	{
		if(arrivaltime[i]==time && flag[i] ==0)
		{
			j=i;
			break;
		}
	}
	if(j!=-1)
	{
		flag[j]=1;
	}
	return j;

}
int main()
{
	int i=0,j,temp,temp1;
	cout<<"enter no of processes:";
	cin>>n;
	int rt[n];
	int queue2[n];
	int q2size=0;
	for(i=0;i<n;i++)
	{
		processid[i]=i;
	}
	for(i=0;i<n;i++)
	{
		cout<<"enter burst time of process "<<i<<" :";
		cin>>bursttime[i];
		rt[i]=bursttime[i];
		cout<<"enter arrival time of process "<<i<<" :";
		cin>>arrivaltime[i];	
		cout<<"enter priority of process "<<i<<" :";
		cin>>priority[i];	
	}
	int timeline=0;
	int remain = n;
	int check[10];
	int k=0;
	prioritysort();
	int index;

	for(i=0;i<n;i++)
		flag[i]=0;
	i=0;
	while(remain!=0)
	{
		while((k = min(timeline))!=-1)
		{
			check[i]=k;
			i++;
		}
		if(i==0 || idel(check,i)==i)
		{
			timeline++;
			continue;
		}

		int index= INT_MAX;
	for(j=0;j<i;j++)			
		{
			if(exec[check[j]]!=1)
				{
			for(k=0;k<n;k++)
			{
				if(check[j]==a[k])
			{
				
					
						if(k<index)			
						{
							index=k;		
							break;
						}
					}
				}
			
			}
		}
		if(index==INT_MAX)
			continue;
		else{
			temp1=a[index];	
		index=temp1;
		temp=rt[index];
		}
	
		for(j=0;j<=temp&&(isin(timeline,index))==-1&& rt[index]>0;j++)   
		{
			rt[index]--;
			timeline++;
		}
		if(rt[index]>0)
		{
				while((k = min(timeline))!=-1)
				{
					check[i]=k;
					i++;
					while(priority[k]>priority[index]&&isin(timeline,k)==-1&&rt[index]!=0)
					{	rt[index]--;
						timeline++;
						if(isin(timeline,-1)!=-1)
							break;
					}
				}
			
				
			if(priority[isin(timeline,-1)]<priority[index]&&isin(timeline,-1)!=-1)	
			{

				queue2[q2size]=index;
				q2size++;
				remain--;
				exec[index]=1;
			}
		}
		if(rt[index]==0)
		{
			waitingtime[index]=timeline-arrivaltime[index]-bursttime[index];   
			wait=wait+waitingtime[index];
			turnaroundtime[index]=timeline-arrivaltime[index];
			turn=turn+turnaroundtime[index];
			exec[index]=1;
			remain--;
		}	
		
	}
	int timeq=2;
	remain = q2size;
	i=0;
	int ch[10]={0};
	while(remain!=0)
	{
		 if(rt[queue2[i]]<=timeq && rt[queue2[i]]>0) 
    { 
      timeline+=rt[queue2[i]]; 
      rt[queue2[i]]=0;  
    } 
    else if(rt[queue2[i]]>0)
    { 
      rt[queue2[i]]-=timeq; 
      timeline+=timeq; 
    } 
    if(rt[queue2[i]]==0&&ch[queue2[i]]==0) 
    { 							
      remain--;  
     	waitingtime[queue2[i]]+=timeline-arrivaltime[queue2[i]]-bursttime[queue2[i]];   
		wait=wait+waitingtime[queue2[i]];
		turnaroundtime[queue2[i]]+=timeline-arrivaltime[queue2[i]];
		turn=turn+turnaroundtime[queue2[i]];
		ch[queue2[i]]=1; 
    } 
    if(i==q2size-1)
      i=0;  
    else 			
      i++; 
	}
	display();
	
}

