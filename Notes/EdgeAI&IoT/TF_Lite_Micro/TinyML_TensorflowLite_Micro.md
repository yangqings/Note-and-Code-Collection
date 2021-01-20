## TinyML:  TensorFlowLite Micro

#### 简介

**TensorFlow:**

PC环境，模型训练+推理，RAM需求为GB级别，存储空间需求为TB级别；

**TensorFlow Lite:**

- 针对手机等嵌入式设备（一般内核为Cortex-A级别）；
- 不支持模型训练，只支持推理，不支持TF主线的全部数据类型（比如double）；
- 不支持一些使用较少的算子（比如tf.depth_to_space）；
- 支持Android Neural Network API加速；
- 支持通过OpenGL使用GPU；
- 对网络的int8量化有很好的支持；

**TensorFlow Lite Micro:**

- 只支持推理；
- 内存限制，KB级别；
- 无操作系统依赖；
- 链接时无标准C或C++库依赖（实际上依赖C Math库）；
- 避免依赖浮点运算，转换为int8；
- 针对Cortex-M内核，支持ARM CMSIS-NN算子加速；
- 无动态内存分配，框架初始化阶段分配固定的内存空间；
- 使用C++ 11；
- 采用**解释执行模型**，模型与解释器分离的模式；
  - 与之对应的是**代码生成模式(code generation)**，将模型直接转换为C/C++代码，参数作为数组存储在代码中
  - 代码生成模式的优点：
    - 易于编译，源码包含了所有依赖；
    - 易修改性（源码可直接修改）；
    - 内联数据；
    - 代码大小较优，不会包含冗余代码；
  - 代码生成模式的缺点：
    - 可升级性相比模型解释方法较差
    - 一份代码不兼容多个模型
    - 替换模型困难
- 采用project generation + 解释执行模型，兼备代码生成的优点；
  - 优点：
    - 可升级性
    - 模型可替换性
    - 内联数据，模型参数以C数组编译到 程序中，FlatBuffers序列化格式
    - 生成项目包含了外部依赖项
  - 缺点：
    - 难以直接减少代码size
    - 需要手动使用OpResolver机制注册希望使用的kernel
- 实现DebugLog方法是唯一需要针对特定平台作特定的适配，也就是将Debug信息printf；

#### 编译系统

#### 如何设计一个TinyML应用程序

可行性

资料

特征生成

数据可视化

确定需求

#### 优化延迟 

模型改进

估算模型延迟

加速

模型

量化

#### 优化功耗

#### 优化内存占用

#### 调试