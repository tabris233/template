/***
Manacher 是一个能在O(n)的复杂度内解决字符串中最长回文子串的问题

str  原字符串
a    进行Manacher算法的为减轻编码难度改进的字符串
p[i] 以a[i]为中心的回文串的半径(含a[i])
id   最长回文子串的中心位置
mx   id+p[id] 最长回文子串的左外边界。

算法核心的部分
if(mx > i) p[i] = (p[(id<<1)-i]<(mx-i))?p[(id<<1)-1]:(mx-i);
else p[i]=1;

首先我们知道对于一个字符串进行操作的时候，是从左到右依次进行的
那么由于回文串的对称性，
那么可以确定的是对于a[i]为中心的回文串的长度至少是在以这个最大的回文串中对称的那个位置为中心的回文串的长度,但只能确定的是在最大的回文串的那一部分中的长度,至于之外的就要一个个的匹配了
*/
/***
id  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
a： $ # 1 # 2 # 2 # 1 # 2 # 3 # 2 # 1 #
p_i 1 1 2 1 2 5 2 
*/
char a[N],str[N];
int p[N];
void Manacher(){
    int len  = 0;
    a[len] = '$', a[++len] = '#';
    int slen = strlen(str)-1;
    Rep(i,0,slen) a[++len] = str[i],a[++len] = '#';

    memset(p,0,sizeof(p));
    int id = -1,mx = -1,mxp = -1;
    Rep(i,0,len){
        if(mx > i) p[i] = (p[(id<<1)-i]<(mx-i))?p[(id<<1)-i]:(mx-i);
        else p[i]=1;
        while(i-p[i]>=0&&i+p[i]<=len&&a[i-p[i]]==a[i+p[i]]) p[i]++;
        if(p[i]+i>mx) mx=p[i]+i,id=i;
        if(p[i]>mxp) mxp = p[i];
    }
    printf("%d\n",mxp-1);
    return ;
}