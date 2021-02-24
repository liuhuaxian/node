# centos 系统问题记录

##### 问题：第一次安装系统时并重新启动，系统的无法找到license文件。导致系统无法启动。

- 解决方案。

  - 确定系统是否安装centos-release安装包，该包的/usr/share/doc/xxxx-release/EULA文件及是这个license文件。

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

    

