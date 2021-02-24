### Search

- Links
  - [Get Fedora](https://getfedora.org/)
  - [Fedora Docs](https://docs.fedoraproject.org/)
  - [Fedora Magazine](https://fedoramagazine.org/)
  - [What Can I Do?](https://whatcanidoforfedora.org/)
- CodeOfConduct
  - [Code of Conduct](https://docs.fedoraproject.org/en-US/project/code-of-conduct/)
- Subprojects
  - [Ambassadors](https://fedoraproject.org/wiki/Ambassadors)
  - [Community Operations](https://fedoraproject.org/wiki/CommOps)
  - [Design](https://fedoraproject.org/wiki/Design)
  - [Documentation](https://fedoraproject.org/wiki/DocsProject)
  - [EPEL](https://fedoraproject.org/wiki/EPEL)
  - [Infrastructure](https://fedoraproject.org/wiki/Infrastructure)
  - [Internationalization](https://fedoraproject.org/wiki/I18N)
  - [Localization](https://fedoraproject.org/wiki/L10N)
  - [Marketing](https://fedoraproject.org/wiki/Marketing)
  - [Magazine](https://fedoraproject.org/wiki/Magazine)
  - [Package Maintainers](https://fedoraproject.org/wiki/PackageMaintainers)
  - [Quality Assurance](https://fedoraproject.org/wiki/QA)
  - [Websites](https://fedoraproject.org/wiki/Websites)
  - [All projects](https://fedoraproject.org/wiki/Projects)
- Log In

# How to create an RPM package/zh-cn

 

- [Page](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn)
- [Discussion](https://fedoraproject.org/w/index.php?title=Talk:How_to_create_an_RPM_package/zh-cn&action=edit&redlink=1)
- [View](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn)
- [View source](https://fedoraproject.org/w/index.php?title=How_to_create_an_RPM_package/zh-cn&action=edit)
- [History](https://fedoraproject.org/w/index.php?title=How_to_create_an_RPM_package/zh-cn&action=history)

From Fedora Project Wiki

< [How to create an RPM package](https://fedoraproject.org/wiki/How_to_create_an_RPM_package)

## Contents



- [1 关于本指南](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.85.B3.E4.BA.8E.E6.9C.AC.E6.8C.87.E5.8D.97)
- [2 准备系统](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.87.86.E5.A4.87.E7.B3.BB.E7.BB.9F)
- [3 RPM 基础知识](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#RPM_.E5.9F.BA.E7.A1.80.E7.9F.A5.E8.AF.86)
- 4 做好准备打包一个特殊程序
  - [4.1 分离程序](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.88.86.E7.A6.BB.E7.A8.8B.E5.BA.8F)
  - [4.2 许可协议](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E8.AE.B8.E5.8F.AF.E5.8D.8F.E8.AE.AE)
  - [4.3 使用已有的信息](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E4.BD.BF.E7.94.A8.E5.B7.B2.E6.9C.89.E7.9A.84.E4.BF.A1.E6.81.AF)
- 5 新建一个 .spec 文件
  - 5.1 模板和实例
    - [5.1.1 模板](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E6.A8.A1.E6.9D.BF)
    - 5.1.2 实例
      - [5.1.2.1 eject](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#eject)
- [6 SPEC 文件综述](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#SPEC_.E6.96.87.E4.BB.B6.E7.BB.BC.E8.BF.B0)
- 7 SPEC 文件剖析
  - 7.1 %prep 部分
    - [7.1.1 %prep 部分：%autosetup 命令](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25prep_.E9.83.A8.E5.88.86.EF.BC.9A.25autosetup_.E5.91.BD.E4.BB.A4)
    - [7.1.2 %prep 部分：%patch 命令](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25prep_.E9.83.A8.E5.88.86.EF.BC.9A.25patch_.E5.91.BD.E4.BB.A4)
    - [7.1.3 %prep 部分：未修改文件](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25prep_.E9.83.A8.E5.88.86.EF.BC.9A.E6.9C.AA.E4.BF.AE.E6.94.B9.E6.96.87.E4.BB.B6)
  - [7.2 %build 部分](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25build_.E9.83.A8.E5.88.86)
  - [7.3 %install 部分](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25install_.E9.83.A8.E5.88.86)
  - [7.4 %check 部分](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25check_.E9.83.A8.E5.88.86)
  - 7.5 %files 部分
    - [7.5.1 %files 基础](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25files_.E5.9F.BA.E7.A1.80)
    - [7.5.2 %files 前缀](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25files_.E5.89.8D.E7.BC.80)
    - [7.5.3 %files 和文件系统层次标准 (FHS)](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25files_.E5.92.8C.E6.96.87.E4.BB.B6.E7.B3.BB.E7.BB.9F.E5.B1.82.E6.AC.A1.E6.A0.87.E5.87.86_.28FHS.29)
    - [7.5.4 %files 示例](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.25files_.E7.A4.BA.E4.BE.8B)
    - [7.5.5 找出重复内容](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E6.89.BE.E5.87.BA.E9.87.8D.E5.A4.8D.E5.86.85.E5.AE.B9)
  - [7.6 Scriptlets](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#Scriptlets)
  - [7.7 宏](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.AE.8F)
  - [7.8 其它标签](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.85.B6.E5.AE.83.E6.A0.87.E7.AD.BE)
  - [7.9 子软件包](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.AD.90.E8.BD.AF.E4.BB.B6.E5.8C.85)
  - [7.10 条件判断](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E6.9D.A1.E4.BB.B6.E5.88.A4.E6.96.AD)
  - [7.11 应用程序具体规定](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.BA.94.E7.94.A8.E7.A8.8B.E5.BA.8F.E5.85.B7.E4.BD.93.E8.A7.84.E5.AE.9A)
  - [7.12 其他注意事项](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E5.85.B6.E4.BB.96.E6.B3.A8.E6.84.8F.E4.BA.8B.E9.A1.B9)
- 8 构建 RPM 包
  - [8.1 使用 rpmlint 测试](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E4.BD.BF.E7.94.A8_rpmlint_.E6.B5.8B.E8.AF.95)
  - [8.2 从 SPEC 构建 RPM 包](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E4.BB.8E_SPEC_.E6.9E.84.E5.BB.BA_RPM_.E5.8C.85)
  - [8.3 使用 rpmlint 测试已构建的 RPM 包](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E4.BD.BF.E7.94.A8_rpmlint_.E6.B5.8B.E8.AF.95.E5.B7.B2.E6.9E.84.E5.BB.BA.E7.9A.84_RPM_.E5.8C.85)
- [9 Mock 和 Koji](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#Mock_.E5.92.8C_Koji)
- [10 有用的工具](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E6.9C.89.E7.94.A8.E7.9A.84.E5.B7.A5.E5.85.B7)
- [11 相关规定](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E7.9B.B8.E5.85.B3.E8.A7.84.E5.AE.9A)
- [12 维护软件包](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E7.BB.B4.E6.8A.A4.E8.BD.AF.E4.BB.B6.E5.8C.85)
- [13 更多信息](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn#.E6.9B.B4.E5.A4.9A.E4.BF.A1.E6.81.AF)

## 关于本指南

本指南描述了如何为 Fedora 制作 RPM 包，特别是如何写 .spec 配置文件。不像其它文档，本文档会解释 Fedora  中特殊领域的打包(会有链接指向 Fedora 的特殊打包规定)。并且由于本文档通过 wiki 更新，因此会尽可能的保持最新。除了  Fedora，绝大部分内容也会适用其他基于 RPM 机制的发行版。如果您等不及了，您可以先看看[如何创建一个 GNU Hello World 软件包](https://fedoraproject.org/wiki/How_to_create_a_GNU_Hello_RPM_package/zh-cn)，这是一个创建 RPM 包的简短总结(不包含详细信息)。 

**目前 Fedora 文档团队有一份草稿已经发布：** 

[Packager 指南](http://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/Packagers_Guide) 

注意，本指南并不是 Fedora 官方的打包**规定**，[打包委员会](https://fedoraproject.org/wiki/Packaging:Committee) 制定的 Fedora 所有打包规定如下： 

- [打包规定](https://fedoraproject.org/wiki/Packaging:Guidelines)
- [软件许可协议规定](https://fedoraproject.org/wiki/Packaging:LicensingGuidelines)
- [软件包命名规定](https://fedoraproject.org/wiki/Packaging:NamingGuidelines)
- [Dist 标签使用指南](https://fedoraproject.org/wiki/Packaging:DistTag)
- [软件包审核规定](https://fedoraproject.org/wiki/Packaging:ReviewGuidelines)
- [SPEC 文件编写指南](https://fedoraproject.org/wiki/Packaging:ScriptletSnippets) ([zh_CN](https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-hk))

**[打包规定](https://fedoraproject.org/wiki/Packaging:Guidelines) 和 [软件包命名规定](https://fedoraproject.org/wiki/Packaging:NamingGuidelines) 是主要的两份规定，本指南与这两份规定100%兼容。** 

如果您计划为 Fedora 的官方源创建一个 RPM 包，请按照 [如何成为 Fedora 软件包仓库维护人员](https://fedoraproject.org/wiki/Join_the_package_collection_maintainers/zh-cn) 页面的步骤一步步来。 

## 准备系统

在您为 Fedora 创建 RPM 包之前，您需要安装一些必须的开发工具并设置账户： 

```
 # dnf install @development-tools fedora-packager rpmdevtools
```

您可以新建一个临时用户以便创建 RPM 包。这样，如果有错误发生，构建程序不会破坏您的系统，比如造成文件损失或您的私人文件/密钥被发送到互联网上。 

[![Stop (medium size).png](https://fedoraproject.org/w/uploads/thumb/6/61/Stop_%28medium_size%29.png/35px-Stop_%28medium_size%29.png)](https://fedoraproject.org/wiki/File:Stop_(medium_size).png)

**切记！不要使用 `root` 用户来执行打包操作。因为这十分危险，所有二进制文件都会在打包前安装至系统中，因此您应该以普通用户身份打包，以防止系统被破坏。**

创建名为 `makerpm` 的用户，添加至 'mock' 用户组，设置好密码并通过该用户登录： 

```
 # /usr/sbin/useradd makerpm
 # usermod -a -G mock makerpm
 # passwd makerpm
```

然后，您可以通过这个临时用户开始打包操作。 

一旦以 makerpm 用户登陆，使用以下命令在用户家目录下，创建标准的打包工作目录结构： 

```
 $ rpmdev-setuptree
```

`rpmdev-setuptree` 程序将创建 `~/rpmbuild` 目录，以及一系列预设的子目录（如 `SPECS` 和 `BUILD`），你将使用它们作为打包目录。另外，还会创建 `~/.rpmmacros` 文件，它用于设置各种选项。 

[打包指南建议保留文件时间戳](https://fedoraproject.org/wiki/Packaging:Guidelines#Timestamps)；当然，您在使用 `wget` 或 `curl` 获取软件源代码的时候就会自动保存。如果您使用 `wget` 来获取源代码，确保 `~/.wgetrc` 文件包含此行 `timestamping = on` 。如果您使用 `curl` ，确保 `~/.curlrc` 文件包含 `-R` 选项。 

一旦设置完毕，通常不需要再次设置。 

## RPM 基础知识

若要构建一个标准的 RPM 包，您需要创建 `.spec` 文件，其中包含软件打包的全部信息。然后，对此文件执行 `rpmbuild` 命令，经过这一步，系统会按照步骤生成最终的 RPM 包。 

一般情况，您应该把源代码包，比如由开发者发布的以 `.tar.gz` 结尾的文件，放入 `~/rpmbuild/SOURCES` 目录。将`.spec` 文件放入 `~/rpmbuild/SPECS` 目录，并命名为 "*软件包名*.spec" 。当然， *软件包名* 就是最终 RPM 包的名字。为了创建二进制（Binary RPM）和源码软件包（SRPM），您需要将目录切换至 `~/rpmbuild/SPECS` 并执行： 

```bash
 $ rpmbuild -ba NAME.spec
```

当执行此命令时，`rpmbuild` 会自动读取 `.spec` 文件并按照下表列出的步骤完成构建。下表中，以 `%` 开头的语句为预定义宏，每个宏的作用如下： 

| 阶段       | 读取的目录       | 写入的目录       | 具体动作                                                     |
| ---------- | ---------------- | ---------------- | ------------------------------------------------------------ |
| `%prep`    | `%_sourcedir`    | `%_builddir`     | 读取位于 `%_sourcedir` 目录的源代码和 patch 。之后，解压源代码至 `%_builddir` 的子目录并应用所有 patch。 |
| `%build`   | `%_builddir`     | `%_builddir`     | 编译位于 `%_builddir` 构建目录下的文件。通过执行类似 "`./configure && make`" 的命令实现。 |
| `%install` | `%_builddir`     | `%_buildrootdir` | 读取位于 `%_builddir` 构建目录下的文件并将其安装至 `%_buildrootdir` 目录。这些文件就是用户安装 RPM 后，最终得到的文件。注意一个奇怪的地方: *最终安装目录* **不是** *构建目录*。通过执行类似 "`make install`" 的命令实现。 |
| `%check`   | `%_builddir`     | `%_builddir`     | 检查软件是否正常运行。通过执行类似 "`make test`" 的命令实现。很多软件包都不需要此步。 |
| `bin`      | `%_buildrootdir` | `%_rpmdir`       | 读取位于 `%_buildrootdir` 最终安装目录下的文件，以便最终在 `%_rpmdir` 目录下创建 RPM 包。在该目录下，不同架构的 RPM 包会分别保存至不同子目录， "`noarch`" 目录保存适用于所有架构的 RPM 包。这些 RPM 文件就是用户最终安装的 RPM 包。 |
| `src`      | `%_sourcedir`    | `%_srcrpmdir`    | 创建源码 RPM 包（简称 SRPM，以`.src.rpm` 作为后缀名），并保存至 `%_srcrpmdir` 目录。SRPM 包通常用于审核和升级软件包。 |


 在 `rpmbuild` 中，对上表中的每个宏代码都有对应的目录： 

| 宏代码           | 名称              | 默认位置               | 用途                                         |
| ---------------- | ----------------- | ---------------------- | -------------------------------------------- |
| `%_specdir`      | Spec 文件目录     | `~/rpmbuild/SPECS`     | 保存 RPM 包配置（`.spec`）文件               |
| `%_sourcedir`    | 源代码目录        | `~/rpmbuild/SOURCES`   | 保存源码包（如 .tar 包）和所有 patch 补丁    |
| `%_builddir`     | 构建目录          | `~/rpmbuild/BUILD`     | 源码包被解压至此，并在该目录的子目录完成编译 |
| `%_buildrootdir` | 最终安装目录      | `~/rpmbuild/BUILDROOT` | 保存 %install 阶段安装的文件                 |
| `%_rpmdir`       | 标准 RPM 包目录   | `~/rpmbuild/RPMS`      | 生成/保存二进制 RPM 包                       |
| `%_srcrpmdir`    | 源代码 RPM 包目录 | `~/rpmbuild/SRPMS`     | 生成/保存源码 RPM 包(SRPM)                   |

如果某一阶段失败，请查看输出信息以了解失败*原因*，并根据需要修改 `.spec` 文件。 

## 做好准备打包一个特殊程序

如果这里有特殊的程序，它们需要被安装或者运行以便让您打包的普通程序正常工作，那么请先安装它们，然后记录下诸如软件包等相关信息。 

如果想为 Fedora 源打包一个程序，您必须使用源代码来打包，且包含 patch 以及打包简介；**不可以**使用预编译代码进行打包。将源代码（通常是 .tar.gz 文件）放入 "`~/rpmbuild/SOURCES`" 目录（注意用户）。 

仔细阅读该软件的安装说明。我们建议您先手工安装一次以了解具体情况。除少数情况外，所有二进制文件和程序库都必须由源码包中的源码编译而成。 

### 分离程序

应用程序的源代码发布时，通常会捆绑许多外部依赖库的源代码。[请不要将外部组件与主程序一起打包](https://fedoraproject.org/wiki/Packaging:No_Bundled_Libraries)。相反，您需要拆分每个组件并单独打包。 

### 许可协议

您只允许打包**符合协议**的软件。请查看 [Packaging:Guidelines#Legal](https://fedoraproject.org/wiki/Packaging:Guidelines#Legal)、[Licensing:Main](https://fedoraproject.org/wiki/Licensing:Main) 和 [Packaging:LicensingGuidelines](https://fedoraproject.org/wiki/Packaging:LicensingGuidelines)。通常情况下，您只可以打包使用开源许可证（如 GNU GPL、LGPL、BSD-new、MIT/X 或 Apache  2.0）发布的开源软件（OSS）。请仔细检查许可证是否名副其实，同时确认软件整体是否均基于开源协议发布（如检查头文件注释、 README  文件等等)。如果软件捆绑外部依赖库，请确保这些库也使用开源协议（这十分重要）。 

### 使用已有的信息

尽可能利用一切已有的信息！很明显，请不要打包源中已存在的程序！为了防止您犯这种错误，请查阅 [Fedora 软件包数据库](https://admin.fedoraproject.org/pkgdb/)。同时建议查阅 [正在被审核的软件包](https://fedoraproject.org/wiki/PackageMaintainers/InProgressReviewRequests)和 [已停止使用的软件包](https://fedoraproject.org/wiki/PackageMaintainers/RetiredPackages)列表。如果未找到相关信息，请使用 Google 搜索查看是否有类似 rpm 包。您可以直接访问 [Fedora 软件包 Git 源](http://pkgs.fedoraproject.org/cgit/) 查看相关 SPEC 文件（和 Patch）。您可以使用 DNF 插件下载 SRPM 包： 

```
$ dnf download --source sourcepackage-name
```

或通过访问 [Fedora 镜像列表](http://mirrors.fedoraproject.org/publiclist) 的 HTTP/FTP 镜像页面，导航至 `releases/31/Everything/source/SRPMS` 目录（ "`31`" 表示 Fedora 版本），手动下载扩展名为 `.src.rpm` 的 SRPM 包即可。 

一旦有了源码包，执行以下命令安装至 `~/rpmbuild` 目录： 

```
$ rpm -ivh 源码包名*.src.rpm
```

您也可以使用 `rpm2cpio` 将源码包解压至任意目录： 

```
$ mkdir 源码包名_src_rpm
$ cd 源码包名_src_rpm
$ rpm2cpio ../源码包名.src.rpm | cpio -i
```

使用已有的信息以帮助您打包。[RPM Find](http://rpmfind.net/) 和 [PKGS.org](http://pkgs.org) 可以搜索非 Fedora 系统的 RPM 包。您可以尝试以相同的方式安装 SRPMS，并进行调试。如果未找到 RPM，可以参考 [Ubuntu](http://packages.ubuntu.com/) 或 [Debian](http://www.debian.org/distrib/packages) 的源码包（标准 tar 文件，内部包含 "`debian/`" 子目录）。如果您在 [FreeBSD ports 仓库](http://www.freebsd.org/ports/installing.html) 找到想要的软件， [请下载 ports 源码包](ftp://ftp.freebsd.org/pub/FreeBSD/ports/ports/ports.tar.gz) 并查看是否包含相关信息。有时，这些操作没什么实际帮助，因为不同系统有不同的打包规则。 

## 新建一个 .spec 文件

现在，您需要在 `~/rpmbuild/SPECS` 目录下，新建一个 SPEC 文件。文件应命名为 "`软件包名.spec`"。名称根据软件包名或通用名填写即可。但是，必须要遵守 [软件包命名规定](https://fedoraproject.org/wiki/Packaging/NamingGuidelines)。 

### 模板和实例

#### 模板

如果您首次创建 .spec 文件，vim 或 emacs 会自动生成模板： 

```
 $ cd ~/rpmbuild/SPECS
 $ vim program.spec
```

示例（仅供参考）： 

```.spec
Name:
Version:
Release:	1%{?dist}
Summary:
Group:
License:
URL:
Source0:
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:
Requires:

%description

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc

%changelog
```

您可以使用 `$RPM_BUILD_ROOT` 代替 `%{buildroot}`，两者都可以使用。 

您也可以使用 `rpmdev-newspec` 命令来创建 SPEC 文件。`rpmdev-newspec 软件包名` 可以创建一个初始 SPEC 文件，该工具从软件包名判断使用哪个模板，支持指定模板。 `/etc/rpmdevtools/spectemplate-*.spec` 包含所有可用的模板，使用 `rpmdev-newspec --help` 命令了解更多信息。例如，为 python 模块创建 SPEC 文件： 

```
cd ~/rpmbuild/SPECS
rpmdev-newspec python-antigravity
vi python-antigravity.spec
```

#### 实例

##### eject

这是 Fedora 16 `eject` 程序的 spec 文件： 

```
Summary:            A program that ejects removable media using software control
Name:               eject
Version:            2.1.5
Release:            21%{?dist}
License:            GPLv2+
Group:              System Environment/Base
Source:             %{name}-%{version}.tar.gz
Patch1:             eject-2.1.1-verbose.patch
Patch2:             eject-timeout.patch
Patch3:             eject-2.1.5-opendevice.patch
Patch4:             eject-2.1.5-spaces.patch
Patch5:             eject-2.1.5-lock.patch
Patch6:             eject-2.1.5-umount.patch
URL:                http://www.pobox.com/~tranter
ExcludeArch:        s390 s390x
BuildRequires:      gettext
BuildRequires:      libtool

%description
The eject program allows the user to eject removable media (typically
CD-ROMs, floppy disks or Iomega Jaz or Zip disks) using software
control. Eject can also control some multi-disk CD changers and even
some devices' auto-eject features.

Install eject if you'd like to eject removable media using software
control.

%prep
%autosetup -n %{name}

%build
%configure
make %{?_smp_mflags}

%install
%make_install

install -m 755 -d %{buildroot}/%{_sbindir}
ln -s ../bin/eject %{buildroot}/%{_sbindir}

%find_lang %{name}

%files -f %{name}.lang
%doc README TODO COPYING ChangeLog
%{_bindir}/*
%{_sbindir}/*
%{_mandir}/man1/*

%changelog
* Tue Feb 08 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2.1.5-21
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Fri Jul 02 2010 Kamil Dudka <kdudka@redhat.com> 2.1.5-20
- handle multi-partition devices with spaces in mount points properly (#608502)
```

 

## SPEC 文件综述

其他有用的信息： 

- [RPM 指南](http://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/RPM_Guide/ch-creating-rpms.html) 描述了如何编写 spec 文件。
- IBM "Packaging software with RPM" 系列文章 [Part 1](http://www.ibm.com/developerworks/library/l-rpm1/)，[Part 2](http://www.ibm.com/developerworks/library/l-rpm2/)，[Part 3](http://www.ibm.com/developerworks/library/l-rpm3/)。
- [Maximum RPM](http://rpm.org/max-rpm-snapshot/) 包含详细信息，但内容已经过时。

您需要遵守这些规定：[软件包命名规定](https://fedoraproject.org/wiki/Packaging/NamingGuidelines)，[打包规定](https://fedoraproject.org/wiki/Packaging/Guidelines) 和 [软件包审核规定](https://fedoraproject.org/wiki/Packaging/ReviewGuidelines)。 

"`#`" 字符表示注释，但需要避免注释宏（以 `%` 开头），因为它们会首先被替换展开。使用 `%%` 注释宏。另外，还要避免在脚本命令的相同行中使用行内注释。 

以下介绍了主要的标签。注意 `%{name}`，`%{version}` 和 `%{release}` 代表 Name, Version 和 Release 这三个标签。只要更改标签，宏就会使用新值。 

- **Name**: 软件包名，应与 SPEC 文件名一致。命名必须符合 [软件包命名规定](https://fedoraproject.org/wiki/Packaging/NamingGuidelines)。
- **Version**: 上游版本号。请查看 [版本标签规定](https://fedoraproject.org/wiki/Packaging/NamingGuidelines#Version_Tag)。如果包含非数字字符，您可能需要将它们包含在 Release 标签中。如果上游采用日期作为版本号，请考虑以：`yy.mm[dd]` (例如 `2008-05-01` 可变为 `8.05`) 格式作为版本号。
- **Release**: 发行编号。初始值为 `1%{?dist}`。每次制作新包时，请递增该数字。当上游发布新版本时，请修改 Version 标签并重置 Release 的数字为 `1`。具体参考打包规定中的 [Release 标签部分](https://fedoraproject.org/wiki/Packaging/NamingGuidelines#Release_Tag)，以及 [Dist tag](https://fedoraproject.org/wiki/Packaging/DistTag)。
- **Summary**: 一行简短的软件包介绍。请使用美式英语。**请勿在结尾添加标点！**
- **Group**: 指定软件包组，例如 "Applications/Engineering"；执行 "`less /usr/share/doc/rpm-*/GROUPS`" 查看完整的组列表。任何包含文档的子软件包，使用 "Documentation" 组（如 `kernel-doc`）。***注意 Fedora 17+ 后已废除此标签。[Spec 文件参考手册](http://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/Packagers_Guide/chap-Packagers_Guide-Spec_File_Reference-Preamble.html) 有介绍***
- **License**: 授权协议，必须是开源许可证。请*不要*使用旧的 Copyright 标签。协议采用标准缩写（如 "`GPLv2+`"）并且描述明确（如， "`GPLv2+`" 表示 GPL 2 及后续版本，而不是 "`GPL`" 或 "`GPLv2`" 这种不准确的写法)。参考 [Licensing](https://fedoraproject.org/wiki/Licensing) 和 [Licensing Guidelines](https://fedoraproject.org/wiki/Packaging/LicensingGuidelines)。如果一个软件采用多个协议，可以使用 "`and`" 和 "`or`"（例如 "`GPLv2 and BSD`"）来描述。
- **URL**: 该软件包的项目主页。***注意：源码包 URL 请使用 Source0 指定。***
- **Source0**: 软件源码包的 URL 地址。"`Source`" 与 "`Source0`" 相同。**强烈建议**提供完整 URL 地址，文件名用于查找 `SOURCES` 目录。如果可能，建议使用 `%{name}` 和 `%{version}` 替换 URL 中的名称/版本，这样更新时就会自动对应。下载源码包时，需要 [保留时间戳](https://fedoraproject.org/wiki/Packaging:Guidelines#Timestamps)。如果有多个源码包，请用 `Source1`，`Source2` 等依次列出。如果你需要添加额外文件，请将它们列在后面。更多特殊案例（如 revision control），请参考 [Source URL](https://fedoraproject.org/wiki/Packaging/SourceURL)。
- **Patch0**: 用于源码的补丁名称。如果你需要在源码包解压后对一些代码做修改，你应该修改代码并使用 diff 命令生成 patch 文件，然后放在 `~/rpmbuild/SOURCES` 目录下。一个 Patch 应该只做一种修改，所以可能会包含多个 patch 文件。
- **BuildArch**: 如果你要打包的文件不依赖任何架构（例如 shell 脚本，数据文件），请使用 "`BuildArch: noarch`"。RPM 架构会变成 "`noarch`"。
- **BuildRoot**: 在 %install 阶段（%build 阶段后）文件需要安装至此位置。Fedora 不需要此标签，只有 EPEL5 还需要它。默认情况下，根目录为 "`%{_topdir}/BUILDROOT/`"。
- **BuildRequires**: 编译软件包所需的依赖包列表，以逗号分隔。此标签可以多次指定。编译依赖 *不会* 自动判断，所以需要列出编译所需的*所有*依赖包。[常见的软件包可省略](https://fedoraproject.org/wiki/Packaging/Guidelines#Exceptions_2)，例如 `gcc`。如果有必要，你可以指定需要的最低版本（例："`ocaml >= 3.08`"）。如果你需要找到包含 `/EGGS` 文件的软件包，可执行 "`rpm -qf /EGGS`"。如果你需要找到包含 `EGGS` 程序的软件包，可执行 "`rpm -qf which EGGS`"。请保持最小依赖（例如，如果你不需要 perl 的功能，可使用 `sed` 代替），但请注意，如果不包含相关依赖，某些程序会禁用一些功能；此时，你需要添加这些依赖。`![Package-x-generic-16.png](https://fedoraproject.org/w/uploads/a/a4/Package-x-generic-16.png)auto-buildrequires` 软件包可能会有帮助。
- **Requires**: 安装软件包时所需的依赖包列表，以逗号分隔。请注意， BuildRequires 标签是编译所需的依赖，而 Requires 标签是安装/运行程序所需的依赖。大多数情况下，`rpmbuild` 会自动探测依赖，所以可能不需要 Requires 标签。然而，你也可以明确标明需要哪些软件包，或由于未自动探测所需依赖而需要手动标明。
- **%description**: 程序的详细/多行描述，请使用美式英语。每行必须小于等于 80 个字符。空行表示开始新段落。使用图形安装软件时会重新格式化段落；以空格开头的行被视为已格式化的格式，一般使用等宽字体显示。参考 [RPM Guide](http://docs.fedoraproject.org/drafts/rpm-guide-en/ch09s03.html)。
- **%prep**: 打包准备阶段执行一些命令（如，解压源码包，打补丁等），以便开始编译。一般仅包含 "`%autosetup`"；如果源码包需要解压并切换至 `NAME` 目录，则输入 "`%autosetup -n NAME`"。查看 %prep 部分了解更多信息。
- **%build**: 包含构建阶段执行的命令，构建完成后便开始后续安装。程序应该包含有如何编译的介绍。查看 %build 部分了解更多信息。
- **%install**: 包含安装阶段执行的命令。命令将文件从 `%{_builddir}` 目录安装至 `%{buildroot}` 目录。查看 %install 部分了解更多信息。
- **%check**: 包含测试阶段执行的命令。此阶段在 %install 之后执行，通常包含 "`make test`" 或 "`make check`" 命令。此阶段要与 %build 分开，以便在需要时忽略测试。
- **%clean**: 清理安装目录的命令。此阶段在 Fedora 中是多余的，仅针对 EPEL。一般只包含：

```
rm -rf %{buildroot}
```

- **%files**: 需要被打包/安装的文件列表。查看 %files 部分了解更多信息。
- **%changelog**: RPM 包变更日志。请使用示例中的格式。**注意，不是软件本身的变更日志。**
- **ExcludeArch**: 排除某些架构。如果该软件不能在某些架构上正常编译或工作，通过该标签列出。
- **ExclusiveArch**: 列出该软件包独占的架构。
- 你可以加入一些代码片段，以便在真实系统上安装/删除包时执行这些代码（相反，%install 脚本仅将文件虚拟【pseudo】安装至  build root 目录）。这些代码称为 "scriptlets"，通常用于从软件包更新系统信息。查看 "Scriptlets"  部分了解更多信息。

RPM 还支持使用一个 SPEC 文件制作多个软件包（这称为 [子软件包](https://fedoraproject.org/wiki/How_to_create_an_RPM_package#Subpackages)），例如 `name-libs` 和 `name-devel` 等软件包。 

[![Stop (medium size).png](https://fedoraproject.org/w/uploads/thumb/6/61/Stop_%28medium_size%29.png/35px-Stop_%28medium_size%29.png)](https://fedoraproject.org/wiki/File:Stop_(medium_size).png)

**请**不要

- Packager
- Vendor
- Copyright

请**不要**制作 "relocatable" 软件包（不遵守FHS）；它们不会为 Fedora 加分，反而把事情搞得更复杂。 

## SPEC 文件剖析

### %prep 部分

%prep 部分描述了解压源码包的方法。一般而言，其中包含 "`%autosetup`" 命令。另外，还可以使用 "`%setup`" 和 "`%patch`" 命令来指定操作 Source0 等标签的文件。查看 [Maximum RPM 的 %setup and %patch 小节](http://rpm.org/max-rpm-snapshot/s1-rpm-inside-macros.html) 了解更多信息。 

自 RPM 4.4.2 开始，可使用 `%{patches}` 和 `%{sources}` 宏。如果您的软件包包含了许多 patch 或 source，并且你不想使用 %autosetup，那么可以这么做： 

```c
for p in %{patches}; do
    ...
done
```

注意，RHEL 和其它基于 RPM 的发行版，并不支持这种用法。 

#### %prep 部分：%autosetup 命令

"`%autosetup`" 命令用于解压源码包。可用选项包括： 

- **`-n` \*name\*** : 如果源码包解压后的目录名称与 RPM 名称不同，此选项用于指定正确的目录名称。例如，如果 tarball 解压目录为 FOO，则使用 "`%autosetup -n FOO`"。
- **`-c` \*name\*** : 如果源码包解压后包含多个目录，而不是单个目录时，此选项可以创建名为 *name* 的目录，并在其中解压。

如果使用 "`%setup`" 命令，通常使用 *`-q`'* 抑止不必要的输出。 

[如果需要解压多个文件，有更多 %spec 选项可用](http://rpm.org/max-rpm-snapshot/s1-rpm-inside-macros.html)，这对于创建子包很有用。常用选项如下： 

| `-a number` | 在切换目录后，只解压指定序号的 Source 文件（例如 "`-a 0`" 表示 Source0） |
| ----------- | ------------------------------------------------------------ |
| `-b number` | 在切换目录前， 只解压指定序号的 Source 文件（例如 "`-b 0`" 表示 Source0） |
| `-D`        | 解压前，不删除目录。                                         |
| `-T`        | 禁止自动解压归档。                                           |

#### %prep 部分：%patch 命令

如果使用 "`%autosetup`" 命令，则不需要手动进行补丁管理。如果你的需求很复杂，或需要与 EPEL 兼容，需要用到此部分的内容。"`%patch0`" 命令用于应用 Patch0（%patch1 应用 Patch1，以此类推）。Patches 是修改源码的最佳方式。常用的 "`-pNUMBER`" 选项，向 `patch` 程序传递参数，表示跳过 NUM 个路径前缀。 

补丁文件名通常像这样 "`telnet-0.17-env.patch`"，命名格式为 `%{name} - %{version} - REASON.patch`"（有时省略 version 版本）。补丁文件通常是 "`diff -u`" 命令的输出；如果你在 `~/rpmbuild/BUILD` 子目录执行此命令，则之后便不需要指定 `-p` 选项。 

为一个文件制作补丁的步骤： 

```
cp foo/bar foo/bar.orig
vim foo/bar
diff -u foo/bar.orig foo/bar > ~/rpmbuild/SOURCES/PKGNAME.REASON.patch
```

如果需要修改多个文件，简单方法是复制 `BUILD` 下的整个子目录，然后在子目录执行 diff。切换至 "`~rpmbuild/BUILD/NAME`" 目录后，执行以下命令： 

```
cp -pr ./ ../PACKAGENAME.orig/
... 执行修改 ...
diff -ur ../PACKAGENAME.orig . > ~/rpmbuild/SOURCES/NAME.REASON.patch
```

如果你想在一个补丁中编辑多个文件，你可以在编辑之前，使用 "`.orig`" 扩展名复制原始文件。然后，使用 "`gendiff`"（在 `rpm-build` 包中）创建补丁文件。 

需要确保你的补丁精确匹配上下文。默认 "fuzz" 值为 "`0`"，表示要求精确匹配。你可以添加 "`%global _default_patch_fuzz 2`" 将 fuzz 设为旧版 Fedora RPM 所采用的值，但我们建议你尽量避免这样做。 

如 [Packaging/PatchUpstreamStatus](https://fedoraproject.org/wiki/Packaging/PatchUpstreamStatus) 所述，SPEC 文件中的所有补丁都需要注释来描述补丁的上游状态。其中应包括上游 bug/email 文档（包含日期）。如果是 Fedora 特别需要的补丁，应描述为何需要它。Fedora 项目致力于贴近上游；查看 [PackageMaintainers/WhyUpstream](https://fedoraproject.org/wiki/PackageMaintainers/WhyUpstream) 了解其重要性。 

#### %prep 部分：未修改文件

有时，一个或多个源码包不需要解压。你可以使用以下命令，将文件复制到 build 目录中，如（ `SOURCE1` 表示对应的源码包）： 

```
cp -p %SOURCE1 .
```

### %build 部分

"%build" 部分有时会有点复杂；在这里你可以配置，并编译用于安装的文件。 

许多程序使用 GNU `configure` 进行配置。默认情况下，文件会安装到前缀为 "`/usr/local`" 的路径下，对于手动安装很合理。然而，打包时需要修改前缀为 "`/usr`"。共享库路径视架构而定，安装至 `/usr/lib` 或 `/usr/lib64` 目录。 

由于 GNU `configure` 很常见，可使用 "`%configure`" 宏来自动设置正确选项（例如，设置前缀为 `/usr`）。一般用法如下： 

```bash
 %configure
 make %{?_smp_mflags}
```

若需要覆盖 makefile 变量，请将变量作为参数传递给 `make`： 

```
make %{?_smp_mflags} CFLAGS="%{optflags}" BINDIR=%{_bindir}
```

更多详细信息，请参考 ["GNU autoconf, automake 和 libtool"](http://sourceware.org/autobook/) 以及 ["开源开发工具：Make, Configure, Automake, Autoconf 介绍" by Stefan Hundhammer](http://www.suse.de/~sh/automake/automake.pdf)。 

一些程序使用 `cmake`。请参考 [Packaging/cmake](https://fedoraproject.org/wiki/Packaging/cmake)。 

### %install 部分

此部分包含安装阶段需要执行的命令，即从 `%{_builddir}` 复制相关文件到 `%{buildroot}` 目录（通常表示从 `~/rpmbuild/BUILD` 复制到 `~/rpmbuild/BUILDROOT`) 目录，并根据需要在 `%{buildroot}` 中创建必要目录。 

容易混淆的术语： 

- "build 目录"，也称为 `%{_builddir}`，实际上与 "build root"，又称为 `%{buildroot}`，是不同的目录。在前者中进行编译，并将需要打包的文件从前者复制到后者。
- 在 %build 阶段，当前目录为 `%{buildsubdir}`，是 %prep 阶段中在 `%{_builddir}` 下创建的子目录。这些目录通常名为 `~/rpmbuild/BUILD/%{name}-%{version}`。
- %install 阶段的命令**不会**在用户安装 RPM 包时执行，此阶段仅在打包时执行。

一般，这里执行 "`make install`" 之类的命令： 

```c
%install
rm -rf %{buildroot} # 仅用于 RHEL 5
%make_install
```

理想情况下，对于支持的程序，你应该使用 %make_install，它等同于 [`DESTDIR=%{buildroot}`](http://www.gnu.org/prep/standards/html_node/DESTDIR.html)，它会将文件安装到 %{buildroot} 目录中。 

如果程序不支持 `DESTDIR`，使用以下方法避开此问题： 

- 修补 makefile 以便支持 `DESTDIR`。请在 `DESTDIR` 根据需要创建必要目录，并向上游提交补丁。
- 使用 "`%makeinstall`" 宏。此方法可能有效，但也可能失败。该宏会展开为 "`make prefix=%{buildroot}%{_prefix} bindir=%{buildroot}%{_bindir} ... install`"，可能导致某些程序无法正常工作。请在 `%{buildroot}` 根据需要创建必要目录。
- 使用 `auto-destdir` 软件包。它需要 "`BuildRequires: auto-destdir`"，并将 "`make install`" 修改为 "`make-redir DESTDIR=%{buildroot} install`"。这仅适用于使用常用命令安装文件的情况，例如 `cp` 和 `install`。
- 手动执行安装。这需要在 `%{buildroot}` 下创建必要目录，并从 `%{_builddir}` 复制文件至 `%{buildroot}` 目录。要特别注意更新，通常会包含新文件。示例如下：

```
%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{_bindir}/
cp -p mycommand %{buildroot}%{_bindir}/
```

### %check 部分

如果需要执行测试，使用 %check 是个好主意。测试代码应写入 %check 部分（紧接在 %install 之后，因为需要测试 %buildroot 中的文件），而不是写入 %build 部分，这样才能在必要时忽略测试。 

通常，此部分包含： 

```
make test
```

有时候也可以用： 

```
make check
```

请熟悉 Makefile 的用法，并选择适当的方式。 

### %files 部分

此部分列出了需要被打包的文件和目录。 

#### %files 基础

`%defattr` 用于设置默认文件权限，通常可以在 `%files` 的开头看到它。注意，如果不需要修改权限，则不需要使用它。其格式为： 

```
%defattr(<文件权限>, <用户>, <用户组>, <目录权限>)
```

第 4 个参数通常会省略。常规用法为 `%defattr(-,root,root,-)`，其中 "`-`" 表示默认权限。 

您应该列出该软件包拥有的所有文件和目录。尽量使用宏代替目录名，查看宏列表 [Packaging:RPMMacros](https://fedoraproject.org/wiki/Packaging:RPMMacros)（例如：使用 `%{_bindir}/mycommand` 代替 `/usr/bin/mycommand`）。如果路径以 "`/`" 开头（或从宏扩展），则从 `%{buildroot}` 目录取用。否则，假设文件在当前目录中（例如：在 `%{_builddir}` 中，包含需要的文档）。如果您的包仅安装一个文件，如 `/usr/sbin/mycommand`，则 `%files` 部分如下所示：  

```
%files
%{_sbindir}/mycommand
```

若要使软件包不受上游改动的影响，可使用通配符匹配所有文件： 

```
%{_bindir}/*
```

包含一个目录： 

```
%{_datadir}/%{name}/
```

注意，`%{_bindir}/*` 不会声明此软件包拥有 `/usr/bin` 目录，而只包含其中的文件。如果您列出一个目录，则该软件包拥有这个目录，及该目录内的所有文件和子目录。因此，**不要**列出 `%{_bindir}`，并且要小心的处理那些可能和其他软件包共享的目录。 

如果存在以下情况，可能引发错误： 

- 通配符未匹配到任何文件或目录
- 文件或目录被多次列出
- 未列出 `%{buildroot}` 下的某个文件或目录




您也可以使用 `%exclude` 来排除文件。这对于使用通配符来列出全部文件时会很有用，注意如果未匹配到任何文件也会造成失败。 

#### %files 前缀

您可能需要在 `%files` 部分添加一个或多个前缀；请用空格分隔。详情请查看 [Max RPM section on %files directives](http://www.rpm.org/max-rpm/s1-rpm-inside-files-list-directives.html)。 

通常，"`%doc`" 用于列出 `%{_builddir}` 内，但未复制到 `%{buildroot}` 中的文档。通常包括 `README` 和 `INSTALL`。它们会保存至 `/usr/share/doc` 下适当的目录中，不需要声明 `/usr/share/doc` 的所有权。 

**注意：** 如果指定 `%doc` 条目，rpmbuild < 4.9.1 在安装前会将 %doc 目录删除。这表明已保存至其中的文档，例如，在 `%install` 中安装的文档会被删除，因此最终不会出现在软件包中。如果您想要在 `%install` 中安装一些文档，请将它们临时安装到 build 目录（不是 build root 目录）中，例如 `_docs_staging`，接着在 `%files` 中列出，如 `%doc _docs_staging/*` 这样。 

配置文件保存在 `/etc` 中，一般会这样指定（确保用户的修改不会在更新时被覆盖）： 

```
%config(noreplace) %{_sysconfdir}/foo.conf
```

如果更新的配置文件无法与之前的配置兼容，则应这样指定： 

```
%config %{_sysconfdir}/foo.conf
```

"`%attr(mode, user, group)`" 用于对文件进行更精细的权限控制，"`-`" 表示使用默认值： 

```
%attr(0644, root, root) FOO.BAR
```

"`%caps(capabilities)`" 用于为文件分配 POSIX [capabilities](http://linux.die.net/man/7/capabilities)。例如： 

```
%caps(cap_net_admin=pe) FOO.BAR
```

如果包含特定语言编写的文件，请使用 `%lang` 来标注： 

```
%lang(de) %{_datadir}/locale/de/LC_MESSAGES/tcsh*
```

使用区域语言（Locale）文件的程序应遵循 [处理 i18n 文件的建议方法](https://fedoraproject.org/wiki/Packaging:Guidelines#Handling_Locale_Files)： 

- 在 `%install` 步骤中找出文件名： ` %find_lang ${name}`
- 添加必要的编译依赖： `BuildRequires: gettext`
- 使用找到的文件名： `%files -f ${name}.lang`

以下前缀在 Fedora 中**无效**：`%license` 和 `%readme`。 

#### %files 和文件系统层次标准 (FHS)

您应该遵守 [文件系统层次标准（FHS, Filesystem Hierarchy Standard）](http://www.pathname.com/fhs/)。可执行文件保存在 `/usr/bin`，配置文件保存在 `/etc`， 共享库保存在 `/usr/lib`（或 `/usr/lib64`）等等。只有一个例外：不需要用户或管理员直接执行的可执行文件，应保存至 `/usr/libexec` 子目录，子目录通过 `%{_libexecdir}/%{name}` 宏来引用。 

请 **不要** 将文件安装到 `/opt` 或 `/usr/local` 目录中。 

不幸的是，许多程序默认情况下并不遵守 FHS。尤其是，架构无关的共享库被保存至 `/usr/lib` 而非 `/usr/share` 之中。前者供依赖架构的共享库使用，后者供架构无关的共享库使用；这表示不同 CPU 架构的系统都能共享 `/usr/share` 目录。Fedora 中也有一些例外（如 Python 和 Perl），总的来说，Fedora 比其他发行版更严格遵守标准规范。`rpmlint` 会在将 ELF 以外的文件保存至 `/usr/lib` 目录时返回警告。 

#### %files 示例

以下为 %files 部分的简单示例： 

```
%files
%doc README
%license LICENSE COPYING
%{_bindir}/*
%{_sbindir}/*
%{_datadir}/%{name}/
%config(noreplace) %{_sysconfdir}/*.conf
```

#### 找出重复内容

您可以列出任意两个二进制软件包的重复文件，执行以下命令： 

```
cd ~/rpmbuild/RPMS/ARCH  # 将 "ARCH" 替换为您的系统架构
rpm -qlp PACKAGE1.*.rpm | sort > ,1
rpm -qlp PACKAGE2.*.rpm | sort > ,2
comm -12 ,1 ,2
```

### Scriptlets

当用户安装 RPM 时，您可能想要执行一些命令。这可以通过 scriptlets 完成。请查看 [Packaging/ScriptletSnippets](https://fedoraproject.org/wiki/Packaging/ScriptletSnippets)。 

脚本片段可以： 

- 在软体包安装之前 (**`%pre`**) 或之后 (**`%post`**) 执行
- 在软体包卸载之前 (**`%preun`**) 或之后 (**`%postun`**) 执行
- 在事务开始 (**`%pretrans`**) 或结束 (**`%posttrans`**) 时执行

例如，每个二进制 RPM 包都会在动态链接器的默认路径中存储共享库文件，并在 `%post` 和 `%postun` 中调用 `ldconfig` 来更新库缓存。如果软件包有多个包含共享库的子包，则每个软体包也需要执行相同动作。 

```
%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig
```

如果仅执行一个命令，则 "`-p`" 选项会直接执行，而不启用 shell。然而，若有许多命令时，不要使用此选项，按正常编写 shell 脚本即可。 

如果你在脚本片段中执行任何程序，就必须以 "`Requires(CONTEXT)`"（例： `Requires(post)`）的形式列出所有依赖。 

`%pre`、`%post`、`%preun` 和 `%postun` 提供 `$1` 参数，表示动作完成后，系统中保留的此名称的软件包数量。不要比较此参数值是否等于 `2`，而是比较是否大于等于 `2`。`%pretrans` 和 `%posttrans`，`$1` 的值恒为 `0`。 

例如，如果软件包安装了一份 info 手册，那么可以用 `info` 包提供的 `install-info` 来更新 info 手册索引。首先，我们不保证系统已安装 `info` 软件包，除非明确声明需要它；其次，我们不想在 `install-info` 执行失败时，使软件包安装失败： 

```
Requires(post): info
Requires(preun): info
...
%post
/sbin/install-info %{_infodir}/%{name}.info %{_infodir}/dir || :
%preun
if [ $1 = 0 ] ; then
/sbin/install-info --delete %{_infodir}/%{name}.info %{_infodir}/dir || :
fi
```

还有一个安装 info 手册时的小问题。`install-info` 命令会更新 info 目录，所以我们应该在 `%install` 阶段删除 %{buildroot} 中无用的空目录： 

```
rm -f %{buildroot}%{_infodir}/dir
```

另一个类似代码片段的功能是 "triggers"（触发器），它可以在其他软件包安装或删除时，为你的包执行一些动作。请参考 [RPM Triggers](http://rpm.org/api/4.4.2.2/triggers.html)。 

### 宏

宏通常以 `%{string}` 格式出现，以下介绍常见的宏： 

| 宏名称               | 典型扩展               | 意义                                                         |
| -------------------- | ---------------------- | ------------------------------------------------------------ |
| `%{_bindir}`         | `/usr/bin`             | 二进制目录：保存可执行文件                                   |
| `%{_builddir}`       | `~/rpmbuild/BUILD`     | 构建目录：软件在 build 的子目录被编译。参考 `%buildsubdir`   |
| `%{buildroot}`       | `~/rpmbuild/BUILDROOT` | Build root：`%install` 阶段中，将 `%{_builddir}` 子目录下的文件复制到 `%{buildroot}` 的子目录（之前，`%{buildroot}` 使用的位置为 "/var/tmp/"） |
| `%{buildsubdir}`     | `%{_builddir}/%{name}` | 构建子目录：`%build` 阶段中，文件会在 `%{_builddir}` 的子目录中编译。此宏在 `%autosetup` 之后设置 |
| `%{_datadir}`        | `/usr/share`           | 共享数据目录                                                 |
| `%{_defaultdocdir}`  | `/usr/share/doc`       | 默认文档目录                                                 |
| `%{dist}`            | `.fc*NUMBER*`          | 发行版名称+版本号（例如 "`.fc31`"）                          |
| `%{fedora}`          | `*NUMBER*`             | Fedora 发行版本号（例如 "`31`"）                             |
| `%{_includedir}`     | `/usr/include`         | 程序头文件目录                                               |
| `%{_infodir}`        | `/usr/share/info`      | info 手册目录                                                |
| `%{_initrddir}`      | `/etc/rc.d/init.d`     | init 脚本目录                                                |
| `%{_libdir}`         | `/usr/lib`             | 共享库目录                                                   |
| `%{_libexecdir}`     | `/usr/libexec`         | 仅由系统调用执行该目录中的命令                               |
| `%{_localstatedir}`  | `/var`                 | 保存缓存/日志/lock等信息的目录                               |
| `%{_mandir}`         | `/usr/share/man`       | man 手册目录                                                 |
| `%{name}`            |                        | 软件包名称，通过 Name: tag 设置                              |
| `%{_sbindir}`        | `/usr/sbin`            | 保存管理员可执行命令                                         |
| `%{_sharedstatedir}` | `/var/lib`             | 保存程序运行所处理的文件                                     |
| `%{_sysconfdir}`     | `/etc`                 | 配置文件目录                                                 |
| `%{version}`         |                        | 软件包版本，通过 Version: tag 设置                           |

您可以查看 `/etc/rpm/*` 和 `/usr/lib/rpm`，以及 `/usr/lib/rpm/macros` 以进一步了解宏。或使用 `rpm --showrc` 显示当前 RPM 所使用的宏变量和值（根据 `rpmrc` 和宏配置文件）。 

您可以使用 %global 来定义自己的宏，但在使用前需要先进行定义。（宏变量定义时，可以利用嵌套来引用其他宏。）例如： 

```
%global date 2012-02-08
```

使用 `rpmbuild` 的 "`-E`" 选项查找 SPEC 文件中宏变量的值： 

```
rpmbuild -E '%{_bindir}' myfile.spec
```

参考 [Packaging/RPMMacros](https://fedoraproject.org/wiki/Packaging/RPMMacros) 和 [RPM 指南 - 第 9 章](https://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/RPM_Guide/ch09s07.html)。 

### 其它标签

除了 Requires 和 BuildRequires 标签外，你还可以使用以下标签控制依赖关系： 

- Provides

  : 列出此软件包提供的虚拟软件包名称。例如，可能有个 "

  ```
  foo
  ```

  " 软件包需要其他程序的 "bar" 功能；如果有许多软件包可以满足该需求，则这些包可以指定 "

  ```
  Provides: bar
  ```

  "，而 "

  ```
  foo
  ```

  " 包可以指定 "

  ```
  Requires: bar
  ```

  "。你也可以使用 

  "alternatives" 系统

  ，但是若一个系统中有多个用户，不同人可能希望使用不同设置，此时请避免使用它，毕竟此设置为系统全局设置。使用 "

  ```
  rpm -q --provides PACKAGENAME
  ```

  " 查看指定包提供哪些虚拟包。Fedora 中的一些虚拟包示例： 

  - MTA: 邮件传输代理（mail transport agent, MTA），例如 sendmail。
  - tex(latex): 用于 latex

- **Obsoletes**: 当软件包安装时卸载另一个指定的包。用于软件包改名时，或是用该软件包完全取代另一个不同的包时使用。

- **Conflicts**: 表示安装此包时冲突的软件包。如果可以请避免使用此标签。查看 [Packaging/Conflicts](https://fedoraproject.org/wiki/Packaging/Conflicts)。

- **BuildConflicts**: 表示编译此包时冲突的软件包。如果可以请避免使用此标签。

若要处理不同的系统架构，可使用以下 2 个标签： 

- **ExcludeArch**: 排除无法构建此软件包的系统架构。例如：

```
ExcludeArch: ppc
```

- **ExclusiveArch**: 仅包含指定的系统架构。除非绝对正确，否则请避免使用。

可用的系统架构在 [Architectures](https://fedoraproject.org/wiki/Architectures) 中列出。 

### 子软件包

一个 SPEC 文件可以定义多个 RPM 包。换句话说，一个 SRPM 文件可以制作出多个 RPM 包。注意，这仍然只需要一个构建（%prep、%build、%install 等）过程。`name-doc` 和 `name-devel` 是最常见的文档和开发文件子软件包。 

使用 `%package` 宏指令来定义子软件包： 

```
%package subpackage_name
```

在每个 `%package` 指令后，需要列出该子包的必要标签。至少应包括 Summary 和 Group 标签，以及 `%description subpackage_name` 和 `%files subpackage_name` 指令： 

```
%package foo
Summary: 简介
Group: 包组

%description foo
相关描述

%files foo
该包需要包含的文件
```

任何子包中未指定的标签，都会从主包继承。 

默认情况下，如果软件包名为 "`foo`"，而子包名为 "`bar`"，则生成的子包为 "`foo-bar`"。可以使用 "`-n`" 选项指定包名（但需要在所有其它部分添加此选项）： 

```
%package -n new_subpackage_name
```

查看 [RPM 指南 针对子包的章节](http://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/RPM_Guide/ch10s04.html) 了解更多信息。 

### 条件判断

你可以插入条件判断语句，例如可根据特定系统架构执行不同动作： 

```
%ifarch ARCHITECTURE_NAME
```

相反的用法为： 

```
%ifnarch ARCHITECTURE_NAME
```

通用的条件判断用法为： 

```
%if TRUE_OR_FALSE
```

可以选择使用 "`%else`" 字段；条件判断使用 "`%endif`" 结束。 

### 应用程序具体规定

有许多应用程序的具体规定可以帮助你（例：程序语言、应用程序、共享库、构建系统等)。大多都列在 [应用程序专用打包规定](https://fedoraproject.org/wiki/Packaging/Guidelines#Application_Specific_Guidelines)。一些应用程序具体规定的例子有： 

- [Cmake](https://fedoraproject.org/wiki/Packaging:Cmake)
- [Emacs](https://fedoraproject.org/wiki/Packaging:Emacs)

另外，还有一些可以帮你找到应用程序专用规定的方法： 

- Fedoraproject.org 的 'SEARCH' 命令
- [PackagingDrafts](https://fedoraproject.org/wiki/PackagingDrafts)
- [特别兴趣小组（Special Interest Group, SIG）](https://fedoraproject.org/wiki/SIGs)
- [以 'Packaging' 开头的 Wiki 页面](https://fedoraproject.org/wiki/Special:PrefixIndex/Packaging)

### 其他注意事项

[Packaging/FrequentlyMadeMistakes](https://fedoraproject.org/wiki/Packaging/FrequentlyMadeMistakes) 包含常见错误的相关信息。[PackageMaintainers/Packaging Tricks](https://fedoraproject.org/wiki/PackageMaintainers/Packaging_Tricks) 包含一些推荐，以及有争议的技巧。 

请尝试编写你的 SPEC 文件，尽可能在上游更新时使一切都能水到渠成，使你除了修改版本号并刷新源文件外，不需要做其他任何修改。例如，如果要为 *.txt 文件设置执行权限，请不要用： 

```
 chmod a-x Filename1.txt Filename2.txt Filename3.txt
```

而是，考虑使用以下方式处理，可直接处理使用相同命名规则的新文件： 

```
 chmod a-x *.txt
```

如果你想查看大量脚本片段，使用以下命令显示所有已安装包的脚本片段： 

```
 rpm -qa --queryformat "\n\nPACKAGE: %{name}\n" --scripts | less
```

不要尝试和用户交互；RPM 以支持批量安装为设计核心。如果有程序需要显示 EULA 用户授权协议，则应在初次执行时执行该动作，而非安装时。 

建议不要试图启动服务，因为这会使安装过程变得缓慢。如果你安装 init 或 systemd 脚本，请考虑使用 `chkconfig` 或 `systemctl` 安排服务在下次重启时启动/停止该服务。卸载前，如果服务正在运行，一般需要先尝试停止这些服务。 

卸载要尽可能撤消安装阶段中所做的更改，但不要删除任何用户创建的文件。 

一般而言，如果有二进制文件，则会剥离其中包含的调试信息，并将调试信息保存至 `name-debug` 子包中。如果需要禁用此动作，可以在 SPEC 文件顶部添加以下指令： 

```
%global _enable_debug_package 0
%global debug_package %{nil}
%global __os_install_post /usr/lib/rpm/brp-compress %{nil}
```

若要避免执行剥离动作，还需要在 `%install` 部分添加以下变量： 

```
export DONT_STRIP=1
```

通过条件判断的方式，在 SPEC 文件中检查 Fedora 版本： 

```
%if 0%{?fedora} <= <version>
```

`?` 使 `%fedora` 宏在未定义时返回空。这样会使结果为 `0` ，而 `%fedora` 宏若存在数值时也不会有干扰。(注意，这种做法在 Koji "scratch" 编译中不起作用，`%fedora` 的值在创建 SRPM 时已设定） 

GUI 程序必须有桌面条目（desktop entry），以便用户通过图形化菜单启动程序。对于 `.desktop` 文件，请参考 [Fedora packaging guidelines for desktop files](https://fedoraproject.org/wiki/Packaging/Guidelines#Desktop_files) 和 [desktop entry spec](http://standards.freedesktop.org/desktop-entry-spec/latest/)。对于 `/usr/share/icons` 中的图标，请参考 [icon theme spec](http://standards.freedesktop.org/icon-theme-spec/icon-theme-spec-latest.html)。 

## 构建 RPM 包

### 使用 rpmlint 测试

为避免常见错误，请先使用 `rpmlint` 查找 SPEC 文件的错误： 

```
$ rpmlint program.spec
```

如果返回错误/警告，使用 "`-i`" 选项查看更详细的信息。 

有时，`rpmlint` 也会有误报的情况发生。请查看 [打包规定](https://fedoraproject.org/wiki/Packaging/Guidelines#Use_rpmlint) 了解哪些错误可以忽略。 

### 从 SPEC 构建 RPM 包

一旦 SPEC 编写完毕，请执行以下命令来构建 SRPM 和 RPM 包： 

```
$ rpmbuild -ba program.spec
```

如果成功，RPM 会保存至 `~/rpmbuild/RPMS`，SRPM 会保存至 `~/rpmbuild/SRPMS`。 

如果失败，请查看 BUILD 目录的相应编译日志。为了帮助调试，可以用 "`--short-circuit`" 选项来忽略成功的阶段。例如，若想要（略过更早的阶段）重新从 `%install` 阶段开始，请执行： 

```
$ rpmbuild -bi --short-circuit program.spec
```

如果只想创建 SRPM（不需要执行 `%prep` 或 `%build` 或其他阶段），请执行： 

```
rpmbuild -bs program.spec
```

### 使用 rpmlint 测试已构建的 RPM 包

`rpmlint` 用于检查 SPEC/RPM/SRPM 是否存在错误。你需要在发布软件包之前，解决这些警告。[此页面](https://fedoraproject.org/wiki/Common_Rpmlint_issues) 提供一些常见问题的解释。如果你位于 SPEC 目录中，请执行： 

```
$ rpmlint NAME.spec ../RPMS/*/NAME*.rpm ../SRPMS/NAME*.rpm
```

进入 `~/rpmbuild/RPMS` 下的特定架构目录中，您会发现有许多二进制 RPM 包。使用以下命令快速查看 RPM 包含的文件和权限： 

```
$ rpmls *.rpm
```

如果看上去正常，以 root 身份安装它们： 

```
# rpm -ivp package1.rpm package2.rpm package3.rpm ...
```

以不同方式来测试程序，看看是否全部都正常工作。如果是 GUI 工具，请确认其是否出现在桌面菜单中，否则表示 `.desktop` 条目可能有错。 

最后卸载软件包： 

```
# rpm -e package1 package2 package3
```

## Mock 和 Koji

[Mock](https://fedoraproject.org/wiki/Projects/Mock) 用于在标准环境下，使用 SRPM 来构建二进制 RPM 包的强大工具。这可以暴露出包的构建依赖是否存在问题。如果构建失败，表示可能缺少某些 BuildRequires 编译依赖。请参考 [使用 Mock 测试构建软件包](https://fedoraproject.org/wiki/Using_Mock_to_test_package_builds)。一旦你的账户属于 "`mock`" 组，执行以下命令进行本地构建测试： 

```
$ mock -r fedora-9-i386 rebuild path_to_source_RPM
```

你可以使用 Koji（会使用 `mock`）在各种不同的系统上执行构建，包括你没有的系统架构。[PackageMaintainers/Join](https://fedoraproject.org/wiki/PackageMaintainers/Join) 和 [PackageMaintainers/UsingKoji](https://fedoraproject.org/wiki/PackageMaintainers/UsingKoji) 包含更多有关 Koji 的信息。一旦设置完成，你就可以使用以下命令，在各种平台上测试你的 SRPM： 

```
$ koji build --scratch dist-f9 path_to_source_RPM
```

请将 `dist-f9` 替换为任意 Fedora 发行版本，但不要使用 `dist-rawhide`。记住，`%fedora`、`%fc9` 等宏变量的值都不会在 scratch build 中得到修正，所以如果你的 SPEC 会根据宏变量值来执行不同操作，则不能起作用。 

你的 Koji 构建只依赖 TARGET 发行版软件源中实际存在的软件包。因此，如果你的软件包依赖 Bodhi  中尚未发行的其它软件包，则不能使用 Koji 为已发行的版本进行构建。如果你需要为尚未稳定的版本构建软件包，请通过 Bodhi 提交 Koji  buildroot override 请求。如果你的软件包依赖其他人维护的软件包，请联系其维护者。[在 Bodhi 可以处理 Koji  buildroot override 请求之前，以前的旧方法是在此处提交 rel-eng 请求：https://fedorahosted.org/rel-eng/newticket ，并请求将该软件包加入成为 buildroot override。] 

## 有用的工具

`rpmdevtools` 软件包包含各种有用的工具；"`rpm -qil rpmdevtools`" 将显示此包的相关信息和文件列表。 

- `rpmdev-bumpspec` : 增加 spec 文件的发行版本号，并以当前时间和版本格式添加 changelog 日志：

```
rpmdev-bumpspec --comment=COMMENT --userstring=NAME+EMAIL_STRING SPECFILES
```

DNF 下载插件（DNF 核心插件）也十分有用： 

- `dnf download` : 下载指定软件包的 SRPM 包，示例如下：

```
dnf download --source PACKAGENAME
```

`auto-buildrequires` 软件包有一个好用的工具，可以帮助我们找到合适的 BuildRequires 条目。安装此包后，使用 "`auto-br-rpmbuild`"  替换 "`rpmbuild`"，你就会看到自动生成的 BuildRequires 列表。 

你可能发现 [RUST](http://rust.sourceforge.net/) 蛮好用的（GPL），但是它不能生成符合 Fedora 软件包质量的 SPEC 文件。[Alien](http://kitenet.net/~joey/code/alien/) 可以转换软件包格式；它不能生成干净的 SRPM，但转换已有的软件包或许可以提供一些有用的信息。 

如果你想为 Fedora 打包，请确保您的包已通过 [Fedora Review](https://fedorahosted.org/FedoraReview/) 检查，这有助于确保您的包完全遵守 [Packaging Guideline](https://fedoraproject.org/w/index.php?title=Packaging:Guidelines%3Frd%3DPackaging/Guidelines&action=edit&redlink=1)。 

最后，[docker-rpm-builder](https://github.com/alanfranz/docker-rpm-builder) (APL 2.0) 使用 [Docker](http://www.docker.com) 构建 RPM 包；使用 rpmbuild 构建，目标架构需要与系统架构相同。另外，mock 对于任何目标结�