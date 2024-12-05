# 安装方法

read dwm/README

[dwm - ArchWiki](https://wiki.archlinux.org/title/Dwm)

```sh
sudo apt install libx11-dev libxft-dev libxinerama-dev
sudo apt install amixer xbacklight # 设置音量、亮度
git clone https://git.suckless.org/dwm
# Alt+P a quick menu
git clone https://git.suckless.org/dmenu

# change config.h

# Atl+Shift+Enter will open the `termcmd`
# change to your terminal (st is too rough...)
# static const char *termcmd[]  = { "xfce4-terminal", NULL };

cd dwm
make && sudo make install

cd dmenu
sudo make clean install
```

## 启动方法

`sudo systemctl set-default multi-user.target` 默认进入tty界面

网上都说创建`~/.xinitrc`，在里面写自定义的启动项+`exec dwm`，然后在tty中用`starx`启动，但总是有些软件在进入dwm后会“水土不服”。所以一步一步看看`startx`是怎么启动的。

`man startx`，下面这几个文件是试图执行的顺序
```sh
$(HOME)/.startxrc
/usr/lib/x86_64-linux-gnu/sys.startxrc
$(HOME)/.xinitrc
/etc/X11/xinit/xinitrc
```

前三者默认都不存在，所以系统默认执行`/etc/X11/xinit/xinitrc`
```sh
$ cat /etc/X11/xinit/xinitrc
#!/bin/sh

# /etc/X11/xinit/xinitrc
#
# global xinitrc file, used by all X sessions started by xinit (startx)

# invoke global X session script
. /etc/X11/Xsession
```

发现它又去找`/etc/X11/Xsession`执行，做了一些定义（`man Xsession` "DEFAULT STARTUP PROCEDURE"），包括：
```sh
USRRESOURCES=$HOME/.Xresources

USERXSESSION=$HOME/.xsession
USERXSESSIONRC=$HOME/.xsessionrc
ALTUSERXSESSION=$HOME/.Xsession
```

最后去`/etc/X11/Xsession.d`目录下按顺序执行各个脚本（`man Xsession` "SUPPLIED SCRIPTS"）：
- /etc/X11/Xsession.d/20x11-common_process-args
    > 如果只是`startx`（不带任何参数），那就什么都不做
- /etc/X11/Xsession.d/30x11-common_xresources
    > 加载`xrdb -merge $USRRESOURCES`，也就是`xrdb -merge ~/.Xresources`，里面可以指定Cursor的theme
- /etc/X11/Xsession.d/35x11-common_xhost-local
- /etc/X11/Xsession.d/40x11-common_xsessionrc
    > `. "$USERXSESSIONRC"`，也就是执行`~/.xsessionrc`（这里面不应该有`exec`，如果有的话，下面的配置就不会执行了）
- /etc/X11/Xsession.d/50x11-common_determine-startup
    > 如果环境变量中`STARTUP`为空（`STARTUP=dwm startx`，到这里时`STARTUP`就非空），则尝试把`~/.xsession`或`~/.Xsession`作为`STARTUP`
    > 
    > 如果这两个文件不存在，则设置`STARTUP`为`x-session-manager`或`x-window-manager`或`x-terminal-emulator`
- /etc/X11/Xsession.d/90x11-common_ssh-agent
- /etc/X11/Xsession.d/99x11-common_start
    > `exec $STARTUP`最终运行`STARTUP`

> 上面的只是系统初始自带的脚本
>
> `/etc/X11/Xsession.d`下还包括你装的软件的启动脚本，比如`20dbus_xdg-runtime`、`70im-config_launch`等等，如果不执行这些，自然就会出现某些软件“水土不服”的现象

所以最“非侵入性”的启动方法应该为：
- `~/.xsessionrc`中设置自定义的启动项（最后不用`exec dwm`），使用`STARTUP=dwm startx`进行启动
- 或，`~/.xsession`中设置自定义的启动项+最后一句`exec dwm`，使用`startx`进行启动

## 使用方法

read dwm/config.h

https://ratfactor.com/dwm

## patch

```
wget https://dwm.suckless.org/patches/deck/
git apply ./dwm-deck-6.2.diff
```

# 自定义的启动项

```
sudo apt install arandr feh redshift
```

## statusbar

在`~/.xsession`中加一行`bash ~/.statusbar &`，用于启动`.statusbar`的shell脚本

`.statusbar`中死循环`xsetroot -name "Status Info"`

> 有些unicode的符号显示不出来，去安装[nerd fonts](https://github.com/ryanoasis/nerd-fonts)

## 自动选择屏幕

`xrandr`设置屏幕，用`arandr`GUI软件很方便，可以导出`xrandr`脚本，供`~/.xsession`使用

## 自动设置背景

`~/.xsession`中
```
feh --no-fehbg --bg-fill ~/bg.jpg
```

## 自动设置色温

`~/.xsession`中
```
redshift -x
redshift -O 4000
```

## VSCode Keyring

[Configure the keyring to use with VS Code](https://code.visualstudio.com/docs/editor/settings-sync#_recommended-configure-the-keyring-to-use-with-vs-code)

VSCode Preferences: Configure Runtime Arguments `"password-store":"gnome-libsecret"`

## cursor

`~/.Xresources`中
```
Xcursor.theme: StrongholdCursor
```

## config touchpad

sudo nano /etc/X11/xorg.conf.d/30-touchpad.conf
```
Section "InputClass"
    Identifier "touchpad"
    Driver "synaptics"
    MatchIsTouchpad "on"
    Option "Tapping" "on"
    Option "ClickMethod" "clickfinger"
    Option "DisableWhileTyping" "on"
    Option "MiddleEmulation" "on"
    Option "NaturalScrolling" "on"
EndSection
```
