# Binary Search二分查找

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
int right  = nums.length - 1; //注意初始化的值

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

##### 寻找左边界的二分查找

```c++
int left_bound(int [] nums, int target)
{
	if(nums.length == 0) return -1;
	int left = 0;
	int right = nums.length; //注意
	
	while(left < right){
		int mid = (left + right) / 2;
		if(nums[mid] == target){
			right = mid;    //注意[left, mid)，找到目标先不返回，继续缩小边界
		}else if(nums[mid] < target){
			left = mid + 1; //[mid + 1, right)]
		}else if(nums[mid] > target){
			right = mid;//注意
		}
	}
    
    if( left == nums.length ) return -1;
    return nums[left] == target ? left : -1;
}
```

##### 查找双闭区间的左边界二分查找

```c++
int left_bound(int [] nums, int target)
{
	int left = 0;
	int right = nums.length - 1; //区间[left, right]
	
	while(left <= right){
		int mid = (left + right) / 2;
		if(nums[mid] == target){
			right = mid - 1;//继续缩小右边界
		}else if(nums[mid] < target){
			left = mid + 1; //[mid + 1, right]
		}else if(nums[mid] > target){
			right = mid - 1;//注意[left, mid-1]
		}
	}
    
    if( left >= nums.length || nums[left] != target) return -1;
    return left;
}
```

##### 右边界二分查找

```c++
int right_bound(int[] nums, int target)
{
    if(nums.length == 0)return -1;
    int left = 0, right = nums.length;
    
    while(left < right){
        int mid = left + (right - left)/2;
        if( nums[mid] == target){
            left = mid + 1; //mid = left - 1
        }else if(nums[mid] < target){
            left = mid + 1;
        }else if(nums[mid] > target){
            right = mid;
        }
    }
    
    if(left == 0)return -1;
    return nums[left -1] == target ? (left - 1) : -1;
}
```

##### 二分查找及其变种

完全有序：

- 二分查找
- leetcode34 查找排序数组第一个元素和最后一个元素
- 找出第一个大于目标元素的索引
- 找出第一个小于目标元素的索引

不完全有序

- leetcode33 搜索旋转数组，查找目标元素（不含重复）
- leetcode81 搜索旋转数组，查找目标元素（含重复）
- leetcode153 寻找旋转数组最小值

二维数组

- leetcode74 搜索二维矩阵