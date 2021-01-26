# CLight GUI

Clight GUI written in Qt.

Huge thanks to @FedeDP for writing [Clight](https://github.com/FedeDP/Clight) and [Clightd](https://github.com/FedeDP/Clightd/), the daemons upon which this is built on. They are also a requirement for this program ;)

## Features
- Configure all aspects of Clight with a pretty GUI!
- Tray applet with quick access to settings (scroll on it to change brightness!)
- Minimize to tray by closing window

## Building
Requires cmake, Qt5/6, and Qt charts. The DBus C++ interfaces are generated based on the XML files for Clight.

## Installing
An AUR package was created by user @yochananmarqos! You can check it out [here](https://aur.archlinux.org/packages/clight-gui-git/). For users of other distributions, the executable is completely portable and requires no other dependencies.

## Screenshots
![tray](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/tray.png)
![context](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/context.png)
![info-tab](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/info-tab.png)
![brightness-tab](https://github.com/nullobsi/clight-gui/blob/main/screenshots/brightness-tab.png)
![sensor-tab](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/sensor-tab.png)