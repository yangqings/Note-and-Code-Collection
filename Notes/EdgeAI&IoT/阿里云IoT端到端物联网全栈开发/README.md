

# 阿里云IoT端到端物联网全栈



<div align=center>
    <img src="images\0 课程场景.png" width="100%" />
</div>

## 端侧代码实现

端侧两种方式连接阿里云IoT平台：

- Paho MQTT 直连
  - 获取设备证书（三元组信息）productKey,  device name, device secret
  - 计算MQTT连接参数，连接AliIoT，订阅主题
- 加密传输，通过HTTPS认证再连接的模式（参考ST资料 I-Cube-Aliyun）

### MQTT协议

目前版本3.1.1

<div align=center>
    <img src="images\1 MQTT协议.png" width="100%" />
</div>

现在最新版本3.1.1，消息队列遥测传输，应用层协议

- 轻量级，开销小
- 异步通信模式，解耦通信双方
- 主流的MQTT是基于TCP连接进行数据推送的，但是同样有基于UDP的版本，叫做MQTT-SN。这两种版本由于基于不同的连接方式，优缺点自然也就各有不同了。

客户端：设备

代理端：服务器

<div align=center>
    <img src="images\2 MQTT主题和消息.png" width="100%" />
</div>





<div align=center>
    <img src="images\3 MQTT连接与会话.png" width="100%" />
</div>



<div align=center>
    <img src="images\4 MQTT报文格式.png" width="100%" />
</div>





<div align=center>
    <img src="images\5 MQTT QOS级别.png" width="100%" />
</div>



主流的IoT平台都没有实现QoS2级别的通信，开销太大，可以通过QoS1级别的通信，通过甄别消息ID，保证收到一条数据

<div align=center>
    <img src="images\6 MQTT Retain消息.png" width="100%" />
</div>

<div align=center>
    <img src="images\7 阿里云IoT平台侧的MQTT实现.png" width="100%" />
</div>


### 设备端代码工程结构（重点）

#### 整体架构

<div align=center>
    <img src="images\8 设备软件架构.png" width="100%" /">
</div>

#### 网络数据流分层



## 服务器端代码实现

