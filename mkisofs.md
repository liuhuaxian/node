# `mkisofs `

实例

```sh
mkisofs -relaxed-filenames -allow-lowercase -graft-points -allow-multidot -pad -r -l -J -d -v -V "RedFlag_Asianux_Server_V4_2" -hide-rr-moved -o RedFlag-Asianux-Server-for-Loongson-V4.2-`date "+%y%m%d-%H%M%S"`.iso $1/
```

#### **-b** *eltorito_boot_image*

- Specifies the path and filename of the boot image to be used when making an El Torito bootable CD for x86 PCs. The pathname must be relative to the source path  specified to **genisoimage**. This option is required to make an El Torito bootable CD. The boot image must be exactly 1200 kB, 1440 kB or 2880 kB, and **genisoimage** will use this size when creating the output ISO9660 filesystem. The PC  BIOS will use the image to emulate a floppy disk, so the first 512-byte  sector should contain PC boot code. This will work, for example, if the  boot image is a LILO-based boot floppy.
- 指定制作用于x86 PC的El  Torito可引导CD时要使用的引导映像的路径和文件名。 路径名必须相对于genisoimage指定的源路径。 制作El  Torito可启动CD时需要此选项。 引导映像必须恰好是1200 kB，1440 kB或2880  kB，并且在创建输出ISO9660文件系统时，genisoimage将使用此大小。  PC  BIOS将使用该映像来模拟软盘，因此第一个512字节扇区应包含PC引导代码。 例如，如果启动映像是基于LILO的启动软盘，则它将起作用。

#### **-c** *boot_catalog*

- Specifies the path and  filename of the boot catalog, which is required for an El Torito  bootable CD. The pathname must be relative to the source path specified  to **genisoimage**. This file will be inserted into the output tree  and not created in the source filesystem, so be sure the specified  filename does not conflict with an existing file, or it will be  excluded. Usually a name like *boot.catalog* is chosen.
- 指定启动目录的路径和文件名，这是El Torito可启动CD所必需的。  路径名必须相对于genisoimage指定的源路径。  该文件将插入输出树中，而不在源文件系统中创建，因此请确保指定的文件名与现有文件不冲突，否则将被排除。  通常会选择类似boot.catalog的名称。

- If **-sort** has not been specified, the boot catalog sorted with low priority (+1)  to the beginning of the medium. If you don't like this, you need to  specify a sort weight of 0 for the boot catalog.

- 如果未指定-sort，则引导目录以低优先级（+1）排序到介质的开头。 如果您不喜欢这样，则需要为引导目录指定排序权重0。

#### **-v**

- Verbose execution. If given twice on the command line, extra debug information will be printed.

-  详细执行。 如果在命令行上给出两次，将打印更多的调试信息。 

#### **-U**

- Allows "untranslated" filenames, completely violating the ISO9660 standards described above. Enables the following flags: **-d -l -N -allow-leading-dots -relaxed-filenames** **-allow-lowercase -allow-multidot -no-iso-translate**. Allows more than one `.' character in the filename, as well as  mixed-case filenames. This is useful on HP-UX, where the built-in *cdfs* filesystem does not recognize any extensions. Use with extreme caution.

-  允许“未翻译”的文件名，完全违反了上述ISO9660标准。 启用以下标志：-d -l -N -allow-leading-dots  -relaxed-filenames -allow-lowercase -allow-multidot -no-iso-translate。  允许多个`。 文件名中的字符，以及大小写混合的文件名。 这在内置cdfs文件系统无法识别任何扩展名的HP-UX上很有用。 谨慎使用 

#### **-J**

- Generate Joliet directory records in addition to  regular ISO9660 filenames. This is primarily useful when the discs are  to be used on Windows machines. Joliet filenames are specified in  Unicode and each path component can be up to 64 Unicode characters long. Note that Joliet is not a standard --- only Microsoft Windows and Linux systems can read Joliet extensions. For greater portability, consider  using both Joliet and Rock Ridge extensions.
-  除常规ISO9660文件名外，还生成Joliet目录记录。 当要在Windows计算机上使用光盘时，这主要有用。   Joliet文件名以Unicode指定，每个路径部分的长度最多为64个Unicode字符。 请注意，Joliet不是标准的-仅Microsoft Windows和Linux系统可以读取Joliet扩展名。 为了提高便携性，请考虑同时使用Joliet和Rock Ridge扩展。 

#### **-R**

- Generate SUSP and RR records using the Rock Ridge protocol to further describe the files on the ISO9660 filesystem.
-  使用Rock Ridge协议生成SUSP和RR记录，以进一步描述ISO9660文件系统上的文件。 

#### **-T**

- Generate a file *TRANS.TBL* in each  directory on the CD-ROM, which can be used on non-Rock Ridge-capable  systems to help establish the correct filenames. There is also  information present in the file that indicates the major and minor  numbers for block and character devices, and each symlink has the name  of the link file given.
-  在CD-ROM上的每个目录中生成一个文件TRANS.TBL，可在非Rock Ridge功能的系统上使用该文件来帮助建立正确的文件名。 文件中还存在指示块和字符设备的主要和次要信息的信息，每个符号链接都有给定链接文件的名称。 

#### **-V** *volid*

- Specifies the volume ID (volume name or label) to be written into the master block. There is space for 32  characters. Equivalent to **VOLI** in the *.genisoimagerc* file. The volume ID is used as the mount point by the Solaris volume manager  and as a label assigned to a disc on various other platforms such as  Windows and Apple Mac OS.
-  指定要写入主块的卷ID（卷名或标签）。 可以容纳32个字符。 等效于.genisoimagerc文件中的VOLI。 卷ID被Solaris卷管理器用作安装点，并用作分配给Windows和Apple Mac OS等各种其他平台上的光盘的标签。 

#### **-no-emul-boot**

- Specifies that the boot image used to  create El Torito bootable CDs is a "no emulation" image. The system will load and execute this image without performing any disk emulation.
-  指定用于创建El Torito可启动CD的启动映像是“无仿真”映像。 系统将加载并执行该映像，而不执行任何磁盘仿真。 

#### **-boot-load-size** load_sectors

- Specifies the  number of "virtual" (512-byte) sectors to load in no-emulation mode. The default is to load the entire boot file. Some BIOSes may have problems  if this is not a multiple of 4.
- 指定要在非仿真模式下加载的“虚拟”（512字节）扇区的数量。 默认是加载整个启动文件。 如果不是4的倍数，则某些BIOS可能会出现问题。

#### **-boot-info-table**

- Specifies that a 56-byte table with information of the CD-ROM layout will be patched in at offset 8 in the  boot file. If this option is given, the boot file is *modified in the source filesystem*, so make a copy of this file if it cannot be easily regenerated! See the **EL TORITO BOOT INFO TABLE** section for a description of this table.

- 指定将在引导文件中的偏移量8处修补包含CD-ROM布局信息的56字节表。  如果指定了此选项，则会在源文件系统中修改启动文件，因此，如果无法轻松地重新生成该文件，请对其进行复制！ 有关此表的说明，请参见《 EL  TORITO BOOT INFO TABLE TABLE》。

## 示例

```sh
/usr/bin/mkisofs -v -U -J -R -T -b isolinux/isolinux.bin -c isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table -eltorito-alt-boot -e images/efiboot.img -no-emul-boot -V Asianux -o Redflag-asianux-8-Mini-DVD.iso /home/builder/work/ax8-iso/asianux

isolinux/isolinux.bin  ===>里面存放磁盘块的配置块，及首块的信息
isolinux/boot.cat      ===>里里是磁盘的日志信息
images/efiboot.img     ===》供efi方式安装系统使用。
```

```sh
[builder@localhost asianux]$ ls
BaseOS  EFI  images  isolinux  media.repo
[builder@localhost asianux]$ pwd
/home/builder/work/ax8-iso/asianux
[builder@localhost asianux]$ tree EFI/
EFI/
└── BOOT
    ├── BOOT.conf
    ├── BOOTIA32.EFI
    ├── BOOTX64.EFI
    ├── fonts
    │   └── unicode.pf2
    ├── grub.cfg
    ├── grubia32.efi
    ├── grubx64.efi
    ├── mmia32.efi
    └── mmx64.efi

[builder@localhost asianux]$ tree images/
images/
├── efiboot.img   ===>这文件解压开就是EFI文件夹中的所有内容
├── install.img
└── pxeboot
    ├── initrd.img
    └── vmlinuz
    
[builder@localhost asianux]$ tree isolinux/
isolinux/
├── boot.msg
├── grub.conf
├── initrd.img
├── isolinux.bin
├── isolinux.cfg
├── ldlinux.c32
├── libcom32.c32
├── libutil.c32
├── memtest
├── splash.png
├── vesamenu.c32
└── vmlinuz
```

EFI模式下对该处指示的引导

```sh
[builder@localhost BOOT]$ pwd
/home/builder/work/ax8-iso/asianux/EFI/BOOT

[builder@localhost BOOT]$ cat grub.cfg 
set default="1"

function load_video {
  insmod efi_gop
  insmod efi_uga
  insmod video_bochs
  insmod video_cirrus
  insmod all_video
}

load_video
set gfxpayload=keep
insmod gzio
insmod part_gpt
insmod ext2

set timeout=60
### END /etc/grub.d/00_header ###

search --no-floppy --set=root -l 'Asianux'

### BEGIN /etc/grub.d/10_linux ###
menuentry 'Install Asianux 8' --class fedora --class gnu-linux --class gnu --class os {
	linuxefi /images/pxeboot/vmlinuz inst.stage2=hd:LABEL=Asianux quiet
	initrdefi /images/pxeboot/initrd.img
}
menuentry 'Test this media & install Asianux 8' --class fedora --class gnu-linux --class gnu --class os {
	linuxefi /images/pxeboot/vmlinuz inst.stage2=hd:LABEL=Asianux rd.live.check quiet
	initrdefi /images/pxeboot/initrd.img
}
submenu 'Troubleshooting -->' {
	menuentry 'Install Asianux 8 in basic graphics mode' --class fedora --class gnu-linux --class gnu --class os {
		linuxefi /images/pxeboot/vmlinuz inst.stage2=hd:LABEL=Asianux nomodeset quiet
		initrdefi /images/pxeboot/initrd.img
	}
	menuentry 'Rescue a Asianux system' --class fedora --class gnu-linux --class gnu --class os {
		linuxefi /images/pxeboot/vmlinuz inst.stage2=hd:LABEL=Asianux rescue quiet
		initrdefi /images/pxeboot/initrd.img
	}
}
```

当为BISO模式的时候使用下面的引导的配置

```sh
[builder@localhost isolinux]$ pwd
/home/builder/work/ax8-iso/asianux/isolinux

[builder@localhost isolinux]$ ls
boot.msg  grub.conf  initrd.img  isolinux.bin  isolinux.cfg  ldlinux.c32  libcom32.c32  libutil.c32  memtest  splash.png  vesamenu.c32  vmlinuz

[builder@localhost isolinux]$ cat grub.conf 
#debug --graphics
default=1
splashimage=@SPLASHPATH@
timeout 60
hiddenmenu
title Install Asianux 8
	findiso
	kernel @KERNELPATH@ @ROOT@ quiet
	initrd @INITRDPATH@
title Test this media & install Asianux 8
	findiso
	kernel @KERNELPATH@ @ROOT@ rd.live.check quiet
	initrd @INITRDPATH@
```

详见：https://www.cnblogs.com/hgzero/p/13181868.html

