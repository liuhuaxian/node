###  1.CentOS-7-x86_64-DVD-1708.iso安装树介绍


     我们从Centos7的官方网站下载CentOS-7-x86_64-DVD-1708.iso的镜像，使用相关的解压缩工具，便可以得到下图中的目录树结构。iso中有一个可引导的系统，我们称他为LiveOS，这个操作系统可以为我们在指定的存储设备上安装一个Centos7操作系统，也可以对出现问题的Centos7操作系统进行修复，还有一些我们自己yy的功能，说白了LiveOS作为一个操作系统同样需要具有bootloader、内核、initrd、rootfs等来引导运行

 ![p](图片\watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTI1NzAxMDU=,size_16,color_FFFFFF,t_70)

> 注意：可以忽略各个目录下的TRANS.TBL，这些文件记录了该目录的文件类型和文件名。再者下述所提到的bootloader、内核、rootfs等非明确指出，皆为LiveOS本身组建

- [BOOT]

  :这些目录实际上并不存在于ISO中。如果您烧录ISO，您将看不到这些目录。这个目录是解压软件生成的 

  - **1-Boot-NoEmul.img**:isolinux/isolinux.bin的前2048字节
  - **2-Boot-NoEmul.img**

- EFI目录：某些文章中所说的EFI分区，该目录中的文件用于基于EFI的系统引导。 

  - BOOT
    - **BOOTIA32.EFI、BOOTX64.EFI、grubia32.efi、grubx64.efi、mmia32.efi、mmx64.efi**:EFI模式下的bootloader，EFI固件找到EFI目录所在的分区（EFI启动涉及到一个写入到 firmware中的bootloader, EFI并不把bootloader放置在 MBR 中，firmware 知道如何读取分区表以及  FAT 的文件格式。EFI 所在的分区是用 FAT 格式格式化的特定分区，其中包含 bootloader, 该bootloader 是 EFI  可执行程序），然后加载运行这个分区下的EFI/Boot/xxx.efi
    - **grub.cfg**：EFI模式引导下的bootloarder配置文件（* 可以进行修改进行定制 *）
    - **fonts**：字体相关

- **Packages目录**：Centos7所用的rpm包（*内核、glibc库、第三方库、软件等*）

- repodata目录

  ： 

  - **repomd.xml**:记录了Centos7软件组的软件信息：最小化安装、图形化安装、服务器配置安装等（*可以定制所要安装的软件内容*）

- **TRANS.TBL文件**：记录当前目录的列表，主要是为了长文件名称。 （用mkisofs重新制作iso镜像时，使用-T参数重新生成）

- **.discinfo**：安装介质的识别信息。

- **.treeinfo**：记录不同安装方式安装程序所在的目录结构

- images目录

  - **efiboot.img**：解压后为前面EFI目录中的内容(UEFI模式下的bootloader和配置文件)
  - **pxeboot目录**：里面有EFI模式下的内核（**vmlinuz**）及RAM镜像(**initrd.img**)

- isolinux目录

  - **isolinux.bin**：Iisolinux是Linux/i386的bootloarder，它在“无仿真（*no emulation*）”模式下运行ISO 9660/El Torito CD-ROMs。这避免了创建空间有限(用于“软盘模拟（*floppy emulation*）”)或兼容性问题(用于“*硬盘模拟（hard disk emulation）*”)的“模拟磁盘映像（*emulation disk imag*）”。[isolinux.bin说明](https://www.syslinux.org/wiki/index.php?title=ISOLINUX#Can_I_boot_other_operating_systems_with_ISOLINUX.3F)
  - **isolinux.cfg**：传统bios下的bootloarder配置
  - **initrd.img**：传统bios引导模式下的RAM镜像(*initrd.img*)
  - **memtest**：内存测试模块
  - **grub.conf**：bootloarder配置（***这个和isolinux.cfg的关系还不明确***）
  - **splash.png**：bootloarder界面的背景图
  - **vmlinuz**：有传统bios引导模式下的内核（*vmlinuz*）
  - **boot.cat**：记录了引导目录信息
  - **boot.msg**：提示字符串

- LiveOS

  - **squashfs.img**：rootfs根文件系统（anaconda之类的软件都在里面）