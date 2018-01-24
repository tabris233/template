multiset

// 在<set>头文件中，还定义了另一个非常实用的模版类multiset(多重集合)。
// 多重集合与集合的区别在于集合中不能存在相同元素，而多重集合中可以存在。

// 定义multiset对象的示例代码如下：

multiset<int> s;
multiset<double> ss;

// multiset和set的基本操作相似，需要注意的是，集合的count()能返回0(无)或者1(有)，
// 而多重集合是有多少个返回多少个。