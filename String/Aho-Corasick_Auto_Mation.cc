struct  Aho_Corasick_automaton{
    int ch[N][130],val[N],fail[N],cnt,root;
    int newnode(){
        memset(ch[cnt],-1,sizeof(ch[cnt]));
        fail[cnt]=val[cnt++]=-1;
        return cnt-1;
    }
    void init(){
        cnt = 0;
        root = newnode();
    }
    void insert(char *s,int id){
        int now = root;
        for(int i=0;s[i];i++){
            if( ch[now][s[i]] == -1)
                ch[now][s[i]] = newnode();
            now=ch[now][s[i]];
        }
        val[now]=id;
    }
    void build(){
        fail[root]=root;
        queue<int>q;
        for(int i=0;i<130;i++){
            if(-1==ch[root][i])ch[root][i]=root;
            else {
                fail[ch[root][i]]=root;
                q.push(ch[root][i]);
            }
        }
        for(int now;!q.empty();){
            now=q.front();q.pop();
            for(int i=0;i<130;i++){
                if(-1==ch[now][i]) ch[now][i]=ch[fail[now]][i];
                else {
                fail[ch[now][i]]=ch[fail[now]][i];
                q.push(ch[now][i]);
                }
            }
        }
    }
    int vis[1000];
    int Get(int x){
        int flag = 0;
        for(;x!=root;x=fail[x])
            if(val[x]!=-1){
                vis[val[x]]=1;
                flag = 1;
            }
        return flag;
    }
    int match(char *s){
        int now = root,flag = 0;
        memset(vis,0,sizeof(vis));
        for(int i=0;s[i];i++){
            now = ch[now][s[i]];
            flag |= Get(now);
        }
        return flag;
    }
}ac;
int main(){
    ac.init();           // 初始化自动机
    for(;;)ac.insert(s); // 插入子串s
    ac.build();          // 构造fail
    ac.match(s);         // 对串s进行匹配
}