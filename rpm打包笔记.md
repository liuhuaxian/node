# rpm打包笔记

## 打补丁命令

补丁文件通常是 "`diff -u`" 命令的输出

## 打印rpm所支持的宏值

```bash
rpm -E "%{?dist}"
```

建立rpm的工作空间

```bash
rpmdev-setuptree
```

## rpmlint检查

为避免常见错误，请先使用 rpmlint 查找 SPEC 文件的错误：

    $ rpmlint program.spec

如果返回错误/警告，使用 “-i” 选项查看更详细的信息。

也可以使用 rpmlint 测试已构建的 RPM 包，检查 SPEC/RPM/SRPM 是否存在错误。你需要在发布软件包之前，解决这些警告。此页面 提供一些常见问题的解释。如果你位于 SPEC 目录中，请执行：

```bash
$ rpmlint NAME.spec ../RPMS/*/NAME*.rpm ../SRPMS/NAME*.rpm
```

进入 ~/rpmbuild/RPMS 下的特定架构目录中，您会发现有许多二进制 RPM 包。使用以下命令快速查看 RPM 包含的文件和权限：

```bash
$ rpmls *.rpm
```

