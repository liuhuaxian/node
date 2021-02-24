# centos7关机自动进行远程服务器备份

## 编写关机及其重启后执行的脚本

注：实验发现关机及其重启后执行的脚本的脚本中不能嵌套调用其它脚本。

该脚本需要应该与服务程序中ExecStart项相对应。及该脚本名为/home/lhx/reboot.sh

`vim /home/lhx/reboot.sh`

```bash
#!/bin/bash
passwd="123456" 
echo "shutdown or reboot at `date +'%Y%m%d%H%M'`" >> /home/redflag/mock/reboot.log
/usr/bin/expect <<-EOF
spawn rsync -arv /home/redflag/mock/ root@192.168.30.200:/home/liuhuaxian/bak/mock
expect "*password"
send "123456\n"
expect eof
EOF 
```

## 编写关机需要启动的服务，由该服务来启动上面的脚本。

 `vi /usr/lib/systemd/system/rebootSrv.service`

```bash
[Unit]
Description=close services before reboot and shutdown
DefaultDependencies=no 
Before=shutdown.target reboot.target halt.target

[Service] 
Type=oneshot 
ExecStart=/home/lhx/reboot.sh  #your path and filename

[Install]
WantedBy=halt.target reboot.target shutdown.target
```

## 启动服务

然后执行

```bash
[root@localhost lhx]# systemctl enable rebootSrv.service
Created symlink from /etc/systemd/system/halt.target.wants/rebootSrv.service to /usr/lib/systemd/system/rebootSrv.service.
Created symlink from /etc/systemd/system/reboot.target.wants/rebootSrv.service to /usr/lib/systemd/system/rebootSrv.service.
Created symlink from /etc/systemd/system/shutdown.target.wants/rebootSrv.service to /usr/lib/systemd/system/rebootSrv.service.
```

重启关机后就能自动执行`/home/lhx/reboot.sh`该脚本。

