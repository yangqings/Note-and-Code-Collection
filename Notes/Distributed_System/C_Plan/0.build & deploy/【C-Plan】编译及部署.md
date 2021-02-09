# 【C-Plan】编译及部署

## 一、编译

基于`curvebuild`镜像，拉取docker镜像并启动

```bash
docker pull opencurve/curvebuild:centos8
docker run -it opencurve/curvebuild:centos8 /bin/bash
```

遇到无法联网问题，加上--net=host

```bash
docker run --net=host -it opencurve/curvebuild:centos8 /bin/bash
```

编译和打包顺利，没有遇到问题：

<div align=center>
    <img src="image/0 curve build.png" width = "80%">
</div>

<div align=center>
    <img src="image/0 curve build1.png" width = "90%">
</div>

<div align=center>
    <img src="image/0 打包成功.png" width = "90%">
</div>

## 二、单机部署

基于`curveintegration`镜像

#### 拉取并启动镜像

```bash
docker run --cap-add=ALL -v /dev:/dev -v /lib/modules:/lib/modules --privileged -it opencurve/curveintegration:centos8 /bin/bash
```

容器内无法联网，加上`--net=host`，重新 `docker run`

```bash
docker run --net=host --cap-add=ALL -v /dev:/dev -v /lib/modules:/lib/modules --privileged -it opencurve/curveintegration:centos8 /bin/bash
```

#### 获取tar并解压

按步骤进行

#### 执行单机部署

部署集群并启动服务

```bash
ansible-playbook -i server.ini deploy_curve.yml
```

执行命令查看当前集群状态

```bash
curve_ops_tool status
```

<div align=center>
    <img src="image/1 Chunkserver status.png" width = "100%">
</div>

```bash
ansible-playbook -i client.ini deploy_nebd.yml
ansible-playbook -i client.ini deploy_nbd.yml
ansible-playbook -i client.ini deploy_curve_sdk.yml
```

前几次部署尝试安装NBD包一直遇到报错，原因是第一次添加nbd模块时权限不足，感谢前面的@taohansi同学提供的解决办法。

#### 单机部署验证

<div align=center>
    <img src="image/2 创建curve卷.png" width = "100%">
</div>

可以看到nbd0卷