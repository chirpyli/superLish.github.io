---
title: 网络错误:Destination_unreachable:Host_administratively_prohibited
date: 2016-05-06 13:25:00 +0800
categories: [CS, Network]
---



### 问题描述：
当其他主机向本地虚拟机中运行的服务程序发送数据时，服务端无法收到数据，wireshark抓包分析后，发现错误提示信息：`Destination unreachable (Host administratively prohibited)`。意思是：目的主机被强制禁止。基本可以断定是防火墙的问题，因为如果是目的主机不存在的话，报的错误是：`Destination Host Unreachable`，明显，目的主机存在但是包被目的主机主动过滤掉了，什么会将网络数据包过滤掉呢，最常想到的就是防火墙了。

![image](/assets/img/network/ICMP目的不可达主机禁止.png)

所以解决办法就是更改防火墙的配置或者直接关闭防火墙，因为我是与自己本地虚拟机进行通信，直接关闭防火墙就好了。
### 解决办法：
关闭防火墙。

在Ubuntu环境中可执行如下命令(其实关闭防火墙一定程度上就等于允许所有包通过)：
```bash
sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT
sudo iptables -F
```

问题解决。