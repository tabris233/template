// KMP

char s1[N],s2[N];
int Next[N];//Next[i] 表示从[0~i]中最长公共前缀的长.
void get_next(char *s,int len){
    for(int i=0,j=-1;i<=len;++i,++j){
        Next[i]=j;
        while(j>=0&&s[i]!=s[j]) j = Next[j];
    }
//    for(int i=0;i<=len;i++) printf("%d%c",Next[i],(i==len)?'\n':' ');
}
//在串s上找sz
int KMP (char *s,int len,char *sz,int l){
    int i=0,j=0,cnt=0;
    while(i<len/*&&j<l*/){
        if(s[i]==sz[j])  i++,j++;
        else{
            if(0==j)  i++;
            else      j=Next[j];
        }
        if(j==l) cnt++;
    }

//   return (j==l)?(i-l+1):-1; //找第一次出现的位置
    return cnt; //找出现的个数
}
/*
            for(int j=0,i=0;i<=len;i++,j++){
                ans ^= 1LL*(j)*(j)*(len-k-j)*(i-j) ;
                while(j>=0&&a[i]!=p[j]) j=Next[j];
            }
*/