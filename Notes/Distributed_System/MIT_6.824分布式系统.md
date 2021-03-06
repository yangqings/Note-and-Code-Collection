## MIT 6.824分布式系统

[TOC]

### 重要概念：

- **MapReduce:**  MapReduce 编程模型。总的来讲，Google MapReduce 所执行的分布式计算会以一组键值对作为输入，输出另一组键值对，用户则通过编写 Map 函数和 Reduce 函数来指定所要进行的计算；

  使用函数式编程模型的好处在于这种编程模型本身就对并行执行有良好的支持，这使得底层系统能够轻易地将大数据量的计算并行化，同时由用户函数所提供的确定性也使得底层系统能够将函数重新执行作为提供容错性的主要手段；

- **GFS:** 谷歌分布式**文件**系统，容错分布式存储；
- **Primary-Backup Replication:** 主从备份，指得是备份“计算”，实现可容错服务器的一种常用方案；
- **Raft:**  一种分布式共识算法，在 Replicated State Machine 中，分布式共识算法的职责就是按照固定的顺序将指定的日志内容备份到集群的其他实例上。

### Lecure 1 MapReudce

#### 0 概述

**为什么需要MapReduce？**

MapReduce是一种编程模型，用于大规模数据集（大于1TB）的并行运算。概念"Map（映射）"和"Reduce（归约）"，是它们的主要思想，都是从函数式编程语言里借来的，还有从矢量编程语言里借来的特性。它极大地方便了编程人员在不会分布式并行编程的情况下，将自己的程序运行在分布式系统上。 当前的软件实现是指定一个Map（映射）函数，用来把一组键值对映射成一组新的键值对，指定并发的Reduce（归约）函数，用来保证所有映射的键值对中的每一个共享相同的键组

我的理解：MapReduce是一种函数式编程模型，比如要实现一个对文本文件的单词计数的分布式系统，使用MapReduce框架：

- 将输入切成chunk（假设按行切分）
- Master节点为每个MapWorker分发chunk
- MapWorker执行根据单词计数逻辑定义的Map函数，<k1, v1> ---> <k2, v2>

**为什么MapReduce会被谷歌淘汰？**

从2014年开始Google开始不使用新的MapReduce，2016年开始MapReduce替换**Flume**

#### 1.1 MapReduce编程模型

总的来讲，Google MapReduce 所执行的分布式计算会以**一组键值对作为输入**，**输出另一组键值对**，用户则通过编写 Map 函数和 Reduce 函数来指定所要进行的计算。用户首先创建一个Map函数处理一个基于 key/value pair的数据集合，输出中间的基于key/value pair的数据集合；然后再创建一个Reduce函数用来合并所有的具有相同中间key值的中间value值。

#### 1.2 函数式编程模型

了解函数式编程范式的读者不难发现，MapReduce 所采用的编程模型源自于函数式编程里的 Map 函数和 Reduce 函数。后起之秀 Spark 同样采用了类似的编程模型。

使用函数式编程模型的好处在于这种编程模型本身就对并行执行有良好的支持，这使得底层系统能够轻易地将大数据量的计算并行化，同时由用户函数所提供的确定性也使得底层系统能够将函数重新执行作为提供容错性的主要手段

形式化地说，由用户提供的 Map 函数和 Reduce 函数应有如下类型：

map(k1,v1)→list(k2,v2)

reduce(k2,list(v2))→list(v2)

值得注意的是，在实际的实现中 MapReduce 框架使用 `Iterator` 来代表作为输入的集合，主要是为了避免集合过大，无法被完整地放入到内存中。

作为案例，我们考虑这样一个问题：给定大量的文档，计算其中每个单词出现的次数（Word Count）。用户通常需要提供形如如下伪代码的代码来完成计算：

```
map(String key, String value):
  // key: document name
  // value: document contents
  for each word w in value:
    EmitIntermediate(w, “1”);


reduce(String key, Iterator values):
  // key: a word
  // values: a list of counts
  int result = 0;
  for each v in values:
    result += ParseInt(v);
  Emit(AsString(result));
```

#### 1.3 MapReduce 计算执行过程

每一轮 MapReduce 的大致过程如下图所示：

[![img](\PIC\Lec1\mapreduce_architecture.png)](https://mr-dai.github.io/img/mapreduce_summary/mapreduce_architecture.png)

首先，用户通过 MapReduce 客户端指定 Map 函数和 Reduce 函数，以及此次 MapReduce 计算的配置，包括中间结果键值对的 Partition 数量 RR 以及用于切分中间结果的哈希函数 hashhash。 用户开始 MapReduce 计算后，整个 MapReduce 计算的流程可总结如下：

1. 作为输入的文件会被分为 MM 个 Split，每个 Split 的大小通常在 16~64 MB 之间
2. 如此，整个 MapReduce 计算包含 MM 个Map 任务和 RR 个 Reduce 任务。Master 结点会从空闲的 Worker 结点中进行选取并为其分配 Map 任务和 Reduce 任务
3. 收到 Map 任务的 Worker 们（又称 Mapper）开始读入自己对应的 Split，将读入的内容解析为输入键值对并调用由用户定义的 Map 函数。由 Map 函数产生的中间结果键值对会被暂时存放在缓冲内存区中
4. 在 Map 阶段进行的同时，Mapper 们周期性地将放置在缓冲区中的中间结果存入到自己的本地磁盘中，同时根据用户指定的 Partition 函数（默认为 hash(key)hash(key) modmod RR）将产生的中间结果分为 RR 个部分。任务完成时，Mapper 便会将中间结果在其本地磁盘上的存放位置报告给 Master
5. Mapper 上报的中间结果存放位置会被 Master 转发给 Reducer。当 Reducer 接收到这些信息后便会通过 RPC 读取存储在 Mapper 本地磁盘上属于对应 Partition 的中间结果。在读取完毕后，Reducer 会对读取到的数据进行排序以令拥有相同键的键值对能够连续分布
6. 之后，Reducer 会为每个键收集与其关联的值的集合，并以之调用用户定义的 Reduce 函数。Reduce 函数的结果会被放入到对应的 Reduce Partition 结果文件

实际上，在一个 MapReduce 集群中，Master 会记录每一个 Map 和 Reduce 任务的当前完成状态，以及所分配的 Worker。除此之外，Master 还负责将 Mapper 产生的中间结果文件的位置和大小转发给 Reducer。

值得注意的是，每次 MapReduce 任务执行时，MM 和 RR 的值都应比集群中的 Worker 数量要高得多，以达成集群内负载均衡的效果。

#### 1.4 MapReduce 容错机制

由于 Google MapReduce 很大程度上利用了由 Google File System 提供的分布式原子文件读写操作，所以 MapReduce 集群的容错机制实现相比之下便简洁很多，也主要集中在任务意外中断的恢复上。

##### 1.4.1 Worker 失效

在 MapReduce 集群中，Master 会周期地向每一个 Worker 发送 Ping 信号。如果某个 Worker 在一段时间内没有响应，Master 就会认为这个 Worker 已经不可用。

任何分配给该 Worker 的 Map 任务，无论是正在运行还是已经完成，都需要由 Master 重新分配给其他 Worker，因为该 Worker 不可用也意味着存储在该 Worker 本地磁盘上的中间结果也不可用了。Master 也会将这次重试通知给所有 Reducer，没能从原本的 Mapper 上完整获取中间结果的 Reducer 便会开始从新的 Mapper 上获取数据。

如果有 Reduce 任务分配给该 Worker，Master 则会选取其中尚未完成的 Reduce 任务分配给其他 Worker。鉴于 Google MapReduce 的结果是存储在 Google File System 上的，已完成的 Reduce 任务的结果的可用性由 Google File System 提供，因此 MapReduce Master 只需要处理未完成的 Reduce 任务即可。

##### 1.4.2 Master 失效

整个 MapReduce 集群中只会有一个 Master 结点，因此 Master 失效的情况并不多见。

Master 结点在运行时会周期性地将集群的当前状态作为保存点（Checkpoint）写入到磁盘中。Master 进程终止后，重新启动的 Master 进程即可利用存储在磁盘中的数据恢复到上一次保存点的状态。

##### 1.4.3 落后的 Worker

如果集群中有某个 Worker 花了特别长的时间来完成最后的几个 Map 或 Reduce 任务，整个 MapReduce 计算任务的耗时就会因此被拖长，这样的 Worker 也就成了落后者（Straggler）。

MapReduce 在整个计算完成到一定程度时就会将剩余的任务进行备份，即同时将其分配给其他空闲 Worker 来执行，并在其中一个 Worker 完成后将该任务视作已完成。

#### 1.5 其他优化

在高可用的基础上，Google MapReduce 系统现有的实现同样采取了一些优化方式来提高系统运行的整体效率。

##### 1.5.1 数据本地性

在 Google 内部所使用的计算环境中，机器间的网络带宽是比较稀缺的资源，需要尽量减少在机器间过多地进行不必要的数据传输。

Google MapReduce 采用 Google File System 来保存输入和结果数据，因此 Master 在分配 Map 任务时会从 Google File System 中读取各个 Block 的位置信息，并尽量将对应的 Map 任务分配到持有该 Block 的 Replica 的机器上；如果无法将任务分配至该机器，Master 也会利用 Google File System 提供的机架拓扑信息将任务分配到较近的机器上。

##### 1.5.2 Combiner

在某些情形下，用户所定义的 Map 任务可能会产生大量重复的中间结果键，同时用户所定义的 Reduce 函数本身也是满足交换律和结合律的。

在这种情况下，Google MapReduce 系统允许用户声明在 Mapper 上执行的 Combiner 函数：Mapper 会使用由自己输出的 RR 个中间结果 Partition 调用 Combiner 函数以对中间结果进行局部合并，减少 Mapper 和 Reducer 间需要传输的数据量。



### Lecure 2 RPC and Threads

RPC ( Remote Procedure Call ): 远程过程调用，简单的理解就是，一个节点请求另一个节点提供服务

Cordination

这节课的总结：



### Lecure 3 GFS

```mermaid
graph LR
WANT_PERFORMANCE-->NEED_SHARDING
DONT_WANT_FAULTS-->NEED_TOLENRANCE
WANT_TOLERANCE-->NEED_REPLICATION
WANT_REPLICATION-->NEED_IN_CONSISCCENCY
WANT_CONSISCENCY-->_LOW_PERFORMANCE
```

#### 3.1  GFS Target:

- Big, Fast
- Global, Universal
- Sharding
- Automatic Rcovering



#### 3.2 Paper: *The Google File System* 

Topic：谷歌分布式文件系统

##### 3.2.1 GFS设计原则：

- 节点失效是常态
- 存储内容以大文件为主

##### 3.2.2 GFS集群架构：

![GFS集群架构](PIC/GFS Architecture.png)

##### 3.2.3 chunk大小：

##### 3.2.4 GFS元数据管理：

GFS元数据主要包括的信息：

- 文件和Chunk的命名空间
- 文件与Chunk的映射
- Chunk Replica的位置信息

元数据保存在Master内存中使得Master要对元数据作出变更变得极为容易；同时，这也使得Master可以简单高效地周期性扫描整个集群的状态，以实现Chunk回收、迁移、均衡等操作。唯一的不足在于这使得整个集群所能拥有的Chunk数量受限于Master的内存大小，然而实际中不必担心这种情况，因为一个64MB的Chunk，只需要保存64KB的元数据，况且提高Master内存容量的成本也很低。

Master会把前两类信息以日志形式持久化存储在Master的本地磁盘上，并在在其他机器上备份，但是不会持久化保存Chunk Replica的位置信息，而是在集群启动时由Master询问各个Chunk Server其当前所有的Repica。这样做可以省去由于Chunk Server离开集群、更改名字、重启等原因的Master与Chunk Server的同步问题。此后，Master通过心跳包来监控Chunk Server的状态并更新内存中的信息。

为了保证元数据的可用性，Master在对元数据做任何操作前对会用先写日志的形式将操作进行记录，只有当日志写入完成后才会响应客户端的请求，而这些日志也会备份到多个机器上。日志不仅是元数据的唯一持久化记录，也是定义操作执行顺序的时间线。文件、Chunk和他们的版本信息都由他们的创建时间唯一的永久的标识。

##### 3.2.5 Namespace管理：

##### 3.2.6 Chunk租约lease和变更顺序：

##### 3.2.7 GFS集群常见操作流程：

###### 3.2.7.1 文件写入：

###### 3.2.7.2文件追加：

###### 3.2.7.3 文件快照：

###### 3.2.7.4 文件读取：



#### 3.3 这节课的总结



### Lecure 4 Primary-Backup Replication

阅读《The Design of a Practical System for Fault-Tolerant Virtual Machines》这篇论文主要讲述了 VMware 公司如何利用一种协议来实现两个虚拟机之间的主从备份（Primary-Backup Replication）。

#### 4.1 背景：

为了实现容错服务器，主从备份是常用的方案：备份服务器需要在几乎任何时候保持与服务器保持一致，当主服务器失效后，备份服务器能马上接管，两种主要方式：

- **State Transfer 状态转移：**主服务器所有状态变化传输给备用服务器；方案简单，数据传输量大
- **Replication State Machine 备份状态机：**将需要备份的服务器视为一个确定性状态机--主备以相同方式启动，导入相同的输入，进入相同的状态、给出相同的输出；方案复杂，但是传输数据量小。

VMware 选用了状态机方法，因为对于虚拟机而言，其状态过于复杂，使用状态转移方法也不会简单多少。在虚拟机上应用备份状态机方法也会有一定的顾虑 —— 我们难以保证在虚拟机上运行的应用（即操作系统）是确定性的。实际上，在物理机上应用状态机方法是极其困难的，其所能接收到的输入很多都是不确定的（如定时器中断等），但虚拟机是运行在 Hypervisor（虚拟机管理程序）之上的抽象机器，通过 Hypervisor 这一隔离层便能很好地将非确定性的输入转变为确定性的输入（这种将非确定转为确定的思路在数据库中也很常见，参考 MongoDB oplog）。

#### 4. 2 Deterministic Replay

尽管目标很直白，但考虑到虚拟机的很多输入事件本身是不确定的，如时钟中断、网络中断和磁盘中断，这会为在虚拟机上实现状态机方法带来第一个挑战。这个问题可以被细分为三个问题：

1. 正确地捕获所有的输入事件以及它们的不确定性，以确保有足够地信息能够确定性地重放这些事件
2. 正确地在备份虚拟机上重放这些输入事件和不确定性
3. 保证性能不会因此降级

VMware 实现的主从备份方法名为 VMware vSphere Fault Tolerance，简称 VMware FT，它是基于 VMware Deterministic Replay 实现的。Deterministic Replay 解决了上面的前两个问题，而第三个问题则会由 VMware FT 来解决。

Deterministic Replay 会以日志记录的形式记录主服务器接收到的输入，这些日志信息则会由 VMware FT 传输到备份服务器并被重放。正如上面所提到的那样，真正的麻烦实际上来源于那些会产生不确定作用的输入。对于那些不确定的输入操作，Deterministic Replay 会记录足够多的信息，确保其在备份虚拟机上重新执行能够得到相同的状态和输出；而对于那些不确定的输入事件，如定时器、IO 操作完成中断等，Deterministic Replay 则会记录这些事件发生在哪个指令之后，这样在重放时备份服务器便能在指令流中相同的位置重放这些事件。

#### 4.3 VMware vSphere Fault Tolerance

#### 4.4 主从切换

#### 4.5 更多的考虑

##### 4.5.1 虚拟机恢复

##### 4.5.2 Logging Channel

#### 4.6 FAQ

> Q: Both GFS and VMware FT provide fault tolerance. How should we think about when one or the other is better?
>
> Q：GFS 和 VMware FT 都提供了容错性。我们该怎么比较它们呢？

FT 备份的是**计算**，你能用它为任何已有的网络服务器提供容错性。FT 提供了相当严谨的一致性而且对客户端和服务器都是透明的。例如，你可以将 FT 应用于一个已有的邮件服务器并为其提供容错性。

相比之下，GFS 只为**存储**提供容错性。因为 GFS 只针对一种简单的服务提供容错性，它的备份策略会比 FT 更为高效：例如，GFS 不需要让所有的中断都以相同的顺序应用在所有的 Replica 上。GFS 通常只会被用作一个对外提供完整容错服务的系统的一部分：例如，VMware FT 本身也依赖了一个在主备虚拟机间共享的有容错性的存储服务，而你则可以用类似于 GFS 的东西来实现这个模块（虽然从细节上来讲 GFS 不太适用于 FT）。

> Q: What is “an atomic test-and-set operation on the shared storage”?
>
> Q：论文中提到的“对共享存储的原子 test-and-set 操作”是什么？

意思就是说一个计算机可以在一个原子的操作中读取并且写入指定的磁盘块。如果两个计算机都调用了这个操作，那么两组读写操作不会交织在一起，而是其中一个计算机的读写操作会在另一个计算机的读写操作完成后再执行。

> Q: What happens if the primary fails just after it sends output to the external world?
>
> Q：如果主虚拟机在向外界进行输出后立刻就失效了会怎么样？

这个输出可能会执行两次：主虚拟机一次，备份虚拟机一次。对于网络和磁盘 IO 来说，这个重复不会产生任何问题。如果输出的是一个网络包，那么接收端的 TCP 栈会丢弃掉这个重复的包；如果是磁盘 IO，那么磁盘 IO 实际上是幂等的（两次操作会在同一个位置写入相同的数据，这之间也不会有其他的 IO）。

> Q: Is it reasonable to address only the fail-stop failures? What are other type of failures?
>
> Q：只去解决宕机失效的场景是合理的吗？还存在其他类型的失效吗？

这是合理的，因为现实世界中的多数失效本质上来讲都是宕机失效，例如各种网络失效和电源失效。要做到更好的话就需要处理那些似乎正在正常运行但其实正在产生错误结果的计算机 —— 在最坏的情况下，这样的失效可能是来源于一个恶意的攻击者。这类非宕机失效的失效通常被称为“拜占庭”（Byzantine）。我们实际上是有方法去应对拜占庭失效的，我们会在这节课的末尾学习这些方法，但 6.824 的主要内容还是关于宕机失效。

### Lecure 5 Go threads and Raft

#### 5.1 Go threads

关于Go Thread记录在`Note\C_CPP_Go_Rust`文件夹内的Go学习笔记，主要关注的重点是Go并发编程，以及视频课中提到的，容易出现死锁的几种情况：

- 1
- 2

Go Raft的Debug技巧：

- 1
- 2



#### 5.2 Raft 背景

在上一节中了解到，为了令进程实现高可用，我们可以对进程进行备份，而实现进程的主从备份有两种方法：

- **State Transfer**（状态转移）：主服务器将状态的所有变化都传输给备份服务器
- **Replicated State Machine**（备份状态机）：将需要备份的服务器视为一个确定性状态机 —— 主备以相同的状态启动，以相同顺序导入相同的输入，最后它们就会进入相同的状态、给出相同的输出

其中 Replicated State Machine 是较为常用的主从备份实现方式。常见的 Replicated State Machine 架构如下：

![GFS集群架构](PIC/Lec5/rsm-architecture.png)

Raft 分布式共识算法，在 Replicated State Machine 中，**分布式共识算法的职责就是按照固定的顺序将指定的日志内容备份到集群的其他实例上。**包括在primary-backup-replication中提到的 VMWare FT 协议、广为人知的 Paxos 协议以及Raft 协议，它们完成的工作都是如此。

#### 5.3 Raft 性质与集群交互

在行文上，Raft 的论文首先在图 2 和图 3 中给出了 Raft 算法组成的简单描述以及 Raft 所能为系统提供的性质。首先我们先来说说 Raft 所提供的性质：

- Election Safety（选举安全）：在任意给定的 Term 中，至多一个节点会被选举为 Leader
- Leader Append-Only（Leader 只追加）：Leader 绝不会覆写或删除其所记录的日志，只会追加日志
- Log Matching（日志匹配）：若两份日志在给定 Term 及给定 index 值处有相同的记录，那么两份日志在该位置及之前的所有内容完全一致
- Leader Completeness（Leader 完整性）：若给定日志记录在某一个 Term 中已经被提交（后续会解释何为“提交”），那么后续所有 Term 的 Leader 都将包含该日志记录
- State Machine Safety（状态机安全性）：如果一个服务器在给定 index 值处将某个日志记录应用于其上层状态机，那么其他服务器在该 index 值处都只会应用相同的日志记录

一个 Raft 集群由若干个节点组成。节点可能处于以下三种角色的其中之一：Leader、Follower 或 Candidate，职责分别如下：

- Leader 负责从客户端处接收新的日志记录，备份到其他服务器上，并在日志安全备份后通知其他服务器将该日志记录应用到位于其上层的状态机上
- Follower 总是处于被动状态，接收来自 Leader 和 Candidate 的请求，而自身不会发出任何请求
- Candidate 会在 Leader 选举时负责投票选出 Leader

在采用 Leader-Follower 架构的语境下，Raft 将其需要解决的共识问题拆分为了以下 3 个问题：

- Leader 选举：已有 Leader 失效后需要选举出一个新的 Leader
- 日志备份：Leader 从客户端处接收日志记录，备份到其他服务器上
- 安全性：如果某个服务器为其上层状态机应用了某个日志记录，那么其他服务器在该 index 值处则不能应用其他不同的日志记录

Raft算法运行时会把时间分成任意长度的Term，如图:

![GFS集群架构](PIC/Lec5/term.png)



每个 Term 的开头都会包含一次 Leader 选举，在选举中胜出的节点会担当该 Term 的 Leader。

Term 由单调递增的 Term ID 所标识，每个节点都会在内存中保存当前 Term 的 ID。每次节点间发生通信时，它们都会发出自己所保存的 Term ID；当节点从其他节点处接收到比自己保存的 Term ID 更大的 Term ID 值时，它便会更新自己的 Term ID 并进入 Follower 状态。在 Raft 中，节点间通信由 RPC 实现，主要有 RequestVote 和 AppendEntries 两个 RPC API，其中前者由处于选举阶段的 Candidate 发出，而后者由 Leader 发出。

整个集群的状态信息：

> 所有节点都会持有的持久化状态信息（在响应 RPC 前会先将更新写入到持久存储）：
>
> - `currentTerm`：当前 Term ID（初值为 `0`）
> - `votedFor`: 该 Term 中已接收到来自该节点的选票的 Candidate ID
> - `log[]`: 日志记录。第一个日志记录的 index 值为 `1`
>
> 所有节点都会持有的易失性状态信息：
>
> - `commitIndex`: 最后一个已提交日志记录的 index（初值为 `0`）
> - `lastApplied`: 最后一个已应用至上层状态机的日志记录的 index（初值为 `0`）
>
> Leader 才会持有的易失性状态信息（会在每次选举完成后初始化）：
>
> - `nextIndex[]`: 每个节点即将为其发送的下一个日志记录的 index（初值均为 Leader 最新日志记录 index 值 + 1）
> - `matchIndex[]`: 每个节点上已备份的最后一条日志记录的 index（初值均为 `0`）

在 Raft 集群中，节点间的交互主要由两种 RPC 调用构成。

首先是用于日志备份的 AppendEntries：

> AppendEntries RPC：由 Leader 进行调用，用于将日志记录备份至 Follower，同时还会被用来作为心跳信息
>
> 参数：
>
> - `term`: Leader 的 Term ID
> - `leaderId`: Leader 的 ID
> - `prevLogIndex`: 在正在备份的日志记录之前的日志记录的 index 值
> - `prevLogTerm`: 在正在备份的日志记录之前的日志记录的 Term ID
> - `entries[]`: 正在备份的日志记录
> - `leaderCommmit`: Leader 已经提交的最后一条日志记录的 index 值
>
> 返回值：
>
> - `term`: 接收方的当前 Term ID
> - `success`: 当 Follower 能够在自己的日志中找到 index 值和 Term ID 与 `prevLogIndex` 和 `prevLogTerm` 相同的记录时为 `true`
>
> 接收方在接收到该 RPC 后会进行以下操作：
>
> 1. 若 `term < currentTerm`，返回 `false`
> 2. 若日志中不包含index 值和 Term ID 与 `prevLogIndex` 和 `prevLogTerm` 相同的记录，返回 `false`
> 3. 如果日志中存在与正在备份的日志记录相冲突的记录（有相同的 index 值但 Term ID 不同），删除该记录以及之后的所有记录
> 4. 在保存的日志后追加新的日志记录
> 5. 若 `leaderCommit > commitIndex`，令 `commitIndex` 等于 `leaderCommit` 和最后一个新日志记录的 index 值之间的最小值

而后是用于 Leader 选举的 RequestVote：

> RequestVote RPC：由 Candidate 调起以拉取选票
>
> 参数：
>
> - `term`：Candidate 的 Term ID
> - `candidateId`: Candidate 的 ID
> - `lastLogIndex`: Candidate 所持有的最后一条日志记录的 index
> - `lastLogTerm`: Candidate 所持有的最后一条日志记录的 Term ID
>
> 返回值：
>
> - `term`：接收方的 Term ID
> - `voteGranted`：接收方是否同意给出选票
>
> 接收方在接收到该 RPC 后会进行以下操作：
>
> 1. 若 `term < currentTerm`，返回 `false`
> 2. 若 `votedFor == null` 且给定的日志记录信息可得出对方的日志和自己的相同甚至更新，返回 `true`

最后，Raft 集群的节点还需要遵循以下规则：

> 对于所有节点：
>
> - 若 `commitIndex > lastApplied`，则对 `lastApplied` 加 1，并将 `log[lastApplied]` 应用至上层状态机
> - 若 RPC 请求或相应内容中携带的 `term > currentTerm`，则令 `currentTerm = term`，且 Leader 降级为 Follower
>
> 对于 Follower：
>
> - 负责响应 Candidate 和 Leader 的 RPC
> - 如果在 Election Timeout 之前没能收到来自当前 Leader 的 AppendEntries RPC 或将选票投给其他 Candidate，则进入 Candidate 角色
>
> 对于 Candidate：
>
> - 在进入 Candidate 角色时，发起 Leader 选举：
>   1. `currentTerm` 加 1
>   2. 将选票投给自己
>   3. 重置 Election Timeout 计时器
>   4. 发送 RequestVote RPC 至其他所有节点
> - 如果接收到来自其他大多数节点的选票，则进入 Leader 角色
> - 若接收到来自其他 Leader 的 AppendEntries RPC，则进入 Follower 角色
> - 若再次 Election Timeout，那么重新发起选举
>
> 对于 Leader：
>
> - 在空闲时周期地向 Follower 发起空白的 AppendEntries RPC（作为心跳信息），以避免 Follower 发起选举
>
> - 若从客户端处接收到新的命令，则将该命令追加到所存储的日志中，并在顺利将该命令应用至上层状态机后返回响应
>
> - 如果最新一条日志记录的 index 值大于等于某个 Follower 的
>
>    
>
>   ```
>   nextIndex
>   ```
>
>    
>
>   值，则通过 AppendEntries RPC 发送在该
>
>    
>
>   ```
>   nextIndex
>   ```
>
>    
>
>   值之后的所有日志记录：
>
>   1. 如果备份成功，那么就更新该 Follower 对应的 `nextIndex` 和 `matchIndex` 值
>   2. 否则，对 `nextIndex` 减 1 并重试
>
> - 如果存在一个值 `N`，使得 `N > commitIndex`，且大多数的 `matchIndex[i] >= N`，且 `log[N].term == currentTerm`，令 `commitIndex = N`

summary如下：

![GFS集群架构](PIC/Lec5/summary.png)

接下来我们将分章节介绍 Raft 的主要实现以及各种约束的主要考虑

#### 5.4 Leader 选举

在初次启动时，节点首先会进入 Follower 角色。只要它能够一直接收到来自其他 Leader 节点发来的 RPC 请求，它就会一直处于 Follower 状态。如果接收不到来自 Leader 的通信，Follower 会等待一个称为 Election Timeout（选举超时）的超时时间，然后便会开始发起新一轮选举。

Follower 发起选举时会对自己存储的 Term ID 进行自增，并进入 Candidate 状态。随后，它会将自己的一票投给自己，并向其他节点并行地发出 RequestVote RPC 请求。其他节点在接收到该类 RPC 请求时，会以先到先得的原则投出自己在该 Term 中的一票。

当 Candidate 在某个 Term 接收到来自集群中大多数节点发来的投票时，它便会成为 Leader，然后它便会向其他节点进行通信，确保其他节点知悉它是 Leader 而不会发起又一轮投票。每个节点在指定 Term 内只会投出一票，而只有接收到大多数节点发来的投票才能成为 Leader 的性质确保了在任意 Term 内都至多会有一个 Leader。由此我们实现了前面提及的 Eleaction Safety 性质。

Candidate 在投票过程中也有可能收到来自其他 Leader 的 AppendEntries RPC 调用，这意味着有其他节点成为了该 Term 的 Leader。如果该 RPC 中携带的 Term ID 大于等于 Candidate 当前保存的 Term ID，那么 Candidate 便会认可其为 Leader，并进入 Follower 状态，否则它会拒绝该 RPC 并继续保持其 Candidate 身份。

除了上述两种情况以外，选举也有可能发生平局的情况：若干节点在短时间内同时发起选举，导致集群中没有任何一个节点能够收到来自集群大多数节点的投票。此时，节点同样会在等待 Election Timeout 后发起新一轮的选举，但如果不加入额外的应对机制，这样的情况有可能持续发生。为此，Raft 为 Election Timeout 的取值引入了随机机制：节点在进入新的 Term 时，会在一个固定的区间内（如 150~300ms）随机选取自己在该 Term 所使用的 Election Timeout。通过随机化来错开各个节点进入 Candidate 状态的时机便能有效避免这种情况的重复发生。

#### 5.5 日志备份

在选举出一个 Leader 后，Leader 便能够开始响应来自客户端的请求了。客户端请求由需要状态机执行的命令所组成：Leader 会将接收到的命令以日志记录的形式追加到自己的记录里，并通过 AppendEntries RPC 备份到其他节点上；当日志记录被安全备份后，Leader 就会将该命令应用于位于自己上层的状态机，并向客户端返回响应；无论 Leader 已响应客户端与否，Leader 都会不断重试 AppendEntries RPC 调用，直到所有节点都持有该日志记录的备份。

日志由若干日志记录组成：每条记录中都包含一个需要在状态机上执行的命令，以及其对应的 index 值；除外，日志记录还会记录自己所属的 Term ID。

![GFS集群架构](PIC/Lec5/log-entries.png)



当某个日志记录顺利备份到集群大多数节点上后，Leader 便会认为该日志记录“已提交”（Committed），即该日志记录已可被安全的应用到上层状态机上。Raft 保证一个日志记录一旦被提交，那么它最终就会被所有仍可用的状态机所应用。除外，一条日志记录的提交也意味着位于其之前的所有日志记录也进入“已提交”状态。Leader 会保存其已知的最新的已提交日志的 index 值，并在每次进行 AppendEntries RPC 调用时附带该信息；Follower 在接收到该信息后即可将对应的日志记录应用在位于其上层的状态机上。

在运行时，Raft 能为系统提供如下两点性质，这两点性质共同构成了论文图 3 中提到的 Log Matching 性质：

- 对于两份日志中给定的 index 处，如果该处两个日志记录的 Term ID 相同，那么它们存储的状态机命令相同
- 如果两份日志中给定 index 处的日志记录有相同的 Term ID 值，那么位于它们之前的日志记录完全相同

第一条性质很容易得出，考虑到 Leader 在一个 Term 中只会在一个 index 处创建一条日志记录，而且日志的位置不会发生改变。为了提供上述第二个性质，Leader 在进行 AppendEntries RPC 调用时会同时携带在其自身的日志存储中位于该新日志记录之前的日志记录的 index 值及 Term ID；如果 Follower 在自己的日志存储中没有找到这条日志记录，那么 Follower 就会拒绝这条新记录。由此，每一次 AppendEntries RPC 调用的成功返回都意味着 Leader 可以确定该 Follower 存储的日志直到该 index 处均与自己所存储的日志相同。

AppendEntries RPC 的日志一致性检查是必要的，因为 Leader 的崩溃会导致新 Leader 存储的日志可能和 Follower 不一致。

![GFS集群架构](PIC/Lec5/inconsistent-logs.png)

考虑上图（即文中的图 7），对于给定的 Leader 日志，Follower 有可能缺失部分日志（a、b 情形）、有可能包含某些未提交的日志（c、d 情形）、或是两种情况同时发生（e、f 情形）。

对于不一致的 Follower 日志，Raft 会强制要求 Follower 与 Leader 的日志保持一致。为此，Leader 会尝试确定它与各个 Follower 所能相互统一的最后一条日志记录的 index 值，然后就会将 Follower 在该 index 之后的所有日志删除，再将自身存储的日志记录备份到 Follower 上。具体而言：

1. Leader 会为每个 Follower 维持一个 `nextIndex` 变量，代表 Leader 即将通过 AppendEntries RPC 调用发往该 Follower 的日志的 index 值
2. 在刚刚被选举为一个 Leader 时，Leader 会将每个 Follower 的 `nextIndex` 置为其所保存的最新日志记录的 index 之后
3. 当有 Follower 的日志与 Leader 不一致时，Leader 的 AppendEntries RPC 调用会失败，Leader 便对该 Follower 的 `nextIndex` 值减 1 并重试，直到 AppendEntries 成功
4. Follower 接收到合法的 AppendEntries 后，便会移除其在该位置上及以后存储的日志记录，并追加上新的日志记录
5. 如此，在 AppendEntries 调用成功后，Follower 便会在该 Term 接下来的时间里与 Leader 保持一致

由此，我们实现了前面提及的 Leader Append-Only 和 Log Matching 性质。

#### 5.6 Leader 选举约束

就上述所提及的 Leader 选举及日志备份规则，实际上是不足以确保所有状态机都能按照相同的顺序执行相同的命令的。例如，在集群运行的过程中，某个 Follower 可能会失效，而 Leader 继续在集群中提交日志记录；当这个 Follower 恢复后，有可能会被选举为 Leader，而它实际上缺少了一些已经提交的日志记录。

其他的基于 Leader 架构的共识算法都会保证 Leader 最终会持有所有已提交的日志记录。一些算法（如 Viewstamped Replication）允许节点在不持有所有已提交日志记录的情况下被选举为 Leader，并通过其他机制将缺失的日志记录发送至新 Leader。而这种机制实际上会为算法引入额外的复杂度。为了简化算法，Raft 限制了日志记录只会从 Leader 流向 Follower，同时 Leader 绝不会覆写它所保存的日志。

在这样的前提下，要提供相同的保证，Raft 就需要限制哪些 Candidate 可以成为 Leader。前面提到，Candidate 为了成为 Leader 需要获得集群内大多数节点的选票，而一个日志记录被提交同样要求它已经被备份到集群内的大多数节点上，那么如果一个 Candidate 能够成为 Leader，投票给它的节点中必然存在节点保存有所有已提交的日志记录。Candidate 在发送 RequestVote RPC 调用进行拉票时，它还会附带上自己的日志中最后一条记录的 index 值和 Term ID 值：其他节点在接收到后会与自己的日志进行比较，**如果发现对方的日志落后于自己的日志**（首先由 Term ID 决定大小，在 Term ID 相同时由 index 决定大小），就会**拒绝这次 RPC 调用**。如此一来，Raft 就能确保被选举为 Leader 的节点必然包含所有已经提交的日志。

**总结：**在投票给candidate的时候，会比较自己与对方日志，如果对方日志落后于自己，则不会投票。

#### 5.7 来自旧 Term 的日志记录old-entires

如上文所述，Leader 在备份当前 Term 的日志记录时，在成功备份至集群大多数节点上后 Leader 即可认为该日志记录已提交。但如果 Leader 在日志记录备份至大多数节点之前就崩溃了，后续的 Leader 会尝试继续备份该日志。然而，此时的 Leader 即使在将该日志备份至大多数节点上后都无法立刻得出该日志已提交的结论。

![GFS集群架构](PIC/Lec5/old-entries.png)

考虑上图这种情形。在时间点 (a) 时，S1 是 Leader，并把 `(TermID=2, index=2)` 的日志记录备份到了 S2 上。到了时间点 (b) 时，S1 崩溃，S5 收到 S3、S4、S5 的选票，被选为 Leader，并从客户端处接收到日志记录 `(TermID=3, index=2)`。在时间点 (c) 时，S5 崩溃，S1 重启，被选举为 Leader，并继续将先前没有备份的日志记录 `(TermID=2, index=2)` 备份到其他节点上。即便此时 S1 顺利把该日志记录备份到集群大多数节点上，它仍然不能认为该日志记录已被安全提交。考虑此时 S1 崩溃，S5 将可以收到来自 S2、S3、S4、S5 的选票，成为 Leader（其最后一个日志记录的 Term ID 是 3，大于 2），进入情形 (d)：此时 S5 会继续把日志记录 `(TermID=3, index=2)` 备份到其他节点上，覆盖掉原本已经备份至大多数节点的日志记录 `(TermID=2, index=2)`。然而，如果在时间点 (c) S1 成为 Leader 后，同样将当前 Term 的最新日志记录 `(TermID=4, index=3)` 备份出去并提交，就会进入情形 (e)，此时 S5 便无法再被选举为 Leader。因此，解决该问题的关键在于在备份旧 Term 的日志时也要把当前 Term 最新的日志一并分发出去。

由此，Raft 只会在备份当前 Term 的日志记录时才会通过计数的方式来判断该日志记录是否已被提交；一旦该日志记录完成   提交，根据前面提及的 Log Matching 性质，Leader 就能得出之前的日志记录也已被提交。由此，我们便实现了前面提及的 Leader Completeness 性质。文中 5.4.3 节有完整的证明过程，感兴趣的读者可自行查阅。

证得前面 4 条性质后，最后一条 State Machine Safety 性质也可证得：当节点将日志记录应用于其上层状态机时，该日志记录及其之前的所有日志记录必然已经提交。某些节点执行命令的进度可能落后，我们考虑所有节点目前已执行日志记录的 index 值的最小值：Log Completeness 性质保证了未来的所有 Leader 都会持有该日志记录，因此在之后的 Term 中其他节点应用位于该 index 处的日志记录时，该日志记录保存的必然是相同的命令。由此，上层状态机只要按照 Raft 日志记录的 index 值顺序执行命令即可安全完成状态备份。

#### 5.8 时序要求

为了提供合理的可用性，集群仍需满足一定的时序要求，具体如下：
$$
broadcastTime≪electionTimeout≪MTBF
$$
其中 `broadcastTime` 即一个节点并发地发送 RPC 请求至集群中其他节点并接收请求的平均耗时；`electionTimeout` 即节点的选举超时时间；MTBF即单个节点每次失效的平均间隔时间（Mean Time Between Failures）。

上述的不等式要求，`broadcastTime` 要小于 `electionTimeout`一个数量级，以确保正常 Leader 心跳间隔不会导致 Follower 超时并发起选举；同时考虑到 electionTimeout会随机选出，该不等式还能确保 Leader 选举时平局局面不会频繁出现。除外，`electionTimeout`也应比 MTBF小几个数量级，考虑到系统会在 Leader 失效时停止服务，而这样的情况不应当频繁出现。

在这个不等式中，`broadcastTime` 及 `MTBF`由集群架构所决定，`electionTimeout` 则可由运维人员自行配置。

#### 5.9 Candidate 与 Follower 失效

目前来讲我们讨论都是 Leader 失效的问题。对于 Candidate 和 Follower 而言，它们分别是 RequestVote 和 AppendEntries RPC 调用的接收方：当 Candidate 或 Follower 崩溃后，RPC 调用会失败；Raft RPC 失败时会不断重试 RPC，直至 RPC 成功；除外，RPC 调用也有可能已经生效，但接收方在响应前就已失效，为此 Raft 保证 RPC 的幂等性，在节点重启后收到重复的 RPC 调用也不会有所影响。

#### 5.10 集群成员变更

直到目前为止，我们的讨论都假设集群的成员配置是一成不变的，然而这在系统的正常运维中是不常见的：系统总是可能需要做出变更，例如移除一些节点或增加一些节点。

当然，集群可以被全部关闭后，调整配置文件，再全部重启，这样也能完成集群配置变更，但这样会导致系统出现一段时间的不可用。而 Raft 则引入了额外的机制来允许集群在运行中变更自己的成员配置。

在进行配置变更时，直接从旧配置切换至新配置是不可行的，源于不同的节点不可能原子地完成配置切换，而这之间可能会有一些时间间隙使得集群存在两个不同的“大多数”。

![GFS集群架构](PIC/Lec5/configuration-change.png)

如上图所示，集群逐渐地从旧配置切换至新配置，那么在箭头标记的位置就出现了两个不同的“大多数”：S1、S2 构成$C_{old}$ 的大多数，S3、S4、S5 构成 $C_{new}$ 的大多数。在这一时间间隔内，处于两个配置的节点可能会选出各自的 Leader，引入 Split-Brain 问题。问题的关键在于，在这段时间间隔中，$C_{old}$ 和 $C_{new}$ 都能够独立地做出决定。

为了解决这个问题，Raft 采用二阶段的方式来完成配置切换：在 $C_{old}$ 和 $C_{new}$ 之间，引入一个被称为 Joint Consensus 的特殊配置 $C_{old,new}$作为迁移状态。该配置有如下性质：

- 日志记录会被备份到 $C_{old}$ 及 $C_{new}$的节点上
- 两份配置中的任意机器都能成为 Leader
- 选举或提交日志记录要求得到来自 $C_{old}$和 $C_{new}$的两个不同的“大多数”的同意

![GFS集群架构](PIC/Lec5/configuration-change-sequence.png)

上图显示了配置切换的时序，其中可以看到不存在$C_{old}$ 和 $C_{new}$ 都能独立作出决定的时间段。

切换时，Leader 会创建特殊的配置切换日志，并利用先前提到的日志备份机制通知其他节点进行配置切换。对于这种特殊的配置切换日志，节点在接收到时就会立刻切换配置，不会等待日志提交，因此 Leader 会首先进入 $C_{old,new}$ , 配置，同时运用这份配置来判断配置切换的日志是否成功提交。如此，如果 Leader 在完成提交这份日志之前崩溃，新的 Leader 只会处于 $C_{old}$ 或$C_{old,new}$配置，如此一来在该日志记录完成提交前，$C_{new}$便无法独立做出决定。

在 $C_{old,new}$的配置变更日志完成提交后，$C_{old}$便也不能独立做出决定了，且 Leader Completeness 性质保证了此时选举出的 Leader 必然处于 $C_{old,new}$ 配置。此时，Leader 就能开始重复上述过程，切换到 $C_{new}$配置。在 $C_{new}$ 配置日志完成提交后，这个过程中被移出集群的节点就能顺利关闭了。

除此以外，我们仍有三个问题需要去解决。

首先，配置变更可能会引入新的节点，这些节点不包含之前的日志记录，完成日志备份可能会需要较长的时间，而这段时间可能导致集群无法提交日志，引入一段时间的服务不可用。为此，Raft 在节点变更配置之前还引入了一个额外的阶段：此时节点会以不投票成员的形式加入集群，开始备份日志，Leader 在计算“大多数”时也不会考虑它们；等到它们完成备份后，它们就能回到正常状态，完成配置切换。

此外，集群的 Leader 有可能不属于$C_{new}$。在这种情况下，Leader 在完成 $C_{new}$ 的配置变更日志提交后才能变更自己的配置并关闭。也就是说，在 Leader 提交 $C_{new}$ 的日志时，那段时间里它会需要管理一个不包含自己的集群：它会把日志记录备份出去，但不会把自己算入“大多数”。直到 $C_{new}$日志完成提交，$C_{new}$才能够独立做出决定，才能够在原 Leader 降级后在 $C_{new}$ 集群中选出新的 Leader；在那之前，来自 $C_{old}$ 的节点有可能被选为 Leader。

最后，那些从集群中被移除出去的节点可能会在配置切换完成后干扰新集群的运行。这些节点不会再接收到 Leader 的心跳，于是它们就会超时并发起选举。这时它们会发起 RequestVote RPC 调用，其中包含新的 Term ID，而这可能导致新的 Leader 自动降级为 Follower，导致服务不可用。最终新集群会选出一个新的 Leader，但被移除的节点依旧不会接收到心跳信息，它们会再次超时，再次发起选举，如此循环往复。

为解决此问题，节点在其“确信” Leader 仍存活时会拒绝 RequestVote RPC 调用：如果距离节点上一次接收到 Leader 心跳信息过去的时间小于 Election Timeout 的最小值，那么节点便会“确信” Leader 仍然存活。考虑前面提到的时序要求，这确实能够在大多数情况下避免该问题。

#### 5.11 日志压缩

#### 5.12 客户端交互



### Lecure 6 Fault Tolerance Raft Part1

### Lecure 7 Fault Tolerance Raft Part2 

### Lecure 8 Zookeeper

### Lecure 9 More Replication CRAQ

### Lecure 10 Cloud Replication DB Aurora

### Lecure 11 Cache Consistency Frangipani

### Lecure 12  Distributed  Transaction

### Lecure 13 Spanner

### Lecure 14 Optimistic Concurrecny Control

### Lecure 15 Big Data Spark

### Lecure 16 Cache Consistence Memcached at Facebook

### Lecure 17 COPS Causal Consistency

### Lecure 18 Fork Consistency Certificate Transparency

### Lecure 19 Bitcoin

### Lecure 20 BlockStack