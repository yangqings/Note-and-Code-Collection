# 阿里云IoT端到端物联网全栈



![0 课程场景](images\0 课程场景.png)

## 端侧代码实现

端侧两种方式连接阿里云IoT平台：

- Paho MQTT 直连
  - 获取设备证书（三元组信息）productKey,  device name, device secret
  - 计算MQTT连接参数，连接AliIoT，订阅主题
- 加密传输，通过HTTPS认证再连接的模式（参考ST资料 I-Cube-Aliyun）

### MQTT协议

目前版本3.1.1

![1 MQTT协议](images\1 MQTT协议.png)

现在最新版本3.1.1，消息队列遥测传输，应用层协议

- 轻量级，开销小
- 异步通信模式，解耦通信双方
- 主流的MQTT是基于TCP连接进行数据推送的，但是同样有基于UDP的版本，叫做MQTT-SN。这两种版本由于基于不同的连接方式，优缺点自然也就各有不同了。

客户端：设备

代理端：服务器

![2 MQTT主题和消息](images\2 MQTT主题和消息.png)

![3 MQTT连接与会话](images\3 MQTT连接与会话.png)

![4 MQTT报文格式](images\4 MQTT报文格式.png)

![5 MQTT QOS级别](images\5 MQTT QOS级别.png)

主流的IoT平台都没有实现QoS2级别的通信，开销太大，可以通过QoS1级别的通信，通过甄别消息ID，保证收到一条数据

![6 MQTT Retain消息](images\6 MQTT Retain消息.png)

![7 阿里云IoT平台侧的MQTT实现](images\7 阿里云IoT平台侧的MQTT实现.png)

## 服务器端代码实现