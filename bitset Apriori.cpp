#include<bits/stdc++.h>
using namespace std;
const int maxn=1000;
void readIn(const char*FILE,vector<bitset<maxn> >&S){
	freopen(FILE,"r",stdin);
	S.clear();
	static char str[1024];
	while(gets(str+1)){
		bitset<maxn>s;
		int len=strlen(str+1),tmp;
		for(int i=0;i<len;i++){
            if((!i||str[i]==' ')&&isdigit(str[i+1])){
				sscanf(str+i+1,"%d",&tmp);
				s[tmp]=1;
			}
		}
		S.push_back(s);
	}
}

void Apriori(const char*FILE,vector<bitset<maxn> >s,int supp){
	freopen(FILE,"w",stdout);
	vector<bitset<maxn> >C,L;
	vector<int>cnt;
	C.clear(),cnt.clear();
	for(int i=0;i<maxn;i++){
		bitset<maxn>tmp;
		tmp[i]=1;
		C.push_back(tmp);
		cnt.push_back(0);
	}
	/*for(int i=0;i<1000;i++)
		printf("%d ",cnt[i]);
	puts("");*/
	unordered_map<bitset<maxn>,int>F;
	for(int T=1;;T++){
		for(int i=0;i<C.size();i++)
			for(int j=0;j<s.size();j++)
				if((C[i]&s[j])==C[i])
					cnt[i]++;
		L.clear();
		for(int i=0;i<C.size();i++)
			if(supp<=cnt[i])
				L.push_back(C[i]);
		if(!L.size())break;
		printf("L%d %d:\n",T,L.size());
		for(int i=0;i<L.size();i++){
			for(int j=0;j<maxn;j++)
				if(L[i][j])
					printf("%d ",j);
			printf("\n");
		}
		F.clear();
		for(int i=0;i<L.size();i++)
			for(int j=i+1;j<L.size();j++){
				bitset<maxn>tmp=(L[i]|L[j]);
				if(tmp.count()==T+1)
					F[tmp]++;
			}
		C.clear(),cnt.clear();
		for(unordered_map<bitset<maxn>,int>::iterator it=F.begin();it!=F.end();it++)
			if(it->second==(T+1)*T/2){
				C.push_back(it->first);
				cnt.push_back(0);
			}
	}
}
int main(){
	vector<bitset<maxn> >S;
	readIn("T1014D10K.dat",S);
	Apriori("T1014D10K_60.txt",S,60);
	Apriori("T1014D10K_80.txt",S,80);
	Apriori("T1014D10K_100.txt",S,100);
	return 0;
}

