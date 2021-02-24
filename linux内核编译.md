## **linux 系统体系结构：**

![img](E:\bak\笔记-for-git\图片\1102171-20170309220251547-1537537668.jpg)

**用户空间(用户模式)转到内核空间(系统模式)方法：**
·系统调用
·硬件中断

**linux kernel 体系结构：**

![img](E:\bak\笔记-for-git\图片\kernel体系结构.jpg)

 

**虚拟文件系统VFS:**
VFS(虚拟文件系统)隐藏各种文件系统的具体细节，为文件操作提供统一的接口

------

## **Linux内核源代码结构**

linux内核下载www.kernel.org
**目录结构:**
解压linux kernel tar后目录
	·arch:根据cpu体系结构不同而分的代码
	·block:部分块设备驱动程序
	·crypto:加密，压缩，CRC校验算法
	·documentation:内核文档
	·drivers:设备驱动程序
	·fs(虚拟文件系统vfs):文件系统
	·include:内核所需的头文件，(与平台无关的头文件在include/linux中)
	·lib:库文件代码(与平台相关的)
	·mm:实现内存管理，与硬件体系结构无关的(与硬件体系结构相关的在arch中)
	·net:网络协议的代码
	·samples:一些内核编程的范例
	·scripts:配置内核的脚本
	·security:SElinux的模块
	·sound:音频设备的驱动程序
	·usr:cpio命令实现，用于制作根文件系统的命令(文件系统与内核放到一块的命令)
	·virt:内核虚拟机

------

## **Linux内核配置与编译**

**清理文件(在linux源码根目录):**
	·make clean:只清理所有产生的文件
	·make mrproper:清理所有产生的文件与config配置文件
	·make distclean:清理所有产生的文件与config配置文件，并且编辑过的与补丁文件
↓
**配置(收集硬件信息如cpu型号，网卡等...):**
	·make config:基于文本模式的交互配置
	·make menuconfig:基于文本模式的菜单模式(推荐使用)
	·make oldconfig:使用已有的.config,但会询问新增的配置项
	·make xconfig:图形化的配置(需要安装图形化系统)
**配置方法：**

1)与平台相关的配置
	make  xxxxx_defconfig

2)使用make menuconfig操作方法：
	1>按y:编译>连接>镜像文件
	2>按m:编译
	3>按n:什么都不做
	4>按"空格键":y,n轮换
	配置完并保存后会在linux源码根目录下生成一个.config文件

​	选项说明参加：https://blog.csdn.net/liao20081228/article/details/81389813

3)利用已有的配置文件模板(.config)
	1>linux源码根目录/arch/<cpu架构>/configs/<具体某一的CPU文件>，把里面对应的文件copy并改名为.config		至linux源码根目录下
	2>利用当前运行已有的文件(要用ls /boot/ -a查看)把/boot/config-\`uname  -r`拷贝并改名为.config至linux源码		根目录下执行以上操作就可以用make menuconfig在拷贝.config文件上面修改文件了
↓
**编译内核:**
1)make vmlinuz
		注意：在把.config配置文件cp到根目录编译内核前，必须进入make menuconfig并保存退出(否则生不了效)
↓
**编译并安装模块:**
1)编译内核模块:make modules
2)安装内核模块:make modules_install INSTALL_MOD_PATH=/lib/modules
	更换本机器内核:将编译好的内核模块从内核源码目录copy至/lib/modules下
3)制作initramdisk
	/bin/kernel-install add 4.19.90-5.AXS7.mips64el /boot/vmlinuz-4.19.90-5.AXS7.mips64el