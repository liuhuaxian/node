# Centos8和7的区别（参照redhat）                

## 红帽RHEL8与RHEL7的区别

## 1.红帽RHEL8和RHEL7功能区别对比

####  1.1 默认的文件系统

 		RHEL8与RHEL7都是采用XFS

#### 1.2 RHEL8与RHEL7的内核版本分别是多少

 		关于内核版本，RHEL8和7的区别如下：
 			RHEL8采用4.18.0-x
 			RHEL7采用3.10-0-x

#### 1.3 内核代码名字

 		关于内核代码，RHEL8和7的区别如下：

​			RHEL8采用2019-05-07 (Kernel Version 4.18.0-80)
​			RHE7采用2014-06-09 (Kernel Version 3.10.0-123)

#### 1.4 标准/默认的仓库频道

 	关于仓库频道，RHEL8和7的区别如下：

​		RHEL8
 			Repo ID: rhel-8-for-x86_64-appstream-rpms
​			 Repo Name: Red Hat Enterprise Linux 8 for x86_64 - AppStream (RPMs)

​			Repo ID: rhel-8-for-x86_64-baseos-rpms
​			 Repo Name: Red Hat Enterprise Linux 8 for x86_64 - BaseOS (RPMs)

​		RHEL7
 			Repo ID: rhel-7-server-rpms
 			Repo Name: Red Hat Enterprise Linux 7 Server (RPMs)

#### 1.5 网络时间同步

​	 关于网络时间同步，RHEL8和7的区别如下：

​	RHEL8
​	 只使用Chronyd，不支持NTP部署。

​	RHEL7
 	Chronyd与NTP两者都支持

#### 1.6 支持最大的文件

​	 关于支持最大的文件，RHEL8和7的区别如下：

​	RHEL8
 	XFS文件系统支持的最大文件大小已从500 TiB增加到1024 TiB。
​	 (此最大文件大小仅适用于64位机器。Red Hat Enterprise Linux不支持32位机器上的XFS.)

​	RHEL7
​	 最大. (单独) 文件大小= 500TiB
​	 最大. 文件系统大小 = 500TiB

#### 1.7 软件包管理

​	 关于软件包管理，RHEL8和7的区别如下：

​	红帽8
​	 包管理由DNF (YUMv4)完成。

​		yum4基于DNF技术，yum4命令提供了与早期版本中使用的Yum v3的向后兼容性。yum命令只是到dnf
​		的一个符号链接。

​	红帽7
​		 yum基于3.0.x版本

#### 1.8 最大支持的内存

​	 关于最大支持的内存，RHEL8和7的区别如下：

​		红帽8
​			 24TB，64位架构

​		红帽7:
​			 只支持12TB

#### 1.9 默认的网络数据包过滤

​	 关于默认的网络数据包过滤，RHEL8和7的区别如下：

​		RHEL8使用nftables取代了iptables框架

​			nftables是默认的网络包过滤，它取代了以前的iptables框架。firewalld守护进程现在使用nftables作

​			为默认后端。

​			这将取代以前使用的“iptables”、“ip6tables”、“arptables”和“ebtables”工具。“nftables”确实为IPv4和
​			IPv6协议提供了一个单一的框架。

​		而RHEL7 firewalld守护进程使用iptables作为其默认后端。

#### 1.10 默认的数据库

 	关于默认的数据库，RHEL8和7的区别如下：

​		RHEL8默认支持的数据库：

​			MySQL 8.0
​			 MariaDB 10.3
​			 PostgreSQL 10 and PostgreSQL 9.6
​			 Redis 5.0
 			MariaDB是Red Hat Enterprise Linux 7中MySQL的默认实现

#### 1.11 支持的硬件架构

​	 关于支持的硬件架构，RHEL8和7的区别如下：

​		RHEL8支持以下硬件架构

​			 AMD and Intel 64-bit architectures
​			 The 64-bit ARM architecture
 			IBM Power Systems, Little Endian
​			 IBM Z
 	RHEL7支持以下硬件架构：

​			64-bit AMD
​		    64-bit Intel
​			 IBM POWER7
​			 IBM System z

#### 1.12 可供安装的ISO镜像类型

​	关于可供安装的ISO镜像类型，RHEL8和7的区别如下：

​		RHEL 8可以使用以下类型的ISO镜像安装:

​			 Binary(二进制) DVD ISO
​			 Boot ISO
​		在RHEL7中，可以使用以下可用的ISO镜像进行安装:

​				 Boot ISO
 				Binary(二进制) DVD ISO
​				 Supplementary(追加的) Binary DVD

#### 1.13 默认情况下的Cockpit web控制台的安装状态

​	 关于默认情况下的Cockpit web控制台的安装状态，RHEL8和7的区别如下：

​			在RHEL8中，
​				Cockpit是默认安装和可用的。这将在非最小模式下自动安装，并在防火墙中启用所需端
​				口。Cockpit提供了一个增强的框架，可以用来访问/编辑/更改许多系统设置。这提供了通过web接
​				口的访问。可以使用浏览器访问url地址http://:9090进行管理。

​			在RHEL7系统中，
​					Cockpit默认情况下没有安装，需要通过启用extra和optional存储库通道来安装。

#### 1.14 默认虚拟机管理

​		 关于默认虚拟机管理，RHEL8和7的区别如下：

​				在RHEL8系统中，默认情况下，它由Cockpit管理。如果需要，还可以安装virt-manager。

​				而在RHEL7系统中virt-manager将用于基于KVM的虚拟系统管理。

#### 1.15 RMP版本的改进

 关于RMP版本的改进，RHEL8和7的区别如下：

​		Red Hat Enterprise Linux 8是用RPM 4.14发布的。现在，RPM在开始安装之前验证整个包的内容。

​			这有很多改进，其中一些值得注意的功能是:

​			debuginfo包可以并行安装
​			 支持弱依赖关系
​			 支持丰富的或布尔依赖
​		 	支持封装文件超过4 GB的大小
​			 支持文件触发器
​			 构建在RHEL8上的包在压缩负载上使用一个新的SHA-256散列。

​		而Red Hat Enterprise Linux 7是用RPM 4.11发布的。在RHEL7上，RPM实用程序在解压时验证单个文件				的有效负载内容。

#### 1.16 CUPS日志

 	关于CUPS日志，RHEL8和7的区别如下：

​		RHEL8所有类型的CUPS日志都与来自其他程序的日志一起集中记录在systemd journald守护进程中。要		
​		访问CUPS日志，请使用“journalctl -u CUPS”命令。
 	   而RHEL7系统上，CUPS日志被存储中 /var/log/cups directory.

​		nobody用户替换nfsnobody
​		rhel8系统上，nobody和nfsnobody用户和组合并到nobodyID(65534)中。

​		在Red Hat Enterprise Linux 7中，有:

​				ID为99的nobody用户和组
​				 nfsnobody用户和组对的ID为65534，这也是默认的内核溢出ID。

####  1.17 默认版本的控制系统

 	关于默认版本的控制系统，RHEL8和7的区别如下：

​	RHEL 8提供以下版本控制系统:

​		 Git 2.18
​		 Mercurial 4.8
 		Subversion 1.10
​		 并发版本系统(CVS)和版本控制系统(RCS)在RHEL8中都不可用。

​	而Red Hat Enterprise Linux 7与三个最流行的开源修订控制系统一起发布:Git、SVN和CVS。

#### 1.18 编程语言版本

​	 关于编程语言版本，RHEL8和7的区别如下：

​		RHEL8新版本编程语言

​			 Python 3
​			 PHP 7.2
​			 Ruby 2.5
​			 Node.js 10
​	 而RHEL7支持以下编辑语言

​		 Python 2 ( 2.7.X)
​		 PHP 5.4
​		 Ruby 2.0.0

#### 1.19 关于容器技术的支持

​	 关于容器技术的支持，RHEL8和7的区别如下：

​		 Docker不包括在RHEL 8.0中。使用容器时，需要使用podman、buildah、skopeo和runc工具。
​		 podman工具已经作为一个完全支持的特性发布了。
​		 Docker和Docker Registry是Red Hat Enterprise Linux 7中的Extras订阅频道的一部分。

#### 1.20 开发工具支持

 	关于开发工具支持，RHEL8和7的区别如下：

​		RHEL 8提供OpenJDK 11、OpenJDK 8、IcedTea-Web和各种Java工具，如Ant、Maven或Scala。
​	    在RHEL7中，OpenJDK8用作默认的Java开发工具包(JDK)，而Java 8用作默认的Java版本。

#### 1.21 NFS配置对比

 关于NFS配置对比，RHEL8和7的区别如下：

​		RHEL8的NFS配置文件是/etc/ NFS .conf。
 	 	 当从RHEL7升级时，Red Hat Enterprise Linux 8尝试自动将所有选项从/etc/sysconfig/nfs转换
​			为/etc/nfs。并不再支持NFS / UDP。

​		而RHEL7中，默认的NFS配置文件是/etc/sysconfig/ NFS

#### 1.22 默认的显示服务器

 关于默认的显示服务器，RHEL8和7的区别如下：

​		在RHEL 8中，Gnome display Manager使用的默认显示服务器是Wayland。
​			 X.org服务器是RHEL 7中的默认显示服务器

### 2.RHEL8额外新功能新特性

####  	2.1 elevator内核命令行参数被废弃

​	 	早期的RHEL版本中使用了elevator内核命令行参数来设置所有设备的磁盘调度程序。在RHEL 8中，该参数被
​		弃用。上游Linux内核已经取消了对elevator参数的支持，但是出于兼容性的原因，RHEL 8中仍然可以使它。

#### 	2.2 网络脚本被废弃

​		在RHEL 8中，网络脚本在默认情况下不可用。有一个新版本的ifup和ifdown正在使用，这将需要
​		NetworkManager守护进程运行，并在后端使用nmcli。

​		如果需要早期的网络脚本，则必须安装“network-scripts”包。

#### 	2.3 新内核支持5级paging

 		在早期版本中，有4级分页实现，可以处理48/46位虚拟/物理地址，并且物理总线上限为64TB。在即将推出		 的Intel处理器中，这些限制已经扩展到57/52位的虚拟/物理内存寻址，具有128 PiB的虚拟地址空间和4 PB的
		物理内存容量。

#### 	2.4 Anaconda支持RHEL 8中的系统目标

​			以前，Anaconda没有向订阅管理器提供系统用途信息。在Red Hat Enterprise Linux 8.0中，您可以在安装
​			期间使用Anaconda的system purpose窗口或Kickstart的syspurpose命令设置系统的预期目标。

#### 	2.5 CodeReady Linux构建器仓库

 			有一个CodeReady Linux构建器存储库，可用于所有RHEL订阅。这为开发人员提供了额外的包。		
				CodeReady Linux构建器存储库中包含的包不支持生产使用。

#### 	2.6 改进版本的OpenSSH

 			OpenSSH的版本是7.8p1，与早期版本相比有很多改进。其中一些是:

​			不再支持SSH version 1.
 			默认不开启DNS支持.
 			最小可接受RSA密钥大小设置为1024位.
 			移除 'Blowfish', 'CAST', 'RC4' ciphers.
 			默认关闭DSA 公钥算法.

#### 	 2.7 RHEL8中不支持数字用户名和组名

 			useradd和groupadd命令不允许用户名和组名完全由数字字符组成。这是RHEL7中不支持的特性，现在
				RHEL8完全不支持它。

#### 	2.8 默认情况下，securetty现在是禁用的

 			默认情况下禁用了securetty PAM模块，并且从RHEL8中删除了/etc/securetty文件。

#### 	2.9 改进的TCP网络栈

 			RHEL 8拥有TCP网络栈版本4.18，可以提供更高的性能、更好的可伸缩性和更稳定的性能。性能得到了提
			高，特别是在繁忙的TCP服务器与高进入连接速率。

​			除了新的TCP栈之外，还有两种新的TCP拥塞算法。在大多数情况下，BBR和NV可以提供比cubic更低的延
​			迟和更好的吞吐量。

#### 	2.10 高可用性(HA)

 		在Red Hat Enterprise Linux 8中，pcs完全支持Corosync 3集群引擎和用于集群通信的Kronosnet (knet)网
		 络抽象层。无法将集群节点从RHEL7就地升级到RHEL8。

#### 	2.11 lvmlockd取代了clvmd

 		用于管理共享存储逻辑卷的clvmd已被删除，取而代之的是lvmlockd(lvm lock 守护进程)

### 镜像下载地址

 CentOS 8 下载：https://centos.org/download/