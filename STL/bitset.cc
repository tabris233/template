bitset

// 可以当作一个bool型数组考虑,bitset<N> bs;  可以考虑成一个数组bool bs[N]。

// 相关操作：

bs.set();    //全部置1,bs.reset()全部置0;
bs.set(pos); //等价于bs[pos]=1,bs.reset(pos)等价于bs[pos]=0;


// 最重点的来了,bitset<N> a, b;

!a                  //按位取反  
a^b                 //按位异或  
a|b                 //按位或  
a&b                 //按位与  
a=b<<3              //整体移位  
a.count();          //a中1的个数  

//bitset优化有什么用呢

//如果有一个bool数组 a[N] 和b[N] 把每一个位异或的话,一定是
for (int i = 0; i < N; ++i) c[i] = a[i] ^ b[i];  

//但是如果用bitset直接a^b的话,只需要O(N/机器字节数)
//这样可以实现常数优化。