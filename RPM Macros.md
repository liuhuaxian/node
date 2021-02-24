# RPM Macros

RPM provides a rich set of macros to make package maintenance simpler and consistent across packages. For example, it includes a list of default path definitions which are used by the build system macros, and definitions for RPM package build specific directories. They usually should be used instead of hard-coded directories. It also provides the default set of compiler flags as macros, which should be used when compiling manually and not relying on a build system.

 RPM提供了一组丰富的宏，可以使软件包的维护更加简单和一致。 例如，它包括构建系统宏使用的默认路径定义列表，以及RPM软件包构建特定目录的定义。 通常应使用它们而不是硬编码目录。 它还提供了默认的编译器标志集作为宏，应该在手动编译而不依赖于构建系统时使用它们。 

## Getting and setting Macros on the command line

It’s possible to let RPM evaluate arbitrary strings containing macros on the command line by running `rpm --eval` on the command line:

通过在命令行上运行rpm --eval，可以让RPM在命令行上评估包含宏的任意字符串： 

```
$ rpm --eval "some text printed on %{_arch}"
some text printed on x86_64
```

Additionally, values for macros can be temporarily provided (and overridden) by providing command line options to `rpm` and `rpmbuild`:

```
$ rpm --define "test Hello, World!" --eval "%{test}"
Hello, World!
```

## Macros for paths set and used by build systems

The macros for build system invocations (for example, `%configure`, `%cmake`, or `%meson`) use the values defined by RPM to set installation paths for packages. So, it’s usually preferable to not hard-code these paths in spec files either, but use the same macros for consistency.

The values for these macros can be inspected by looking at `/usr/lib/rpm/platform/*/macros` for the respective platform.

The following table lists macros which are widely used in fedora `.spec` files.

用于生成系统调用的宏（例如，％configure，％cmake或％meson）使用RPM定义的值来设置软件包的安装路径。 因此，通常最好也不要在规范文件中对这些路径进行硬编码，而是使用相同的宏来保持一致性。 

可以通过查看相应平台的/ usr / lib / rpm / platform / * / macros来检查这些宏的值。 

下表列出了在fedora .spec文件中广泛使用的宏。

| macro                | definition                | comment                                     |
| -------------------- | ------------------------- | ------------------------------------------- |
| `%{_sysconfdir}`     | `/etc`                    |                                             |
| `%{_prefix}`         | `/usr`                    | can be defined to `/app` for flatpak builds |
| `%{_exec_prefix}`    | `%{_prefix}`              | default: `/usr`                             |
| `%{_includedir}`     | `%{_prefix}/include`      | default: `/usr/include`                     |
| `%{_bindir}`         | `%{_exec_prefix}/bin`     | default: `/usr/bin`                         |
| `%{_libdir}`         | `%{_exec_prefix}/%{_lib}` | default: `/usr/%{_lib}`                     |
| `%{_libexecdir}`     | `%{_exec_prefix}/libexec` | default: `/usr/libexec`                     |
| `%{_sbindir}`        | `%{_exec_prefix}/sbin`    | default: `/usr/sbin`                        |
| `%{_datadir}`        | `%{_datarootdir}`         | default: `/usr/share`                       |
| `%{_infodir}`        | `%{_datarootdir}/info`    | default: `/usr/share/info`                  |
| `%{_mandir}`         | `%{_datarootdir}/man`     | default: `/usr/share/man`                   |
| `%{_docdir}`         | `%{_datadir}/doc`         | default: `/usr/share/doc`                   |
| `%{_rundir}`         | `/run`                    |                                             |
| `%{_localstatedir}`  | `/var`                    |                                             |
| `%{_sharedstatedir}` | `/var/lib`                |                                             |
| `%{_lib}`            | `lib64`                   | `lib` on 32bit platforms                    |

Some seldomly used macros are listed below for completeness. Old `.spec` files might still use them, and there might be cases where they are still needed.

 为了完整性，下面列出了一些很少使用的宏。 旧的.spec文件可能仍会使用它们，并且在某些情况下仍然需要它们。 

| macro             | definition                   | comment                                    |
| ----------------- | ---------------------------- | ------------------------------------------ |
| `%{_datarootdir}` | `%{_prefix}/share`           | default: `/usr/share`                      |
| `%{_var}`         | `/var`                       |                                            |
| `%{_tmppath}`     | `%{_var}/tmp`                | default: `/var/tmp`                        |
| `%{_usr}`         | `/usr`                       |                                            |
| `%{_usrsrc}`      | `%{_usr}/src`                | default: `/usr/src`                        |
| `%{_initddir}`    | `%{_sysconfdir}/rc.d/init.d` | default: `/etc/rc.d/init.d`                |
| `%{_initrddir}`   | `%{_initddir}`               | old misspelling, provided for compatiblity |

## Macros set for the RPM (and SRPM) build process

RPM also exposes the locations of several directories that are relevant to the package build process via macros.

The only macro that’s widely used in `.spec` files is `%{buildroot}`, which points to the root of the installation target directory. It is used for setting `DESTDIR` in the package’s `%install` step.

The other macros are usually only used outside `.spec` files. For example, they are set by `fedpkg` to override the default directories.

RPM还通过宏公开了与软件包构建过程相关的几个目录的位置。 

.spec文件中唯一被广泛使用的宏是％{buildroot}，它指向安装目标目录的根。 它用于在软件包的％install步骤中设置DESTDIR。 

其他宏通常仅在.spec文件外部使用。 例如，它们由fedpkg设置以覆盖默认目录。

| macro              | definition                                                | comment              |
| ------------------ | --------------------------------------------------------- | -------------------- |
| `%{buildroot}`     | `%{_buildrootdir}/%{name}-%{version}-%{release}.%{_arch}` | same as `$BUILDROOT` |
| `%{_topdir}`       | `%{getenv:HOME}/rpmbuild`                                 |                      |
| `%{_builddir}`     | `%{_topdir}/BUILD`                                        |                      |
| `%{_rpmdir}`       | `%{_topdir}/RPMS`                                         |                      |
| `%{_sourcedir}`    | `%{_topdir}/SOURCES`                                      |                      |
| `%{_specdir}`      | `%{_topdir}/SPECS`                                        |                      |
| `%{_srcrpmdir}`    | `%{_topdir}/SRPMS`                                        |                      |
| `%{_buildrootdir}` | `%{_topdir}/BUILDROOT`                                    |                      |

## Macros providing compiler and linker flags

The default build flags for binaries on fedora are also available via macros. They are used by the build system macros to setup the build environment, so it is usually not necessary to use them directly — except, for example, when doing bare bones compilation with `gcc` directly.

The set of flags listed below reflects the current state of fedora 28 on a `x86_64` machine, as defined in the file `/usr/lib/rpm/redhat/macros`.

The `%{optflags}` macro contains flags that determine `CFLAGS`, `CXXFLAGS`, `FFLAGS`, etc. — the `%{__global_cflags}` macro evaluates to the same string.

The current definitions of these values can be found in the `redhat-rpm-macros` package, in the [build flags documentation](https://src.fedoraproject.org/rpms/redhat-rpm-config/blob/master/f/buildflags.md).

fedora上二进制文件的默认构建标志也可以通过宏获得。 构建系统宏使用它们来设置构建环境，因此通常不需要直接使用它们-例如，直接用gcc进行裸机编译时除外。 

下面列出的标志集反映了x86_64机器上fedora 28的当前状态，如文件/ usr / lib / rpm / redhat / macros中所定义。 

％{optflags}宏包含确定CFLAGS，CXXFLAGS，FFLAGS等的标志。-%% {__ global_cflags}宏计算为同一字符串。 

这些值的当前定义可以在redhat-rpm-macros软件包的构建标志文档中找到。

```bash
$ rpm --eval "%{optflags}"
-O2 -g -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -fexceptions -fstack-protector-strong -grecord-gcc-switches -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1 -m64 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection
```

The value of the `LDFLAGS` environment variable set by build systems is determined by the `%{build_flags}` macro:

 构建系统设置的LDFLAGS环境变量的值由％{build_flags}宏确定： 

```bash
$ rpm -E "%{build_ldflags}"
-Wl,-z,relro  -Wl,-z,now -specs=/usr/lib/rpm/redhat/redhat-hardened-ld
```