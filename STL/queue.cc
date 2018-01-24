queue

// queue模版类的定义在<queue>头文件中. 
// queue与stack相似,queue模版类也需要两个模版参数,一个元素类型,一个容器类型,元素类型时必须的,容器类型时可选的,默认为deque类型.

// 定义queue对象的示例代码必须如下:
queue<int> q;
queue<double> qq;

// queue的基本操作:

q.push(x);  //  入队列
q.pop();    //  出队列
q.front();  //  访问队首元素
q.back();   //  访问队尾元素s
q.empty();  //  判断队列是否为空
q.size();   //  访问队列中的元素个数

priority_queue

// 在<queue>头文件中,还定义了另一个非常有用的模版类priority_queue(优先队列).优先队列与队列的差别在于
// 优先队列不是按照入队的顺序出队,而是按照队列中元素的优先权出队列(默认为大者优先,也可以通过指定算子
// 来指定自己的优先顺序).

// priority_queue模版类有三个模版参数,第一个是元素类型,第二个是容器类型,第三个是比较算子.
// 其中后两者都可以忽略,默认容器为vector,默认算子为less,即小的往前排,大的往后排(出队列时列尾元素先出队). 
// 定义priority_queue对象的代码示例：

priority_queue<int> q;
priority_queue<pair<int, int> > qq;                 //  注意在两个尖括号之间一定要留空格,防止误判
priority_queue<int, vector<int>, greater<int> > qqq;//  定义小的先出队列

// priority_queue的基本操作与queue的略微不同.

// priority_queue的基本操作：

q.empty()     //  如果队列为空,则返回true,否则返回false
q.size()      //  返回队列中元素的个数
q.pop()       //  删除队首元素,但不返回其值
q.top()       //  返回具有最高优先级的元素值,但不删除该元素
q.push(item)  //  在基于优先级的适当位置插入新元素

// 初学者在使用priority_queue时,最困难的可能就是如何定义比较算子了.
// 如果是基本数据类型,或已定义了比较运算符的类,
// 可以直接使用STL的less算子和greater算子——默认为使用less算子.
// 如果要定义自己的比较算子,方法有多种,这里介绍其中一种：重载比较运算符.
// 优先队列试图这两个元素x和y代入比较运算符(对于less算子,调用x < y,对于greater算子,调用x > y),
// 若结果为真,则x排在y前面,y将先出队列,反之,则y排在x前面,x将先出队列. 
// 如下算子示例：

class T{
    int x, y, z;
};

// 如果想要按照z的顺序从小到大出队列,只需要改动比较运算符重载为：

bool operator < (const T &tOne, const T &tTwo){
    return tOne.z > tTwo.z;  //  按照z的顺序来决定tOne和tTwo的顺序
}
// 则会得到和第二个例子一样的结果,所以,决定算子的是比较运算符重载函数内部的返回值.