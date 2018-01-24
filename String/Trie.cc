/******************************
字典树 trie
指针实现
双数组
可持久化
******************************/

// point 
const int N = 1010101;
const int Max = 26;

typedef struct node{
    struct node *next[Max];
    int num;
}Node;

//创建一个新节点
Node *createNew(){
    Node *p=new Node;
    for(int i=0;i<Max;i++) p->next[i]=NULL;
    p->num=0;
    return p;
}
Node *head;

//插入一个字符串
void Insert_str(char str[]){
    int len=strlen(str);
  //  printf("len = %d--  ",len);
    Node *t,*p=head;
    for(int i=0;i<len;i++){
        int c=str[i]-'a';
        if( p->next[c] == NULL ){
            //lalal
            t=createNew();
            p->next[c]=t;
        }
        p=p->next[c];
        p->num++;
       // cout<<p->num<<"-"<<str[i]<<" ";
    }
}

int Search_str(char str[]){
    Node *p=head;
    int len=strlen(str);

    int counts=0;
    for(int i=0;i<len;i++){
        int c=str[i]-'a';
        if(p->next[c]==NULL){
        //  cout<<"不存在字符串"<<endl;
            counts=0;
            return 0;
        }
        else{
            p=p->next[c];
            counts=p->num;
            //printf("%d ",p->num);
        }
    }
    return counts;
}

//Double Arrays Trie-DAT
struct TRIE{
    int ch[N][30],cnt;

    int newnode(){
        ++cnt;
        memset(ch[cnt],0,sizeof(ch[cnt]));
        return cnt;
    }

    void init(){
        cnt = 0;
        memset(ch[cnt],0,sizeof(ch[cnt]));
    }

    void insert(char *s){
        int now = 0;
        for(int i=0;s[i];i++){
            if(!ch[now][s[i]-'a'])
                ch[now][s[i]-'a']=newnode();
            now=ch[now][s[i]-'a'];
        }
    }

    int match(char *s){
        int now = 0,ans = 0;
        for(int i=0;s[i];i++){
            if(!ch[now][s[i]-'a']) return i;
            now=ch[now][s[i]-'a'];
            ans++;
        }
        return ans;
    }
}trie;


//可持久化01字典树

int trie[N*20][2],sz[N*20],rt[N],cnt;
//将x插入到trie ,i为位数 (下同)
void update(int pre,int i,int x){
    int now = ++ cnt;
    if(0==i){
        trie [now][0]=trie [now][1]=0;
        sz[now]=sz[pre]+1;
        return ;
    }
    int bt = (x>>(i-1))&1;
    trie[now][1-bt]=trie[pre][1-bt];
    trie[now][bt]  =update(trie[pre][bt],i-1,x);
    sz[now]=sz[trie[now][0]]+sz[trie[now][1]];
    return now;
}
//查询[l,r]区间与x异或结果最大的值, ss=rt[l-1],tt=rt[r];
int query(int ss,int tt,int i,int x){
    if(0==i) return 0;
    int bt = (x>>(i-1))&1;
    if(sz[trie[tt][1-bt]]-sz[trie[ss][1-bt]])
        return (1<<(i-1))+query(trie[ss][1-bt],trie[tt][1-bt],i-1,x);
    else 
        return query(trie[ss][bt],trie[tt][bt],i-1,x);
}
int main(){
    //初始化
    memset(sz,0,sizeof(sz));
    trie[0][0]=trie[0][1]=tr[0]=0;
    rt[0]=update(rt[0],25,0);

    
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);
        rt[i]=update(rt[i-1],25,x);
    }
}