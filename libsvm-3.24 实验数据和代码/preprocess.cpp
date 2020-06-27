#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
void preprocess(char* data_name,char* label_name,char* output){
	freopen(label_name,"r",stdin);
	vector<int>label;label.clear();
	int tmp;
	while(scanf("%d",&tmp)!=EOF)
		label.push_back(tmp);
	int n=label.size();
	static char buf[1<<16];
	freopen(data_name,"r",stdin);
	freopen(output,"w",stdout);
	for(int i=0;i<n;i++){
		gets(buf);
		int len=strlen(buf),cnt=0;
		if(label[i])printf("+1 ");
		else printf("-1 ");
		for(int j=0;j<len;j++){
			if(buf[j]!=' '){
				printf("%d:",++cnt);
				int k=j;
				while(k<len&&buf[k]!=' '){
					printf("%c",buf[k]);
					k++;
				}
				printf(" ");
				j=k-1;
			}
		}
		printf("\n");
	}
}
int main(){
	char test_data_name[]="test_sample.txt";
	char test_label_name[]="test_sample_label.txt";
	char test_output[]="test_sample_data.txt";
	preprocess(test_data_name,test_label_name,test_output);
	
	char train_data_name[]="train_sample.txt";
	char train_label_name[]="train_sample_label.txt";
	char train_output[]="train_sample_data.txt";
	preprocess(train_data_name,train_label_name,train_output);
	return 0;
}
