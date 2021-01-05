## LRU算法框架

Least Recently Used 最少最近使用，一种缓存淘汰算法（[Cache replacement policies](https://en.wikipedia.org/wiki/Cache_replacement_policies)）。

LRU是按照访问时序来淘汰，LFU（Least FrequentlyUsed）是按照访问频率来淘汰。

基本思路：

- O(1)时间查找 ，hash表
- O(1)时间插入，链表

hash表缓存最近使用的value所处链表位置，链表按访问时间将最近访问的数据移到头节点；

需要注意的点：

- 为什么list Node需要保存key和value？
  - 因为超出容量时，删除map对尾节点的映射需要调用map_erase( key )，尾节点的key值就是直接调用list的back方法得到，list使用pair保存了key和对应的value。
- 每次插入新的key，value，需要进行判断是否已经映射，需要判断是否超出缓存容量，分别处理
- c++ list的splice方法是拼接链表，也可以利用这个方法快速将新节点插入到链表头
- 链表节点顺序代表了节点被访问的时间顺序，最近访问在最前面

```c++
class LRUCache {
    unordered_map<int, list<pair<int, int>>::iterator> hash;
    list<pair<int, int>> cache;
    int size;
public:
    LRUCache(int capacity):size(capacity){}

    int get(int key) {
        auto it = hash.find(key);
        if(it == hash.end()){  //key不存在
            return -1;         //返回-1
        }
        //将访问的数据(key,val)移到链表头
        cache.splice(cache.begin(), cache, it->second);it
        return it->second->second;//返回value值，注意理解，it->second返回的是pair的迭代器
    }
    
    void put(int key, int value) {
        auto it = hash.find(key);
        
        //key存在
        if(it != hash.end()){ 
            it->second->second = value;//更改
            return cache.splice(cache.begin(), cache, it->second);//移到链表头位置
        }
        
        //key不存在
        cache.insert(cache.begin(), make_pair(key, value));  //插入新节点
        hash[key] = cache.begin();                           //map映射新建key对新节点x的映射
        
        //超出缓存容量，删除尾节点
        if(cache.size() > size){
            hash.erase(cache.back().first);//list_Node需要保存key和value的原因在此，需要知道  
            cache.pop_back();              // key，才能删除map对该节点的映射
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

