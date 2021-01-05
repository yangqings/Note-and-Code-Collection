### Linux网络包接收过程

基于Linux3.10分析网络包接收过程

Linux实现的是：链路层（网卡驱动）、网络层（内核协议栈）、传输层（内核协议栈）

### 1. Linux收包过程总览

<div align=center>
<img src="./pic/Linux network 1.png" width=70% />
</div>

 内核和网络设备驱动是通过中断的方式来处理的。当设备上有数据到达的时候，会给CPU的相关引脚上触发一个电压变化，以通知CPU来处理数据。对于网络模块来说，由于处理过程比较复杂和耗时，如果在中断函数中完成所有的处理，将会导致中断处理函数（优先级过高）将过度占据CPU，将导致CPU无法响应其它设备，例如鼠标和键盘的消息。因此Linux中断处理函数是分上半部和下半部的。上半部是只进行最简单的工作，快速处理然后释放CPU，接着CPU就可以允许其它中断进来。剩下将绝大部分的工作都放到下半部中，可以慢慢从容处理。2.4以后的内核版本采用的下半部实现方式是软中断，由**ksoftirqd内核线程**全权处理。和硬中断不同的是，硬中断是通过给CPU物理引脚施加电压变化，而**软中断是通过给内存中的一个变量的二进制值以通知软中断处理程序**。

<div align=center>
<img src="./pic/Linux network 2.png" width=100% />
</div>

当网卡上收到数据以后，Linux中第一个工作的模块是网络驱动。网络驱动会以**DMA的方式把网卡上收到的帧写到内存里**。再向CPU发起一个中断，以通知CPU有数据到达。第二，当CPU收到中断请求后，会去调用网络驱动注册的中断处理函数。网卡的中断处理函数并不做过多工作，发出软中断请求，然后尽快释放CPU。ksoftirqd检测到有软中断请求到达，调用**poll开始轮询收包**，收到后交由各级协议栈处理。对于UDP包来说，会被放到用户socket的接收队列中。

### 2. Linux启动

在准备接收网卡数据包之前，准备工作：

- 创建ksoftirq内核线程

- 网络子系统初始化

- 协议栈注册

  <div align=center>
  <img src="./pic/Linux network 3.png" width=100% />
  </div>

- 网卡驱动初始化

  <div align=center>
  <img src="./pic/Linux network 4.png" width=100% />
  </div>

  网卡驱动实现了ethtool所需要的接口，也在这里注册完成函数地址的注册。当 ethtool 发起一个系统调用之后，内核会找到对应操作的回调函数。

  对于igb网卡来说，其实现函数都在`drivers/net/ethernet/intel/igb/igb_ethtool.c`下。

  ethtool这个命令之所以能查看网卡收发包统计、能修改网卡自适应模式、能调整RX 队列的数量和大小，是因为ethtool命令最终调用到了网卡驱动的相应方法，而不是ethtool本身有这个超能力。

- 启动网卡

  当启用一个网卡时（例如，通过 ifconfig eth0 up），net_device_ops 中的 igb_open方法会被调用。它通常会做以下事情：

  <div align=center>
  <img src="./pic/Linux network 5.png" width=100% />
  </div>

### 3.接收数据

- 硬中断处理

  首先当数据帧从网线到达网卡上的时候，第一站是网卡的接收队列。网卡在分配给自己的RingBuffer中寻找可用的内存位置，找到后DMA引擎会把数据DMA到网卡之前关联的内存里，这个时候CPU都是无感的。当DMA操作完成以后，网卡会像CPU发起一个硬中断，通知CPU有数据到达。

  <div align=center>
  <img src="./pic/Linux network 6.png" width=100% />
  </div>

  注意：当RingBuffer满的时候，新来的数据包将给丢弃。ifconfig查看网卡的时候，可以里面有个overruns，表示因为环形队列满被丢弃的包。如果发现有丢包，可能需要通过ethtool命令来加大环形队列的长度

  

- ksoftirq内核线程处理软中断





### 总结：

#### 准备工作

1. 创建ksoftirqd线程，为它设置好它自己的线程函数，后面指望着它来处理软中断呢
2. 协议栈注册，linux要实现许多协议，比如arp，icmp，ip，udp，tcp，每一个协议都会将自己的处理函数注册一下，方便包来了迅速找到对应的处理函数
3. 网卡驱动初始化，每个驱动都有一个初始化函数，内核会让驱动也初始化一下。在这个初始化过程中，把自己的DMA准备好，把NAPI的poll函数地址告诉内核
4. 启动网卡，分配RX，TX队列，注册中断对应的处理函数

#### 接收数据

1. 网卡将数据帧DMA到内存的RingBuffer中，然后向CPU发起中断通知

2. CPU响应中断请求，调用网卡启动时注册的中断处理函数

3. 中断处理函数几乎没干啥，就发起了软中断请求

4. 内核线程ksoftirqd线程发现有软中断请求到来，先关闭硬中断

5. ksoftirqd线程开始调用驱动的poll函数收包

6. poll函数将收到的包送到协议栈注册的ip_rcv函数中

7. ip_rcv函数再讲包送到udp_rcv函数中（对于tcp包就送到tcp_rcv）

