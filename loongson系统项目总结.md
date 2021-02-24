# 基于`loongson`系统移植问题

[TOC]

## 软件包编译阶段

#### 依赖问题

```bash
  =====降低qt5版本为5.9.2=====
qt5-qt3d-5.9.2-1.lns7.src.rpm
qt5-qtcanvas3d-5.9.2-1.lns7.src.rpm
qt5-qtconnectivity-5.9.2-1.lns7.src.rpm
qt5-qtdeclarative-5.9.2-1.lns7.1.loongnix.src.rpm
qt5-qtgraphicaleffects-5.9.2-1.lns7.src.rpm
qt5-qtlocation-5.9.2-1.lns7.src.rpm
qt5-qtmultimedia-5.9.2-1.lns7.src.rpm
qt5-qtquickcontrols2-5.9.2-1.lns7.src.rpm
qt5-qtquickcontrols-5.9.2-1.lns7.src.rpm
qt5-qtscript-5.9.2-1.lns7.src.rpm
qt5-qtsensors-5.9.2-1.lns7.src.rpm
qt5-qtserialbus-5.9.2-1.lns7.src.rpm
qt5-qttools-5.9.2-1.lns7.src.rpm
qt5-qttranslations-5.9.2-1.lns7.src.rpm
qt5-qtwayland-5.9.2-1.lns7.src.rpm
qt5-qtwebchannel-5.9.2-1.lns7.src.rpm
qt5-qtwebsockets-5.9.2-1.lns7.src.rpm

   =====使用qt5版本为5.97======
qt5-qt3d-5.9.7-1.lns7.src.rpm
qt5-qtcanvas3d-5.9.7-1.lns7.src.rpm
qt5-qtconnectivity-5.9.7-1.lns7.src.rpm
qt5-qtdeclarative-5.9.7-1.lns7.1.loongnix.src.rpm
qt5-qtenginio-1.6.2-2.lns7.src.rpm
qt5-qtgraphicaleffects-5.9.7-1.lns7.src.rpm
qt5-qtlocation-5.9.7-1.lns7.src.rpm
qt5-qtmultimedia-5.9.7-1.lns7.src.rpm
qt5-qtquickcontrols2-5.9.7-1.lns7.src.rpm
qt5-qtquickcontrols-5.9.7-1.lns7.src.rpm
qt5-qtscript-5.9.7-1.lns7.src.rpm
qt5-qtsensors-5.9.7-1.lns7.src.rpm
qt5-qtserialbus-5.9.7-1.lns7.src.rpm
qt5-qttools-5.9.7-1.lns7.src.rpm
qt5-qttranslations-5.9.7-1.lns7.src.rpm
qt5-qtwayland-5.9.7-1.lns7.src.rpm
qt5-qtwebchannel-5.9.7-1.lns7.src.rpm
qt5-qtwebsockets-5.9.7-1.lns7.src.rpm
=============================================================
openchange-2.3-3.lns7.src.rpm   ==>降低samba-common samba-devel samba-libs samba-pidl 为4.9.1-6
gnome-color-manager-3.28.0-1.lns7.src.rpm  ===>使用exiv2-libs-0.26的版本
```

#### 跳过check阶段的包

```bash
abrt-java-connector-1.0.6-12.lns7.1.loongnix.src.rpm       ===> no check
babel-0.9.6-8.lns7.src.rpm   ===> no check
bacula-9.4.3-2.lns7.src.rpm   ===> 注释spec文件中的 %ldconfig_scriptlets libs
gc-7.2d-7.lns7.src.rpm      ===>no check
geoclue-0.12.99-7.lns7.src.rpm    ===> 注释geoclue-0.12.99/docs/reference/Makefile.in 中的 @gtkdoc-mktmpl --module=$(DOC_MODULE) $(MKTMPL_OPTIONS)
gsl-1.15-13.lns7.src.rpm   ===>no check
guile-2.0.9-5.lns7.src.rpm  ===>no check
libglvnd-1.0.1-0.8.git5baa1e5.lns7.src.rpm   ===>no check
libkkc-0.3.1-9.lns7.src.rpm    ===>no check
penchange-2.3-3.lns7.src.rpm   ==>降低samba-common samba-devel samba-libs samba-pidl 为4.9.1-6
gnome-color-manager-3.28.0-1.lns7.src.rpm  ===>使用exiv2-libs-0.26的版本
libmemcached-1.0.16-5.lns7.src.rpm  ===>no check
liborcus-0.12.1-2.lns7.src.rpm      ===>no check
nss-3.44.0-4.lns7.src.rpm
nss-3.44.0-7.lns7.src.rpm
pcre-8.32-17.lns7.src.rpm
perl-DateTime-1.04-6.lns7.src.rpm
perl-IO-Socket-IP-0.21-5.lns7.src.rpm
perl-IO-Socket-SSL-1.94-7.lns7.src.rpm
perl-Perl4-CoreLibs-0.003-7.lns7.src.rpm
perl-TimeDate-2.30-2.lns7.src.rpm
perl-Time-Local-1.2300-2.lns7.src.rpm
python-2.7.5-86.lns7.1.loongnix.src.rpm
bacula-9.4.3-2.lns7.src.rpm   ===> 注释spec文件中的 %ldconfig_scriptlets libs
gc-7.2d-7.lns7.src.rpm      ===>no check
geoclue-0.12.99-7.lns7.src.rpm    ===> 注释geoclue-0.12.99/docs/reference/Makefile.in 中的 @gtkdoc-mktmpl --module=$(DOC_MODULE) $(MKTMPL_OPTIONS)
gsl-1.15-13.lns7.src.rpm   ===>no check
guile-2.0.9-5.lns7.src.rpm  ===>no check
libglvnd-1.0.1-0.8.git5baa1e5.lns7.src.rpm   ===>no check
libkkc-0.3.1-9.lns7.src.rpm    ===>no check
penchange-2.3-3.lns7.src.rpm   ==>降低samba-common samba-devel samba-libs samba-pidl 为4.9.1-6
gnome-color-manager-3.28.0-1.lns7.src.rpm  ===>使用exiv2-libs-0.26的版本
libmemcached-1.0.16-5.lns7.src.rpm  ===>no check
liborcus-0.12.1-2.lns7.src.rpm      ===>no check
nss-3.44.0-4.lns7.src.rpm
nss-3.44.0-7.lns7.src.rpm
pcre-8.32-17.lns7.src.rpm
perl-DateTime-1.04-6.lns7.src.rpm
perl-IO-Socket-IP-0.21-5.lns7.src.rpm
perl-IO-Socket-SSL-1.94-7.lns7.src.rpm
perl-Perl4-CoreLibs-0.003-7.lns7.src.rpm
perl-TimeDate-2.30-2.lns7.src.rpm
perl-Time-Local-1.2300-2.lns7.src.rpm
python-2.7.5-86.lns7.1.loongnix.src.rpm
python-2.7.5-88.lns7.1.loongnix.src.rpm
python-cherrypy-3.2.2-4.lns7.src.rpm
pytz-2016.10-2.lns7.src.rpm
satyr-0.13-15.lns7.src.rpm
strace-4.12-9.lns7.src.rpm
strace-4.24-4.lns7.src.rpm
vinagre-3.22.0-12.lns7.src.rpm
libsndfile-1.0.25-10.lns7.src.rpm
libsndfile-1.0.25-11.lns7.src.rpm
mariadb-5.5.64-1.lns7.src.rpm
mariadb-5.5.65-1.lns7.src.rpm
nbdkit-1.2.6-1.lns7.1.loongnix.src.rpm
libgexiv2-0.10.8-1.lns7.src.rpm
```

#### 其它问题

```bash
 ===nocheck 并且存在未打包的文件，将其打入qemu-kvm-common-ev包中===
qemu-kvm-ev-2.12.0-33.1.lns7.1.loongnix.src.rpm
qemu-kvm-ev-2.12.0-33.1.lns7.2.loongnix.src.rpm
qemu-kvm-ev-2.12.0-33.1.AXS7.3.loongnix.src.rpm
qemu-kvm-ev-2.12.0-33.1.lns7.4.loongnix.src.rpm


 ===nocheck并且存在未打包的文件，将其打入compat-openmpi16-devel包中===
openmpi-1.10.7-5.lns7.1.loongnix.src.rpm
openmpi-1.10.7-5.lns7.loongnix.src.rpm

===nocheck并且存在未打包的文件，将其打入自定义的libvirt-other-file包中===
libvirt-4.5.0-23.lns7.1.loongnix.src.rpm
libvirt-4.5.0-23.lns7.2.loongnix.src.rpm
libvirt-4.5.0-23.lns7.3.loongnix.src.rpm

clevis-7-8.lns7.src.rpm ==> 修改spec文件，详见其spec文件的install阶段

keepalived-1.3.5-6.lns7.src.rpm  ===>增加补丁，见源码包。
resteasy-base-3.0.6-4.lns7.src.rpm  ==>该jboss-servlet-2.5-api-1.0.1-5依赖包自己网上下载手动编译过的。
pcp-4.3.2-2.lns7.src.rpm  ===>依赖python3-devel，打包阶段文件找不到，手动添加，
ibus-m17n-1.3.4-13.lns7.src.rpm   ===>安装intltool-0.35.0-2的版本。
libguestfs-1.38.2-12.lns7.src.rpm  ===> 加上编译选项--noprep --nocheck
```

## `mkiso`阶段

#### 使用的`mkiso`脚本如下

```bash
#!/usr/bin/env bash

set -ex

RDIR=$(dirname $(readlink -f "$0"))
DATE=$(date +'%Y%m%d%H%M')

ARCH=${ARCH:-'mips64el'}
RPMSDIR=${RPMSDIR:-"${RDIR}/rpm-now"}
RELEASE=${RELEASE:-'loongson'}
DOCLEAN=${DOCLEAN:-'no'}
USERNAME=${USERNAME:-'root'}

ENFORCE=$(getenforce)
NAME='Asianux'
VERSION='7'
SP='8'
BUGURL='http://bugzilla.chinaredflag.cn'
DESTDIR="${RDIR}"
#MOUNTDIR="/media/cifs"
#CIFSDIR='/deve'
OUT_DIR="${DESTDIR}/iso"
CONFIG_DIR="${DESTDIR}/config"
OS_DIR="${DESTDIR}/${VERSION}/${ARCH}/os"
PKG_DIR="${OS_DIR}/Packages"
GRUB_DIR="${OS_DIR}/EFI/BOOT"
ISO_DIR="${DESTDIR}/${VERSION}/${ARCH}/iso"
LOG_DIR="${DESTDIR}/logs"
COMPS="${CONFIG_DIR}/mips64el-comps.xml"
CFG="${CONFIG_DIR}/asianux78.${ARCH}.cfg"
KS="${CONFIG_DIR}/ax78.mips64el.1.7.ks"
GRUB_CFG="${CONFIG_DIR}/grub.mips64el.cfg"
GPG_KEY="${CONFIG_DIR}/RPM-GPG-KEY-Asianux-7"
SYSTEM_CHK="${CONFIG_DIR}/system-chk"
SYSTEM_CHK_SRV="${CONFIG_DIR}/system-chk.service"
ANACONDA_HELPER="${CONFIG_DIR}/anaconda-helper"
#CIFSSRV='172.16.100.102'
#SEC='ntlm'
TEMPDIRS=("${DESTDIR}/${VERSION}" "$LOG_DIR" "${DESTDIR}/work" "./${NAME}" './ourtree')
PUNGI_ARGS=('--nosource' '--nodebuginfo' '--nohash' '--fulltree' '--isfinal' '--full-archlist' )
PUNGI_ARGS_NAME="--name=${NAME}"
PUNGI_ARGS_CUSTOM=(
  "--ver=${VERSION}"
  "--bugurl=${BUGURL}"
  "--config=${CFG}"
  "--destdir=${DESTDIR}"
)

function createrepo ()
{
  local _repo=$1
  test -d "$_repo"
  pushd "$_repo"
  command createrepo --update -g ${COMPS} -o "$_repo" "$_repo"
  popd

  return "$?"
}

function addrflic ()
{
  local _flag=1
  local _build_requires=('gcc' 'redflag-checkaxsn')

  for _pkg in ${_build_requires[@]}
  do
    if ! rpm -q "$_pkg"
    then
      echo "$_pkg" "not found,Please install it."
      _flag=0
    fi
  done

  if [ $_flag -eq 0 ]
  then
    echo "exit"
    exit 1
  fi

  local _SQUASHFS_IMG_DIR="${RDIR}/${VERSION}/${ARCH}/os/LiveOS/squashfs.img"
  local _SQUASHFS_DIR="${DESTDIR}/squashfs"
local _ROOTFS_DIR="${DESTDIR}/rootfs"
  local _SYSTEM_CHK_TARGET="${_ROOTFS_DIR}/usr/bin"
  local _SYSTEM_CHK_SRV_TARGET="${_ROOTFS_DIR}/usr/lib/systemd/system"
  local _ANACONDA_HELPER_TARGET="${_ROOTFS_DIR}/usr/lib/anaconda-runtime/"

  mkdir -p "$_ROOTFS_DIR"
  unsquashfs -d "$_SQUASHFS_DIR" "${_SQUASHFS_IMG_DIR}"
  mount -t ext4 "${_SQUASHFS_DIR}/LiveOS/rootfs.img" "$_ROOTFS_DIR"
#  gcc ${RDIR}/system-chk.c -o ${RDIR}/system-chk -lcheckaxsn -lglib-2.0
#  cp -v ${RDIR}/system-chk ${CONFIG_DIR}
  mkdir -p "$_SYSTEM_CHK_TARGET" "$_SYSTEM_CHK_SRV_TARGET"
  mkdir -p "$_ANACONDA_HELPER_TARGET"
  cp -v "$SYSTEM_CHK" "$_SYSTEM_CHK_TARGET"
  cp -v "$SYSTEM_CHK_SRV" "$_SYSTEM_CHK_SRV_TARGET"
  cp -v "${ANACONDA_HELPER}" "$_ANACONDA_HELPER_TARGET"
  umount "$_ROOTFS_DIR"

  rm -vf "${_SQUASHFS_IMG_DIR}"
  mksquashfs "$_SQUASHFS_DIR" "${_SQUASHFS_IMG_DIR}" -comp xz

  rm -rf "$_ROOTFS_DIR" "$_SQUASHFS_DIR"
  return $?
}

function makeiso ()
{
  local ISO_PATH="${ISO_DIR}/${NAME}-DVD-${ARCH}-${VERSION}.iso"

  if [[ 'x86_64' == "$ARCH" ]]
  then
    GRUB_DIR="${OS_DIR}/EFI/BOOT"
    PUNGI_ARGS_NAME="--name=${NAME}"
  fi
  sudo pungi -G "$PUNGI_ARGS_NAME" ${PUNGI_ARGS[@]} ${PUNGI_ARGS_CUSTOM[@]}
  #sudo pungi -C "$PUNGI_ARGS_NAME" ${PUNGI_ARGS[@]} ${PUNGI_ARGS_CUSTOM[@]}
  createrepo "$OS_DIR"
  sudo pungi -B "$PUNGI_ARGS_NAME" ${PUNGI_ARGS[@]} ${PUNGI_ARGS_CUSTOM[@]}
  install -Dvm 0644 "$GPG_KEY" "${OS_DIR}"
  install -Dvm 0400 "${GRUB_CFG}" "${GRUB_DIR}/grub.cfg"

#  if [[ 'x86_64' == "$ARCH"  ]]
#  then
    addrflic
#  fi
  sudo pungi -I "$PUNGI_ARGS_NAME" ${PUNGI_ARGS[@]} ${PUNGI_ARGS_CUSTOM[@]}


  mkdir -p "${OUT_DIR}"
  mv -v "${ISO_PATH}" \
        "${OUT_DIR}/${NAME}-${VERSION}.${SP}-${RELEASE}-${ARCH}-dvddisc-${DATE}.iso"
  mv -v "${LOG_DIR}/${ARCH}.log"  \
        "${OUT_DIR}/${NAME}-${VERSION}.${SP}-${RELEASE}-${ARCH}-dvddisc-${DATE}.iso.log"

  return "$?"
}

function clean ()
{
  for _dir in ${TEMPDIRS[@]}
  do
    if [[ -d "${_dir}" ]]
    then
      rm -rf "${_dir}"
    fi
  done

  return $?
}
{
  # This should run as root
  if [[ 0 -ne "$UID" ]]
  then
    exit 1
  fi

  if [[ 'x86_64' != "$ARCH" && 'aarch64' != "$ARCH" && 'mips64el' != "$ARCH" ]]
  then
    exit 1
  fi

  createrepo "$RPMSDIR"
  # Write config file (a ks in fact)
  ( echo "repo --name=${NAME}/${VERSION} --baseurl=file://${RPMSDIR}"
    echo
    cat "$KS"
  ) | tee "$CFG"


  clean && makeiso
  if [[ "$DOCLEAN" == 'yes' ]]
  then
    clean
  fi

  exit "$?"
}
```

#### 所需配置文件

```bash
[lhx@loongson-3a400 config]$ tree
.
├── ax78.mips64el.1.7.ks
├── mips64el-comps.xml
└── grub.mips64el.cfg
```

#### 执行脚本过程中遇到的问题

- 缺少依赖包
  - 寻找对应的rpm包。
- rpm包之间存在冲突
  - 删除冲的rpm包。

## 适配安装系统阶段

#### 更改的符合公司特色的安装包

- 更换具有公司特色的启动界面对应的修改的安装包为

  ```bash
  anaconda-21.48.22.147-1.AXS7.1.loongnix.src.rpm
  asianux-logos-7.6-6.axs7.6.noarch.rpm
  ```

- 移植火狐浏览器，对应的包为。

  ```bash
  asianux-indexhtml-7-5.axs7.1.src.rpm
  firefox-52.7.0-1.AXS7.1.src.rpm
  ```

- 移植系统注册程序对应的安装包名为

  ```bash
  redflag-checkaxsn
  rflic-devel-extra
  rflic-devel
  rflicmgr3
  ```

#### 安装系统过程中遇到的问题

##### 问题一：第一次安装系统时并重新启动，系统的无法找到license文件。导致系统无法启动。

- 解决方案。

  - 确定系统是否安装`centos-release`安装包，该包的`/usr/share/doc/xxxx-release/EULA`文件及是这个license文件。

    ```bash
    [lhx@loongson-3a400 rpm-now]$ rpm -qpl asianux-release-7-5.1804.axs7.mips64el.rpm 
    /etc/asianux-release
    /etc/asianux-release-upstream
    /etc/centos-release
    /etc/issue
    /etc/issue.net
    /etc/os-release
    /etc/pki/rpm-gpg
    /etc/pki/rpm-gpg/RPM-GPG-KEY-redflag-7
    /etc/redflag-release
    /etc/rpm/macros.dist
    /etc/system-release
    /etc/system-release-cpe
    /etc/yum.repos.d/redflag.repo
    /etc/yum/vars/infra
    /usr/lib/systemd/system-preset/85-display-manager.preset
    /usr/lib/systemd/system-preset/90-default.preset
    /usr/share/asianux-release/EULA
    /usr/share/centos-release
    /usr/share/doc/asianux-release/GPL
    /usr/share/doc/centos-release
    /usr/share/doc/redflag-release
    /usr/share/redflag-release
    ```

  - 确定该license文件的寻找路径，在initial-setup包中如下的位置记录了这个文件的寻找路径。

    ```c
    diff -uNr initial-setup-0.3.9.23__orig/initial_setup/gui/spokes/eula.py initial-setup-0.3.9.23/initial_setup/gui/spokes/eula.py
    --- initial-setup-0.3.9.23__orig/initial_setup/gui/spokes/eula.py       2015-01-20 17:13:54.000000000 +0000
    +++ initial-setup-0.3.9.23/initial_setup/gui/spokes/eula.py     2015-03-26 08:50:54.965877149 +0000
    @@ -51,7 +51,7 @@
                 log.error("no license found")
                 self._have_eula = False
                 self._eula_buffer.set_text(_("No license found. Please report this "
    -                                         "at http://bugzilla.redhat.com"))
    +                                         "at http://www.chinaredflag.cn/index.html"))
                 return
    
             self._eula_buffer.set_text("")
    diff -uNr initial-setup-0.3.9.23__orig/initial_setup/product.py initial-setup-0.3.9.23/initial_setup/product.py
    --- initial-setup-0.3.9.23__orig/initial_setup/product.py       2015-01-15 18:54:11.000000000 +0000
    +++ initial-setup-0.3.9.23/initial_setup/product.py     2015-03-26 08:54:23.504016132 +0000
    @@ -7,7 +7,7 @@
     import glob
    
     RELEASE_STRING_FILE = "/etc/os-release"
    -LICENSE_FILE_GLOB = "/usr/share/redhat-release*/EULA*"
    +LICENSE_FILE_GLOB = "/usr/share/asianux-release*/EULA*"
    
     log = logging.getLogger("initial-setup")
    
    diff -uNr initial-setup-0.3.9.23__orig/initial_setup/tui/spokes/eula.py initial-setup-0.3.9.23/initial_setup/tui/spokes/eula.py
    --- initial-setup-0.3.9.23__orig/initial_setup/tui/spokes/eula.py       2015-01-15 18:54:11.000000000 +0000
    +++ initial-setup-0.3.9.23/initial_setup/tui/spokes/eula.py     2015-03-26 08:51:49.932941242 +0000
    @@ -46,7 +46,7 @@
             else:
                 log.debug("license not found")
                 self._window += [TextWidget(_("No license found. Please report this "
    -                                          "at http://bugzilla.redhat.com")), ""]
    +                                          "at http://www.chinaredflag.cn/index.html")), ""]
    
         @property
         def completed(self):
    
    ```


##### 问题二：修改mate-desktop桌面的锁屏背景。

- 背景图片在本系统上所在的位置为：

  ```bash
  /usr/share/backgrounds/day.jpg
  /usr/share/backgrounds/default.jpg
  ```

- 根据要求更换其相片即可。

##### 问题三：修改桌面上的Applications的显示图片。

- 在本系统中其实际图片所在为：

  ```bash
  /usr/share/icons/mate/16x16/places/start-here.png
  /usr/share/icons/mate/22x22/places/start-here.png
  /usr/share/icons/mate/24x24/places/start-here.png
  /usr/share/icons/mate/32x32/places/start-here.png
  /usr/share/icons/mate/48x48/places/start-here.png
  /usr/share/icons/menta/16x16/places/start-here.png
  /usr/share/icons/menta/22x22/places/start-here.png
  /usr/share/icons/menta/24x24/places/start-here.png
  /usr/share/icons/menta/32x32/places/start-here.png
  /usr/share/icons/menta/48x48/places/start-here.png
  ```

- 根据要求更换其图片即可。

##### 问题四：进入安装界面anaconda无法识别磁盘格式。

- 给anaconda打上补丁如下，并重新封`iso`：

  ```c
  diff -Nur anaconda-21.48.22.147-bak/pyanaconda/installclasses/centos.py anaconda-21.48.22.147/pyanaconda/installclasses/centos.py
  --- anaconda-21.48.22.147-bak/pyanaconda/installclasses/centos.py       2020-11-17 09:43:49.431380257 +0800
  +++ anaconda-21.48.22.147/pyanaconda/installclasses/centos.py   2020-11-17 09:45:15.230830311 +0800
  @@ -32,7 +32,7 @@
       sortPriority = 20001
       if not productName.startswith("Asianux"):
           hidden = True
  -    defaultFS = "xfs"
  +    defaultFS = "ext4"
  
       bootloaderTimeoutDefault = 5
  ```

## 自行编写的工具脚本

##### 自动解决安装依赖，并编译指定包中的源码包；

```bash
#!/bin/sh

set -ex 
BASEDIR=`pwd`
DATE=$(date +'%Y%m%d%H%M')
SRCDIR=$BASEDIR/src
RESULTDIR=$BASEDIR/myresult
OKDIR=$RESULTDIR/ok-src
OKRPM=$RESULTDIR/ok-myrpm
FAILEDNODE=$RESULTDIR/failed-"$DATE".txt
SUCCESSNODE=$RESULTDIR/success-"$DATE".txt
MYALLDIR=("$RESULTDIR" "$OKDIR" "$OKRPM")

function HowUsing ()
{
        if [[ $1 -ne 1 ]]
        then
                echo "Using: $2 <srcdir>"
                exit 1
        fi
}


function getsrcdir ()
{
        if [[ -z $1 ]]
        then
                echo "${SRCDIR}"
        else
                SRCDIR=$BASEDIR/$1
        fi
}

function mymkdir ()
{
        for _dir in ${MYALLDIR[@]}
        do
                if [[ ! -d "${_dir}" ]]
                then
                        mkdir -p "${_dir}"
                fi
        done
}

function myrpmbuild ()
{
        export LANG=en_US.UTF-8
        local FILE=$RESULTDIR/.failed.txt
        rpmbuild -ba $1 2> $FILE
        if [[ $? == 0 ]];then
                rm $FILE
                return
        fi
        grep "error: Failed build dependencies" $FILE
        if [[ $? -ne 0 ]];then
                echo "not failed build dependencies !!!"
                rm $FILE
                return 1
        fi
        ERNR=$(awk '$1 == "error:"{print NR}' $FILE)
        echo "$ERNR"
        for rpm in $(awk 'NR > $ERNR{print $1}' $FILE)
        do
                sudo yum install "$rpm" -y
        done
        rm $FILE
        rpmbuild -ba $1
}

{
        HowUsing $# $0
        getsrcdir $1
        mymkdir
        ls ${SRCDIR} | sed 's/.src.rpm//g' | while read resultdir
        do
                if [[ -d ~/rpmbuild ]];then
                        rm -fr ~/rpmbuild
                fi
                rpm -ivh $SRCDIR/$resultdir.src.rpm
                myrpmbuild ~/rpmbuild/SPECS/*
                if [[ $? -eq 0 ]]
                then
                        echo "$resultdir.src.rpm" >> $SUCCESSNODE
                        mv $SRCDIR/$resultdir.src.rpm $OKDIR
                        mkdir -p $OKRPM/$resultdir
                        mv ~/rpmbuild/RPMS ~/rpmbuild/SRPMS -t $OKRPM/$resultdir/
                        rm -fr ~/rpmbuild
                else
                        echo "$resultdir.src.rpm" >> $FAILEDNODE
                        rm -fr ~/rpmbuild
                fi
        done
}
```