离线安装需使用本地源或者直接挂载安装镜像。操作如下：

```
[root@localhost ~] rm -rf /etc/yum.repos.d/*      
[root@localhost ~] vi /etc/yum.repos.d/rhel7.repo

[rhel7-yum]
name=rhel7-source
baseurl=file:///mnt
enabled=1
gpgcheck=0


# yum clean all   
# yum list
```
挂载安装盘：
```shell
mount rhel-server-7.4-x86_64-dvd.iso -o loop /mnt
```

后面就可以正常安装软件了，例如装`gcc`，`yum install gcc`即可。最后卸载iso盘就可以了```umount /mnt/```。