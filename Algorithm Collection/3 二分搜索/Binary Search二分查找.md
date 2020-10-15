#### Binary Search二分查找

##### 基本框架：

```c++
int bianrySearch(int[] nums, int target)
{
    int left = 0, right = ...;
    while(...){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target){
            ...
        }else if(nums[mid] < target){
            left = ...
        }else if(nums[mid] > target){
            right = ...
        }
    }
    return ...;
}
```

需要注意的问题：计算mid，防止溢出；left+(right - left) / 2 和  (left + right ) / 2效果一样，但是前者有效防止了溢出



##### 基本二分查找

```c++
int right  = nums.lenght - 1; //注意初始化的值

while(left <= right){
    int mid = left + (right - left) / 2;
    if(nums[mid] == target){
        return mid;
    }else if(nums[mid] < target){
        left = mid + 1; //注意这里是mid + 1
    }else if(nums[mid] > target){
        right = mid - 1;//注意这里是mid — 1
    }
    return -1;
}
```

初始化right 为nums.lenght - 1和nums.lenght区别：

前者查找范围：[left, right]

后者查找范围：[left, right)

##### 基本二分查找缺陷

比如数组nums = [1, 2, 2, 2, 3]，target为2，算法返回的索引是1，此算法无法保证得到左边界索引(1)或者右边界索引(3)。



