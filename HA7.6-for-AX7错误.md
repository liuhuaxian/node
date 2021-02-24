### HA7.6-for-AX7错误

```bash
[root@localhost SPECS]# rpmbuild -bs rh-ruby24.spec -D '_topdir /home/redflag/HA7.6-for-AX7/.mockbuild/.build_dir'
error: line 13: Unknown tag: %scl_package rh-ruby24
```

```bash
[lhx@pcmk-1 SPECS]$ rpmbuild -ba rh-ruby24.spec 
错误：构建依赖失败：
	help2man 被 rh-ruby24-2.4-2.el7.x86_64 需要
	scl-utils-build 被 rh-ruby24-2.4-2.el7.x86_64 需要
```

以上错误通过手动修改.spec文件完成

- 文件ha-rflicmgr3.spec报错

  ```bash
  /usr/lib/gcc/x86_64-redflag-linux/4.8.5/../../../../lib64/libgdk-x11-2.0.so: undefined reference to `XRRFreeMonitors'
  /usr/lib/gcc/x86_64-redflag-linux/4.8.5/../../../../lib64/libgdk-x11-2.0.so: undefined reference to `XRRGetMonitors'
  ```

  ```
  yum install libX11-devel.i686//无效
  ```

  

