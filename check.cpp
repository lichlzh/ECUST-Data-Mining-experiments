#include<bits/stdc++.h>
using namespace std;
int check(const char*FILE,set<int>&S){
	int ret=0;
	freopen(FILE,"r",stdin);
	set<int>s;
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
		bool occ=1;
		for(set<int>::iterator it=S.begin();it!=S.end();it++)
			if(s.find(*it)==s.end()){
				occ=0;
				break;
			}
		ret+=occ;
	}
	return ret;
}
int main(){
	set<int>s;
	s.clear();
	s.insert(27);s.insert(58);s.insert(354);s.insert(357);s.insert(480);s.insert(752);
	int ans=check("T1014D1K.dat",s);
	printf("%d\n",ans);
	return 0;
}


