# 基于gnome的快捷键的设置

## 前提

前提需要安装gnome-settings-daemon-3.28.1-8.axs7.aarch64.rpm

## 分析

`vim /usr/share/glib-2.0/schemas/org.gnome.settings-daemon.plugins.media-keys.gschema.xml `

```xml
<schemalist>
  <schema gettext-domain="gnome-settings-daemon" id="org.gnome.settings-daemon.plugins.media-keys" path="/org/gnome/settings-daemon/plugins/media-keys/">
    <key name="custom-keybindings" type="as">  ===>表明该类型为array string
      <default>[]</default>
      <summary>Custom keybindings</summary>
      <description>List of custom keybindings</description>
        ········
        ········
   </schema>
     <schema gettext-domain="gnome-settings-daemon" id="org.gnome.settings-daemon.plugins.media-keys.custom-keybinding"> ===>表明上面的array string中的每个元素可以包含的字段。
    <key name="name" type="s">
      <default>''</default>
      <summary>Name</summary>
      <description>Name of the custom binding</description>
    </key>
    <key name="binding" type="s">
      <default>''</default>
      <summary>Binding</summary>
      <description>Binding for the custom binding</description>
    </key>
    <key name="command" type="s">
      <default>''</default>
      <summary>Command</summary>
      <description>Command to run when the binding is invoked</description>
    </key>
  </schema>   
</schemalist>
```



## 示例：

设置快捷键`<Ctrl>F5,<Ctrl>F6,<Ctrl>F2<Ctrl>F3` 按下时分别去执行`/usr/bin/atmmode.sh 1 /usr/bin/atmmode.sh 0 /home/lhx/test.sh /home/lhx/test1.sh`

```bash
  gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings '["/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/atmmode/", "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/unatmmode/", "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/test/", "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/untest/"]'
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/atmmode/   name   atmmode
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/atmmode/ command '/usr/bin/atmmode.sh 1'
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/atmmode/ binding '<Ctrl>F5'

  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/unatmmode/ name unatmmode
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/unatmmode/ command '/usr/bin/atmmode.sh 0'
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/unatmmode/ binding '<Ctrl>F6'

  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/test/ name test
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/test/ command '/home/lhx/test.sh'
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/test/ binding '<Ctrl>F2'

  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/untest/ name untest
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/untest/ command '/home/lhx/test.sh'
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/untest/ binding '<Ctrl>F3'
```

## 验证是否成功

```bash
[root@localhost schemas]# gsettings list-recursively org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/atmmode/

org.gnome.settings-daemon.plugins.media-keys.custom-keybinding binding '<Ctrl>F5'
org.gnome.settings-daemon.plugins.media-keys.custom-keybinding command '/usr/bin/atmmode.sh 1'
org.gnome.settings-daemon.plugins.media-keys.custom-keybinding name 'atmmode'
```

