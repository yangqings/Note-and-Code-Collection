## Person_Detection_Experimental_Benchmark

- Tflite_Micro 行人检测模型Benchmark测试
- 硬件平台：NUCLEO_L496ZG开发板
- 代码工程：https://github.com/yangqings/TencentOS-tiny
- keil工程路径：`TencentOS-tiny/board/NUCLEO_STM32L496ZG/KEIL/tflitemicro_person_detection/`

#### 1. 调用MCU SysTick计时函数

修改`tensorflow/lite/micro/micro_time.cc`，修改后的代码如下：

```C++
#include "tensorflow/lite/micro/micro_time.h"
#include "sys.h"

namespace tflite {

// Reference implementation of the ticks_per_second() function that's required
// for a platform to support Tensorflow Lite for Microcontrollers profiling.
// This returns 0 by default because timing is an optional feature that builds
// without errors on platforms that do not need it.
uint32_t ticks_per_second() { 
	return (1000); 
}

// Reference implementation of the GetCurrentTimeTicks() function that's
// required for a platform to support Tensorflow Lite for Microcontrollers
// profiling. This returns 0 by default because timing is an optional feature
// that builds without errors on platforms that do not need it.
uint32_t GetCurrentTimeTicks() { 
	return (HAL_GetTick()); 
}

}  // namespace tflite
```

#### 2. 测试用例

##### 2.1 添加Benchmark Code

- 下载Tensorflow代码，从`Tensorflow\tensorflow\lite\micro\benchmarks`拷贝person_detection_experimental_benchmark.cc和micro_benchmark.h到`tensorflow\lite\micro\benchmarks`
- 将person_detection_experimental_benchmark.cc加入到keil工程
- 增加micro_benchmark.h头文件路径
- 将main.c中的main函数注释掉

person_detection_experimental_benchmark.cc增加头文件引用：

```c++
//增加头文件引用
#include "main.h"
#include "mcu_init.h"
#include "cmsis_os.h"
```

##### 2.2 Benchmark Code修改

person_detection_experimental_benchmark.h修改内容如下：

```c++
#define TF_LITE_MICRO_BENCHMARKS_BEGIN           \
  namespace micro_benchmark {                    \
  tflite::ErrorReporter* reporter;               \
  }                                              \
                                                 \
  int main(int argc, char** argv) {              \
    tflite::MicroErrorReporter error_reporter;   \
    micro_benchmark::reporter = &error_reporter; \
    uint32_t start_ticks;                         \
    uint32_t duration_ticks;                      \
    uint32_t duration_ms;\
		HAL_Init();\                          //增加初始化
		SystemClock_Config();\                //增加初始化
		board_init();                         //增加初始化
```



##### 2.3 Case 1 Without CMSIS-NN

手动修改keil工程，使用`tensorflow\lite\micro\kernels`中的七个reference算子：

- add.cc
- conv.cc
- depthwise_conv.cc
- fully_connected.cc
- mul.cc
- pooling.cc
- softmax.cc

编译执行，串口输出结果；



##### 2.4 Case 2 With CMSIS-NN

手动修改keil工程，remove七个reference算子，使用`tensorflow\lite\micro\kernels\cmsis-nn`中的七个CMSIS-NN算子加速，编译执行，串口输出结果。



#### 3. 测试结果

- 测试输入图片：`tensorflow\lite\micro\tools\make\downloads\person_model_int8`目录person_image_data.cc和no_person_image_data.cc中保存的96*96(uint_8)灰度图。
- 单次执行和10次迭代的测试结果如下：

|                      Case                      |   Without ARM-CMSIS-NN   |  With ARM-CMSIS-NN   | Improvement |
| :--------------------------------------------: | :----------------------: | :------------------: | :---------: |
|          Initialize_Benchmark_Runner           |     65 ticks (65 ms)     |   66 ticks (66 ms)   |      *      |
|              Run_Single_Iteration              |  12476 ticks (12476 ms)  |  633 ticks (633 ms)  |   19.71X    |
|   Person_Detection_Ten_Ierations_With_Person   | 124769 ticks (124769 ms) | 6324 ticks (6324 ms) |   19.73X    |
| Person_Detection_Ten_Ierations_With_out_Person | 124770 ticks (124770 ms) | 6325 ticks (6325 ms) |   19.72X    |
