## Hash

一个简单的HashTable

```c++
template <typename T>
class HashTable {
private:
	vector<list<T>> hash_table;
	// 哈希函数
	int myhash(const T & obj) const {
		return hash(obj, hash_table.size());
	}
public:
	// size最好是质数
	HashTable(int size=31) {
		hash_table.reserve(size);
		hash_table.resize(size);
	}
	~HashTable() {}
	// 查找哈希表是否存在该值
	bool contains(const T & obj) {
		int hash_value = myhash(obj);
		const list<T> & slot = hash_table[hash_value];
		std::list<T>::const_iterator it = slot.cbegin();
		for (; it != slot.cend() && *it != obj; ++it);
		return it != slot.cend();
	}
	// 插入值
	bool insert(const T & obj) {
		if (contains(obj)) {
			return false;
		}
		int hash_value = myhash(obj);
		std::list<T> & slot = hash_table[hash_value];
		slot.push_front(obj);
		return true;
	}
	// 删除值
	bool remove(const T & obj) {
		list<T> & slot = hash_table[myhash(obj)];
		auto it = find(slot.begin(), slot.end(), obj);
		if (it == slot.end()) {
			return false;
		}
		slot.erase(it);
		return true;
	}
};
// 一个简单的对整数实现的哈希函数
int hash(const int & key, const int &tableSize) {
	return key % tableSize;
}
```

