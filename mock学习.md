# mock学习

## 开始步骤

- 要使用mock的所有用户都必须添加到mock组。 

  ```bash
  usermod -a -G mock [User name]
  ```

  -  要使此更改生效，您必须注销并重新登录，或者运行命令 

    ```bash
    newgrp -
    ```

  配置文件位于/etc/ mock中。Mock版本0.8.0和更高版本缓存下载的rpm包(通过yum_cache插件)，这大大加快了后续构建的速度。尽管如此，您可能希望更改默认配置以指向本地存储库以加速构建(参见下面的注释)。 

   默认情况下，构建是在/ var / lib / mock中完成的，因此请确保您有空间。 从模拟0.8.0及更高版本开始，您可以通过**basedir** 配置选项进行更改。 

## 插件

###  [bind_mount](https://github.com/rpm-software-management/mock/wiki/Plugin-BindMount) 

- bind mountpoints inside the chroot

### [ccache](https://github.com/rpm-software-management/mock/wiki/Plugin-CCache) 

- compiler cache plugin

###  [chroot_scan](https://github.com/rpm-software-management/mock/wiki/Plugin-ChrootScan) 

- allows you to retrieve build artifacts from buildroot (e.g. additional logs, coredumps)

###  [compress_logs](https://github.com/rpm-software-management/mock/wiki/Plugin-CompressLogs) 

- compress logs

###  [hw_info](https://github.com/rpm-software-management/mock/wiki/Plugin-HwInfo) 

- prints HW information of builder

###  [lvm_root](https://github.com/rpm-software-management/mock/wiki/Plugin-LvmRoot) 

- caching buildroots using LVM

###  [mount](https://github.com/rpm-software-management/mock/wiki/Plugin-Mount) 

- allows you to mount directories into chroot

###  [overlayfs](https://github.com/rpm-software-management/mock/wiki/Plugin-Overlayfs) 

- plugin implementing snapshot functionality (similary to lvm_root)

###  [package_state](https://github.com/rpm-software-management/mock/wiki/Plugin-PackageState) 

- dumps list of available and installed packages

###  [pm_request](https://github.com/rpm-software-management/mock/wiki/Plugin-PMRequest) 

- executes package manager commands requested by processes running in the chroot

###  [procenv](https://github.com/rpm-software-management/mock/wiki/Plugin-ProcEnv) 

- dumps the build process runtime within the chroot.

###  [root_cache](https://github.com/rpm-software-management/mock/wiki/Plugin-RootCache) 

- cache buildroots (as tar file)

###  [scm](https://github.com/rpm-software-management/mock/wiki/Plugin-Scm) 

- SCM integration module - builds directly from Git or Svn

###  [selinux](https://github.com/rpm-software-management/mock/wiki/Plugin-SELinux) 

- on SELinux enabled box, this plugin will pretend, that SELinux is disabled in build environment

###  [sign](https://github.com/rpm-software-management/mock/wiki/Plugin-Sign) 

- call command on the produced rpm

###  [tmpfs](https://github.com/rpm-software-management/mock/wiki/Plugin-Tmpfs) 

- mount buildroot directory as tmpfs

###  [yum_cache](https://github.com/rpm-software-management/mock/wiki/Plugin-YumCache) 

- mount `/var/cache/yum` of your host machine to chroot



## mock 选项： 

- --rebuild：重建指定 SRPM
- --buildsrpm：从 spec (--spec ...) 和源码 (--sources ...) 或从 SCM 构建 SRPM
- --shell：在 chroot 内以交互方式运行指定命令。默认命令：/bin/sh
- --chroot：在 chroot 内以非交互方式运行指定命令
- --clean：彻底删除指定 chroot
- --scrub=[all|chroot|cache|root-cache|c-cache|yum-cache]：彻底删除指定 chroot 或缓存目录或所有 chroot 和缓存
- --init：初始化 chroot，不执行构建
- --installdeps：为指定 SRPM 安装编译依赖
- -i, --install：使用包管理安装软件包
- --update：使用包管理更新已安装软件包
- --remove：使用包管理删除软件包
- --orphanskill：杀死指定 buildroot 的所有进程
- --copyin：向指定 chroot 拷贝文件
- --copyout：从指定 chroot 拷贝文件
- --pm-cmd：执行包管理命令 (yum 或 dnf)
- --yum-cmd：执行 yum 包管理命令
- --dnf-cmd：执行 dnf 包管理命令
- --snapshot：使用指定名称创建 LVM 快照
- --remove-snapshot：删除指定 LVM 快照
- --rollback-to：回滚到指定快照
- --umount：卸载 buildroot，如果它已从独立设备挂载 (LVM)
- --mount：挂载 buildroot，如果它已从独立设备挂载 (LVM)
- -r CONFIG, --root=CONFIG：chroot 配置文件名或路径。路径以 .cfg 结尾，否则查找配置目录。默认：default
- --offline：激活 'offline' 模式
- -n, --no-clean：构建前不清理 chroot
- --cleanup-after：构建后清理 chroot。与 --resultdir 同时使用。仅 'rebuild' 时激活
- --no-cleanup-after：构建后不清理 chroot。如果启用自动清理，使用此选项关闭
- --cache-alterations：更改 chroot (即--install) 后重建根缓存。使用 tmpfs 插件时有用
- --nocheck：通过 --nocheck 选项使 rpmbuild 跳过 'make check' 测试
- --arch=ARCH：调用 personality()，告诉内核模拟该系统架构
- --target=RPMBUILD_ARCH：传递给 rpmbuild 作为编译目标架构
- -D 'MACRO EXPR', --define='MACRO EXPR'：定义 rpm 宏 (可多次指定)
- --macro-file=MACROFILE：使用预定义 rpm 宏文件
- --with=option：为构建启用配置选项 (可多次指定)
- --without=option：为构建禁用配置选项 (可多次指定)
- --resultdir=RESULTDIR：保存构建结果的目录
- --rootdir=ROOTDIR：chroot 根目录
- --uniqueext=UNIQUEEXT：设置唯一扩展名 (unique extension)，追加至 buildroot 目录名
- --configdir=CONFIGDIR：更改配置文件目录
- --rpmbuild_timeout=RPMBUILD_TIMEOUT：设置 rpmbuild 任务超时时间
- --unpriv：使用 --chroot 时，在运行命令前放弃特权
- --cwd=DIR：使用 --chroot 时，运行命令前切换至指定目录 (相对于 chroot 环境)
- --spec=SPEC：指定 spec 文件用于构建 SRPM (仅用于 --buildsrpm)
- --sources=SOURCES：指定源 (文件/目录) 用于构建 SRPM (仅用于 --buildsrpm)
- --symlink-dereference：跟随软链接 (仅用于 --buildsrpm)
- --short-circuit=SHORT_CIRCUIT：传递 short-circuit 选项给 rpmbuild 跳过已完成的阶段。警告：不可用于生成软件包。暗含 --no-clean 选项。有效选项：build, install, binary
- --rpmbuild-opts=RPMBUILD_OPTS：指定额外 rpmbuild 选项
- --enablerepo=[repo]：使用 enablerepo 选项启用源
- --disablerepo=[repo]：使用 disablerepo 选项禁用源
- --old-chroot：使用旧 chroot 代替 systemd-nspawn
- --new-chroot：使用新 chroot (systemd-nspawn)
- --postinstall：在构建后，尝试在同一个 buildroot 安装软件包
- -v, --verbose：详细信息
- -q, --quiet：安静模式
- --trace：启用内部 mock 跟踪输出
- --enable-plugin=ENABLED_PLUGINS：启用插件。可用插件： ['tmpfs', 'root_cache',  'yum_cache', 'bind_mount', 'ccache', 'selinux', 'package_state',  'chroot_scan', 'lvm_root', 'compress_logs', 'sign', 'pm_request']
- --disable-plugin=DISABLED_PLUGINS：禁用插件。可用插件： ['tmpfs', 'root_cache', 'yum_cache', 'bind_mount', 'ccache', 'selinux', 'package_state',  'chroot_scan', 'lvm_root', 'compress_logs', 'sign', 'pm_request']
- --plugin-option=PLUGIN:KEY=VALUE：定义插件选项 (可多次指定)
- -p, --print-root-path：打印 chroot 根路径
- -l, --list-snapshots：列出 LVM 快照与 buildroot 的关联
- --scm-enable：从 SCM 库构建
- --scm-option=SCM_OPTS：定义 SCM 选项 (可多次指定)
- --yum：使用 yum 包管理
- --dnf：使用 dnf 包管理