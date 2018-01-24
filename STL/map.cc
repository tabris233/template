map

// 在STL的头文件中<map>中定义了模版类map和multimap,用有序二叉树表存储类型为pair<const Key, T>的元素对序列。
// 序列中的元素以const Key部分作为标识,map中所有元素的Key值必须是唯一的,multimap则允许有重复的Key值。

// 可以将map看作是由Key标识元素的元素集合,这类容器也被称为“关联容器”,可以通过一个Key值来快速决定一个元素,因此非常适合于需要按照Key值查找元素的容器。 
// map模版类需要四个模版参数,第一个是键值类型,第二个是元素类型,第三个是比较算子,第四个是分配器类型。
// 其中键值类型和元素类型是必要的。

// 定义map对象的代码示例：

map<string, int> m;
// map的基本操作:

/*  向map中插入元素  */
m[key] = value; //  [key]操作是map很有特色的操作,如果在map中存在键值为key的元素对, 则返回该元素对的值域部分,否则将会创建一个键值为key的元素对,值域为默认值。所以可以用该操作向map中插入元素对或修改已经存在的元素对的值域部分。
m.insert(make_pair(key, value));    //  也可以直接调用insert方法插入元素对,insert操作会返回一个pair,当map中没有与key相匹配的键值时,其first是指向插入元素对的迭代器,其second为true;若map中已经存在与key相等的键值时,其first是指向该元素对的迭代器,second为false。

/*  查找元素  */
int i = m[key]; //  要注意的是,当与该键值相匹配的元素对不存在时,会创建键值为key(当另一个元素是整形时,m[key]=0)的元素对。
map<string, int>::iterator it = m.find(key);    //  如果map中存在与key相匹配的键值时,find操作将返回指向该元素对的迭代器,否则,返回的迭代器等于map的end()(参见vector中提到的begin()和end()操作)。

/*  删除元素  */
m.erase(key);   //  删除与指定key键值相匹配的元素对,并返回被删除的元素的个数。
m.erase(it);    //  删除由迭代器it所指定的元素对,并返回指向下一个元素对的迭代器。

/*  其他操作  */
m.size();       //  返回元素个数
m.empty();      //  判断是否为空
m.clear();      //  清空所有元素