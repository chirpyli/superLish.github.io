---
title: 网络错误:Destination_unreachable:Host_administratively_prohibited
date: 2016-05-06 13:25:00 +0800
categories: [CS, Network]
---



### 问题描述：
当其他主机向本地虚拟机中运行的服务程序发送数据时，服务端无法收到数据，wireshark抓包分析后，发现错误提示信息：`Destination unreachable (Host administratively prohibited)`。意思是：目的主机被强制禁止。基本可以断定是防火墙的问题。

![在这里插入图片描述](/assets/img/network/ICMP目的不可达主机禁止.png)


### 解决办法：
关闭防火墙。

在Ubuntu环境中可执行如下命令(其实关闭防火墙一定程度上就等于允许所有包通过)：
```
sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT
sudo iptables -F
```

问题解决。