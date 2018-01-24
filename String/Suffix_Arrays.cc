/**********************************************
后缀数组
SA[i] = j  : 表示为按照从小到大排名为i的后缀 是以j(下标)开头的后缀
rank[i] = j: 表示为按照从小到大排名 以i为下标开始的后缀 排名为j
Heigth[i]  : 表示Suffix[SA[i]]和Suffix[SA[i - 1]]的最长公共前缀，也就是排名相邻的两个后缀的最长公共前缀
RANK表示你排第几 SA表示排第几的是谁 (记住这个就行)
**********************************************/
const int MAXN=400010;
//以下为倍增算法求后缀数组
int wa[MAXN],wb[MAXN],wv[MAXN],Ws[MAXN];
int cmp(int *r,int a,int b,int l) {
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
/**< 传入参数：str,sa,len+1,ASCII_MAX+1 */
void da(const int r[],int sa[],int n,int m) {
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++) Ws[i]=0;
    for(i=0; i<n; i++) Ws[x[i]=r[i]]++;//以字符的ascii码为下标
    for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
    for(i=n-1; i>=0; i--) sa[--Ws[x[i]]]=i;
    /*cout<<"SA"<<endl;;
    for(int i=0;i<n+1;i++)cout<<sa[i]<<' ';*/
    for(j=1,p=1; p<n; j*=2,m=p) {
        for(p=0,i=n-j; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0; i<n; i++) wv[i]=x[y[i]];
        for(i=0; i<m; i++) Ws[i]=0;
        for(i=0; i<n; i++) Ws[wv[i]]++;
        for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
        for(i=n-1; i>=0; i--) sa[--Ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
int sa[MAXN],Rank[MAXN],height[MAXN];
//求height数组
/**< str,sa,len */
void calheight(const char *r,int *sa,int n) {
    int i,j,k=0;
    for(i=1; i<=n; i++) Rank[sa[i]]=i;
    for(i=0; i<n; height[Rank[i++]]=k)
        for(k?k--:0,j=sa[Rank[i]-1]; r[i+k]==r[j+k]; k++);
    // Unified  不要乱用，出来检查为了方便的时候 否则容易RE，WA
//    for(int i=n; i>=1; --i) ++sa[i],Rank[i]=Rank[i-1];

}

//求lcp(suffixal(i),suffixal(j))

int mm[MAXN],dp[MAXN][20];
void initrmq(int n,int b[]) {
    mm[0]=-1;
    for(int i=1; i<=n; i++) {
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
        dp[i][0]=b[i];
    }
    for(int j=1; j<=mm[n]; j++)
        for(int i=1; i+(1<<j)-1<=n; i++)
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}

int lcp(int x,int y) {
    x=Rank[x],y=Rank[y];
    if(x>y) swap(x,y); x++;
    int k=mm[y-x+1];
    return min(dp[x][k],dp[y-(1<<k)+1][k]);
}

char s[N];
int a[N];

int main(){
    scanf("%s",s);
    int ls = strlen(s);
    for(int i=0;i<ls;i++) a[i]=s[i]-'a'+1; a[ls]=0;

    da(a,sa,ls+1,30);
    calheight(a,sa,ls);
    initrmq(ls+1,height);
    return 0;
}