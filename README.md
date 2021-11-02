# CLight GUI

Clight GUI written in Qt.

Huge thanks to @FedeDP for writing [Clight](https://github.com/FedeDP/Clight) and [Clightd](https://github.com/FedeDP/Clightd/), the daemons upon which this is built on. They are also a requirement for this program ;)

## Features
Please make sure you are using the latest versions of Clight (4.4) and Clightd (5.3) for the best experience!
- Configure all aspects of Clight with a pretty GUI!
- Tray applet with quick access to settings (scroll on it to change brightness!)
- Minimize to tray by closing window

## Building
Requires cmake, Qt5/6, QtXml, and QtCharts. The DBus C++ interfaces are generated based on the XML files for Clight.

```shell
cd clight-gui
cmake -S src -B build # It may be safe to ignore the CMAKE_PREFIX_PATH warning.
cd build
make
sudo make install
# You may need this to update the icons.
sudo gtk-update-icon-cache -f /usr/share/icons/hicolor/
```

## Installing
An AUR package was created by user @yochananmarqos! You can check it out [here](https://aur.archlinux.org/packages/clight-gui-git/). For users of other distributions, the executable is completely portable and requires no other dependencies.

## Screenshots
![tray](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/tray.png)
![context](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/context.png)
![info-tab](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/info-tab.png)
![brightness-tab](https://github.com/nullobsi/clight-gui/blob/main/screenshots/brightness-tab.png)
![sensor-tab](https://raw.githubusercontent.com/nullobsi/clight-gui/main/screenshots/sensor-tab.png)
