#include<bits/stdc++.h>
using namespace std;
void readIn(const char*FILE,vector<set<int> >&S){
	freopen(FILE,"r",stdin);
	set<int>s;
	S.clear();
	static char str[1024];
	while(gets(str+1)){
		s.clear();
		int len=strlen(str+1),tmp;
		for(int i=0;i<len;i++){
            if((!i||str[i]==' ')&&isdigit(str[i+1])){
				sscanf(str+i+1,"%d",&tmp);
				s.insert(tmp);
			}
		}
		S.push_back(s);
	}
}

void Apriori(const char*FILE,vector<set<int> >s,int supp){
	freopen(FILE,"w",stdout);
	vector<set<int> >C,L;
	vector<int>cnt;
	C.clear(),cnt.clear();
	for(int i=0;i<1000;i++){
		set<int>tmp;
		tmp.clear(),tmp.insert(i);
		C.push_back(tmp);
		cnt.push_back(0);
	}
	/*for(int i=0;i<1000;i++)
		printf("%d ",cnt[i]);
	puts("");*/
	map<set<int>,int>F;
	for(int T=1;;T++){
		for(int i=0;i<C.size();i++){
			for(int j=0;j<s.size();j++){
				bool flag=1;
				for(set<int>::iterator it=C[i].begin();it!=C[i].end();it++)
					if(s[j].find(*it)==s[j].end()){
						flag=0;
						break;
					}
				if(flag)
					cnt[i]++;
			}
		}
		L.clear();
		for(int i=0;i<C.size();i++)
			if(supp<=cnt[i])
				L.push_back(C[i]);
		if(!L.size())break;
		printf("L%d %d:\n",T,L.size());
		for(int i=0;i<L.size();i++){
			for(set<int>::iterator it=L[i].begin();it!=L[i].end();it++)
				printf("%d ",*it);
			printf("\n");
		}
		F.clear();
		for(int i=0;i<L.size();i++)
			for(int j=i+1;j<L.size();j++){
				set<int>tmp=L[i];
				tmp.insert(L[j].begin(),L[j].end());
				if(tmp.size()==T+1)
					F[tmp]++;
			}
		C.clear(),cnt.clear();
		for(map<set<int>,int>::iterator it=F.begin();it!=F.end();it++)
			if(it->second==(T+1)*T/2){
				C.push_back(it->first);
				cnt.push_back(0);
			}
	}
}
int main(){
	vector<set<int> >S;
	readIn("T1014D1K.dat",S);
	Apriori("T1014D1K_6.txt",S,6);
	Apriori("T1014D1K_8.txt",S,8);
	Apriori("T1014D1K_100.txt",S,10);
	return 0;
}

