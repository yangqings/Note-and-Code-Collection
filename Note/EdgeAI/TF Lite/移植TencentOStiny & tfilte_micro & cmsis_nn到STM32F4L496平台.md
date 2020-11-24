# 移植TencentOStiny & tfilte_micro & cmsis_nn到STM32F4L496平台

## STM32F4L496

L4系列芯片

关键参数：

- Frequency：80Mhz
- Power Efficiency：91uA/MHz (LDO Mode), 37uA/MHz (SMPS Mode)

- SRAM：320KB

- Flash：1M Flash
- Other：DSP Instruct , FPU, ART, DCMI

## TencentOStiny移植

参考TOS官方移植文档即可

## tfilte_micro移植

#### tflite_micro代码结构：

- all_ops_resover
- micro_interpreter
- micro_test
- schema_generated
- model_data

#### 测试宏定义



#### TFlite工作流程

1. include dependencies
2. Setting Test Framwork
3. Set up logging
4. Mapping model
5. Creating an AllOpsResover
6. Defining a tensor arena
7. Creating an Interpreter
8. Inspecting the input tensor
9. Runnig Inference on an input
10. Reading the output
11. Runing the test

## cmsis_nn移植



## 摄像头驱动

#### 移植步骤：

1. 摄像头SCCB协议（类似IIC，但是数据位为9位，多一位dummy位）驱动移植，能够读取设备ID和配置Camera寄存器，完成摄像头初始化；
2. DCMI初始化，需要将DCMI数据流与DMA通道连接。一般常见的情况是把DCMI数据通过DMA传到LCD的GRAM；STM32L496还有一个DMA2d的外设，图像加速，图像数据也可以先经过DMA2d，做一些硬件支持的图像处理（resize或者格式转换之类的），然后再传到GRAM；
3. DMA初始化，本项目不把图像数据存到外部存储器，所以将DCMI与DMA连接，数据目的地址是内部SRAM
4. 摄像头分辨率设置、ousize_set、resize容易导致图像数据出问题，需要注意。

## Person Dectection Demo



## Key Word Dectection Demo

