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