# QT dbus

### QDBusInterface remoteApp(char * dbus_name, char *dbus_obj, char * interface);

| 参数      | 描述                       |
| --------- | -------------------------- |
| dbus_name | 挂载在dbus总线上的总线名称 |
| dbus_obj  | 对象路径名称               |
| interface | 接口名称                   |

函数功能，创建一个QDBusInterface 

QDBusInterface类是远程对象上接口的代理。

QDBusInterface是一个通用访问器类，用于调用远程对象、连接到远程对象导出的信号以及获取/设置远程属性的值。这个类对于动态访问远程对象非常有用：也就是说，当您没有表示远程接口的生成代码时。