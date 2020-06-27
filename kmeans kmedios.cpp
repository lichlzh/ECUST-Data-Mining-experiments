#include<bits/stdc++.h>
using namespace std;
void readIn(char*FILE,vector<vector<float> >&dat){
    freopen(FILE,"r",stdin);
    char buf[1<<16];
    while(gets(buf+1)){
        int len=strlen(buf+1);
        vector<float>tmp;
        for(int i=1;i<=len;i++)
            if(i==1||(buf[i-1]==' ')){
                float x;
                sscanf(buf+i,"%f",&x);
                tmp.push_back(x);
            }
        dat.push_back(tmp);
    }
}

float getDis(vector<float>&A,vector<float>&B){
    int L=A.size();
    float res=0;
    for(int i=0;i<L;i++)
        res+=(A[i]-B[i])*(A[i]-B[i]);
    return res;
}
vector<int> kmeans(vector<vector<float> >dat,int k){
    int n=dat.size(),m=dat[0].size();
    vector<int>res(n,-1);
    vector<int>cnt(k,0);
    vector<int>perm;
    vector<vector<float> >center;
    for(int i=0;i<n;i++)
        perm.push_back(i);
    srand(time(NULL));
    random_shuffle(perm.begin(),perm.end());
    for(int i=0;i<k;i++){
        center.push_back(dat[perm[i]]);
        res[perm[i]]=i;
        cnt[i]=1;
    }

    for(int i=k;i<n;i++){
        float minDis=1e9;
        int minId;
        for(int j=0;j<k;j++){
            float d=getDis(dat[perm[i]],center[j]);
            if(d<minDis)
                minDis=d,minId=j;
        }
        res[perm[i]]=minId;
        for(int j=0;j<m;j++){
            center[minId][j]=(center[minId][j]*cnt[minId]+dat[perm[i]][j])/(cnt[minId]+1);
            cnt[minId]++;
        }
    }
    return res;
}

float classify(vector<vector<float> >&dat,vector<vector<int> >&cluster,vector<int>&center,int k,int id){
    float minDis=1e9;
    int minId;
    for(int j=0;j<k;j++){
        float d=getDis(dat[id],dat[center[j]]);
        if(d<minDis)
            minDis=d,minId=j;
    }
    cluster[minId].push_back(id);
    return minDis;
}

vector<int> kmedios(vector<vector<float> >dat,int k,int iters){
    int n=dat.size(),m=dat[0].size();
    vector<int>res(n,-1);
    vector<int>perm;
    vector<vector<int> >cluster;
    vector<int>center;
    for(int i=0;i<n;i++)
        perm.push_back(i);
    srand(time(NULL));
    random_shuffle(perm.begin(),perm.end());
    for(int i=0;i<k;i++){
        vector<int>tmp;tmp.push_back(perm[i]);
        cluster.push_back(tmp);
        center.push_back(perm[i]);
    }
    float curLoss=0;
    for(int i=k;i<n;i++)
        curLoss+=classify(dat,cluster,center,k,perm[i]);
    float minLoss=1e9;
    for(int I=0;I<iters;I++){
        bool flag=0;
        for(int i=0;i<k;i++){
            for(int j=k;j<n;j++){
                swap(perm[i],perm[j]);
                vector<vector<int> >newCluster;
                vector<int>newCenter;
                for(int p=0;p<k;p++){
                    vector<int>tmp;tmp.push_back(perm[p]);
                    newCluster.push_back(tmp);
                    newCenter.push_back(perm[p]);
                }
                float newLoss=0;
                for(int p=k;p<n;p++)
                    newLoss+=classify(dat,cluster,center,k,perm[p]);
                if(newLoss<minLoss){
                    minLoss=newLoss;
                    cluster=newCluster;
                    center=newCenter;
                    flag=1;
                }
            }
        }
        if(!flag)
            break;
        printf("iter:%d, loss:%.2f\n",I,minLoss);
    }
    for(int i=0;i<k;i++)
        for(int j=0;j<cluster[i].size();j++)
            res[cluster[i][j]]=i;
    return res;
}

void print(char*FILE,int k,vector<int>res){
    freopen(FILE,"w",stdout);
    vector<int>s[k];
    for(int i=0;i<res.size();i++)
        s[res[i]].push_back(i);
    for(int i=0;i<k;i++){
        printf("class %d, total number:%d:",i,s[i].size());
        for(int j=0;j<s[i].size();j++)
            printf(" %d",s[i][j]);
        printf("\n");
    }
}
int main(){
    vector<vector<float> >dat;
    readIn("data.txt",dat);
    vector<int>res=kmedios(dat,5,20);
    for(int i=0;i<res.size();i++)
        printf("%d ",res[i]);
    printf("\n");
    print("5.txt",5,res);
    return 0;
}
