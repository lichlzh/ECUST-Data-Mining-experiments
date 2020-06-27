#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<iomanip>
using namespace std;
int read(){
    int xx=0,ff=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')ff=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){xx=xx*10+ch-'0';ch=getchar();}
    return xx*ff;
}
long long READ(){
    long long xx=0,ff=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')ff=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){xx=xx*10+ch-'0';ch=getchar();}
    return xx*ff;
}
char one(){
	char ch=getchar();
	while(ch==' '||ch=='\n'||ch=='\r')
		ch=getchar();
	return ch;
}
const int maxn=60;
typedef long long LL;
map<LL,int>mp[maxn],ind;
map<LL,int>::iterator it,pre;
inline LL lowbit(LL x){return x&(-x);}
inline int count(LL x){
	int ret=0;
	for(;x;x-=lowbit(x))
		ret++;
	return ret;
}
void Apriori(LL init[],int N,double conf){
	ind.clear();
	for(int i=0;i<maxn;i++)
		ind[1LL<<i]=i;
	
	static vector<LL>tmp;
	int siz;
	mp[0].clear(),mp[1].clear();
	for(int i=0;i<N;i++){
		for(int j=init[i];j;j=(j-1)&init[i])
			mp[0][j]++;
		for(int j=init[i];j;j-=lowbit(j))
			mp[1][lowbit(j)]++;
	}
	for(int i=1;!mp[i].empty();i++){
		tmp.clear();
		printf("C%d:\n",i);
		for(it=mp[i].begin();it!=mp[i].end();it++){
			printf("%I64d %d;",it->first,it->second);
			if(it->second>=N*conf)
				tmp.push_back(it->first);
		}
		printf("\nL%d:\n",i);
		siz=tmp.size();
		for(int j=0;j<siz;j++)
			printf("%I64d ",tmp[j]);
		printf("\n");
		mp[i+1].clear();
		for(int j=0;j<siz;j++)
			for(int k=j+1;k<siz;k++)
				if(count(tmp[j]|tmp[k])==i+1)
					mp[i+1][tmp[j]|tmp[k]]++;
		for(it=mp[i+1].begin();it!=mp[i+1].end();)
			if(it->second==(i+1)*i/2){
				it->second=mp[0][it->first];
				it++;
			}
			else{
				pre=it++;
				mp[i+1].erase(pre);
			}
	}
}
int main(){
	LL a[]={13,22,23,18};
	Apriori(a,4,0.5);
	return 0;
}
