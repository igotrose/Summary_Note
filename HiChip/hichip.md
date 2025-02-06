# 海奇
## 开发环境搭建
ubuntu18.04.06
1. VMware Tools 的安装
    1. 点击虚拟机，重新安装 VMware Tools，如果时按钮灰色的，关闭虚拟机，设置 CD\DVD为自动检测，打开虚拟机
    2. 挂载 VMware Tools 安装光盘，通常 VMware Tools 会挂载在 /media/cdrom 或 /mnt/cdrom 目录下
    3. 
2. 更换镜像源，首先将源文件做一个备份
        
        sudo cp /etc/apt/sources.list /etc/apt/sources.bak1
        sudo apt update
3. 安装一系列工具
    - 基础开发工具
      ```bash
        sudo apt install git gcc make cmake automake ninja-build pkg-config tree rename
      ```
    - C/C++ 相关工具
      ```bash
        sudo apt install git gcc make cmake automake ninja-build pkg-config tree rename
      ```
    - Python 相关
      ```bash
      sudo apt install python3 python3-pip python3-dev python3-setuptools python3-wheel python3-venv
      sudo apt install python3-pybind11 swig  
      sudo pip3 install fdt  
      ```

    - 其他实用工具
      ```bash
      sudo apt install unzip rar dos2unix lzip lzma lzop texinfo re2c doxygen graphviz
      ```
    - 文件系统与工具
      ```bash
    sudo apt install mtools mtd-tools genromfs
      ```

    - 安全和压缩库
        ```bash
      sudo apt install libssl-dev libtool
        ```
4. 获取解压下载工具链和SDK放置自己的工作目录下
        
        tar -xvf Codescape.GNI.Tools.Packge*\
        ls /opt/mips32-mti-elf/2019.09-03-2/bin/ -l
## 设置第三方软件的本地下载路径
将第三方软件包下载到本地路径 **/media/data/dl**        
hcrtos sdk默认会尝试从 **http://hichip01/dl** 进行下载，该路径是海奇内部网络建立的http server，
外部网络无法连接，从而sdk尝试失败后会从公开网络去下载。    
    
    cd hcrtos
    make menuconfig
    Mirrors and Download locations
    (file:///media/data/dl) Primary download site
## 确认软件版本
    git branch –av
## 软件开发前准备工作
1. 确认上电正常
2. 确认板子型号
3. 确认板子DDR型号
4. 确认板子屏幕类别
5. 确认板子外围功能
6. 确认板子电源电压，等需要接线是否连接正确
## 软件设计和目录介绍
#### 海奇hcrtos软件框架
* 海奇hcRTOS系统应用是采用Hcboot来引导启动的
* Hcboot基于hcRTOS开发平台进行开发，但又独立于hcRTOS，经过深度裁减后用于引导和启动hcRTOS系统固件。
* Hcboot经过深度裁剪后，剩余引导hcRTOS的功能、show logo功能、升级检测功能等一些基本的功能，也可以认为是一个小应用，开发者也可以进行响应的开发。
#### SDK目录
- bl            // bootloader
  - build
  - host
  - staging
- board         // 板级配置
  - hc15xx
  - hc16xx
  - hc1xxx
- build         // 编译组织makefile和脚本相关
  - download
  - gnuconfig
  - kconfig
  - misc
  - scripts
  - tools
- components    // 组件部分
  - applications
  - bluetooth
  - cjson
  - cmds
  - dtc
  - ffmpeg
  - freetype
  - hccast
  - hc-examples
  - hcfota
  - hclib
  - hctinyplayer-registry
  - hudi
  - kernel
  - ld
  - libcurl
  - libev
  - liblvgl
  - liblzo
  - libogg
  - libopenssl
  - libssp
  - libuac
  - libusb
  - libuvc
  - libvorbis
  - libwebsockets
  - lzo1x
  - mbedtls
  - memtester
  - newlib
  - opencore-amr
  - opus
  - pcre
  - prebuilts
  - pthread
  - quicklz
  - speex
  - uboot-tools
  - unity
  - wolfssl
  - zlib
- configs       // 压缩算法 
- dl            
  - cjson
  - dtc
  - libcurl
  - libogg
  - pcre
  - speex
  - wolfssl
  - zlib
- document      // 海奇开发文档
- hrepo
- Kconfig       // 总配置文件
- Makefile      // 总Makefile文件
- output        // app编译中间文件和编译输出文件，默认最终输出文件夹未output
  - build
  - host
  - images
  - include
  - staging
- output-bl     // bootloader输出文件。文件夹名字来自于编译时的O=xxx
  - build
  - host
  - include
  - staging
- target
  - chip
  - Kconfig
## 软件配置的选择
### deconfig 和 dts
* deconfig 通常指的是取消或关闭某个功能或配置
* dts 是设备树源文件（Device Tree Source）的缩写，它用于描述硬件设备的配置信息

在设备树的上下文中，deconfig 可能意味着关闭某些硬件功能或设备节点配置。例如，当你想禁用某个外设或不使用某个硬件功能时，可能会在设备树中进行相应的修改，删除或注释掉相关配置。比如，你不再使用某个外设，可能会从 dts 文件中移除它的配置。
一个常见的 deconfig 操作可能是禁用某个外设节点，类似于这样：

    &uart1 {
        status = "disabled";
    };
这将禁用 uart1 外设，等效于将该外设的状态设置为“禁用”。
#### deconfig的选择
1. 软件顶层总配置在 ** hcrtos/configs **目录下，根据芯片型号和项目需求，选择对应defconfig
    
    ls configs  // 可以进行查看
    |配置文件|说明|
    |-------|----|
    |hcrtos/configs/hichip_hc16xx_db_d3100_v30_projector_cast_bl_defconfig|用于生成hcboot 的配置文件|
    |hcrtos/configs/hichip_hc16xx_db_d3100_v30_projector_cast_defconfig|用于生成固件|
2. 配置文件命名规则

        hichip_hc16xx_db_d3100_v30_projector_cast_bl_defconfig  
    * hichip    ：芯片原厂
    * hc16xx    ：海奇一代芯片为hc15xx，二代芯片为hc16xx  
    * db        ：db表示demo board，cb表示custom board 
    * d3100     ：芯片型号
    * v30       ：表示硬件版本为V30
    * projector ：该项为app大功能配置。projector为投影仪方案，hcscreen为同屏器方案，hcdemo仅做参考app
    * cast      ：表示该配置带有无线同屏功能
    * bl        ：bl表示编译hcboot的配置，不带bl表示编译hcrtos sdk的配置，两个配置是配对的，缺一不可
    * defconfig ：Linux内核中默认的配置文件的后缀   

***开发者开发项目是，根据需求选择相近的配置进行编译。如原厂配置据不符合项目需求，则需要开发者自行根据项目需求配置deconfig***
#### dts的选择
默认deconfig会定义相关dts路径

    $ grep 'CONFIG_CUSTOM_DTS_PATH' configs/hichip_hc16xx_db_d3100_v30_projector_cast_defconfig
    > CONFIG_CUSTOM_DTS_PATH="$(TOPDIR)/board/hc16xx/common/dts/hc16xx-db-d3100-v30.dts $(TOPDIR)/board/hc16xx/common/dts/lcd/*.dtsi"
该defconfig编译时用到的
* dts为 /board/hc16xx/common/dts/hc16xx-db-d3100-v30.dts 
* 配屏文件dtsi为 /board/hc16xx/common/dts/lcd/*.dtsi      

**开发者可以自行定义dts和dtsi文件的路径，但必须保证hcboot和hcrtos用的是用一个dts和dtsi，且设备树的名字也要修改**
#### 配屏文件的选择
#### DDR配置选择
DDR 是一种常见的内存技术，用于存储数据，它在现代嵌入式系统和计算机中得到了广泛应用。    
ddr文件的选择主要有以下四个方面需要注意：
1. ddr2还是ddr3？
2. 容量大小是多少？
3. 频率用多少？
4. gdb用的ddr文件如何选择？

* ddr的文件路径位于

        board/hc16xx/common/ddrinit/
* gdb工具选用的ddr文件路径位于

        board/hc16xx/common/ddrinit/gdb/

**gdb路径中的ddr文件仅用于gdb工具烧录和调试用**

        hc16xx_ddr3_128M_1066MHz_Refresh3d9us.abs
* hc16xx       ：海奇一代芯片为hc15xx，二代芯片为hc16xx  
* ddr3         : ddr2或者ddr3
* 128M         : ddr容量大小
* 1066MHz      ：工作频率
* Refresh3d9us ：刷新周期
## 编译
#### 编译方法
    ```bash
    make O=output-bl hichip_hc16xx_db_c3100_v20_projector_bl_defconfig 
    make O=output-bl all
    make hichip_hc16xx_db_c3100_v20_projector_defconfig
    make all
    ```
* make        ： 启动构建过程，通常调用Makefile来管理编译任务
* O=output-bl :  指定编译输出目录。O选项是用来设置一个外部构建目录，将所有的编译中间文件、配置文件和最终生成的文件输出到这个目录，而不是默认的当前目录
* defconfig   :  默认配置
* all         :  make的默认目标，表示构建整个目录
#### 常用编译命令
    ```bash
    # 修改了 bootloader 和 dts，需要按如下命令进行重新编译：
    make O=output-bl kernel-clean kernel-rebuild all

    # 进行 bootloader 的配置：
    make O=output-bl menuconfig

    # 进行 app 的配置选项：
    make menuconfig

    # 修改了启视频道支持特性，特别是删除某些音视频特性支持，需要用如下命令：
    make kernel-reconfigure kernel-clean kernel-rebuild all

    # 修改了应用，需要用如下命令：
    make apps-projector-rebuild all

    # 修改了 components/hccast 下的内容，需要：
    make hccast-reconfigure hccast-rebuild all

    # 删除全部编译中间文件：
    rm output-bl -rf

    # 修改了 components/cmds 下的内容：
    make cmds-rebuild all

    # 修改了 lvgl 的配置：
    make liblvgl-reconfigure

    # 修改了 lvgl 的某些配置需要：
    make liblvgl-rebuild all

    # 修改了 components/liblvgl 的代码：
    make liblvgl-rebuild all
    ```
#### 编译完成后
    ```bash
    tree output/images
    ```
- output/images
  - bootloader.bin
  - dtb.bin
  - dtb.fixup.bin
  - for-debug                              
  // 用于RD debug用的，这里面的hcfota.bin包含了全部的文件，而且会忽略版本检查，强制升级。ini文件用于ejtag升级
    - hc16xx_jtag_updater.out
    - HCFOTA.bin
    - HCFOTA.bin.35d86
    - HCFOTA_HC16C3100V20_2501140208.bin
    - HCProgrammer.exe
    - sfburn.ini
  - for-factory
  //spinorflash.bin是用于生成烧录器用的，即贴片生产用的，是flash上对应的烧录文件，用烧录器进行烧录。
    - spinorflash.bin
  - for-net-upgrade
  //这是用于网络升级的，这里面的hcfota.bin与 "for-upgrade"里面的是一样的。 只是这个文件夹还生成了网络配置文件HCFOTA.jsonp
    - 2501140208/
      - HCFOTA.ota.bin
    - HCFOTA.jsonp
  - for-upgrade
  //hcfota.bin“不会忽略版本检查”，“不会包含boot分区“。如需升级boot分区，需要手动执行HCFota_Generator.exe，生成对应的HCFOTA.bin
    - HCFOTA_HC16C3100V20_2501140208.ota.bin
    - HCFOTA.ota.bin
  - fs-partition1-root/
    - HCCAST_1920x1080.264
    - music_bg_logo.264
  - fs-partition2-root/
  - fs-partition3-root/
  - hc16xx-db-c3100-v20.dtb
  - hc16xx_ddr3_128M_800MHz.abs
  - hc16xx_jtag_updater.bin
  - hcboot.bin
  - hcboot.out 
  - hcboot.out.map
  - hcboot.uncompress.bin
  - hcboot.uncompress.out
  - hcboot.uncompress.out.map
  - hcdemo.uImage
  - HCFota_Generator.exe
  - HCFota_Generator.pdb
  - hcprog.ini
  - hcscreen.bin
  - hcscreen.bin.lzma
  - hcscreen.out
  - hcscreen.out.map
  - hcscreen.uImage
  - persistentmem.bin
  - romfs.img
  - user_data
#### 独有配置
## 烧录
#### 烧录方法
|方法|gdb烧录|usb烧录|hcfota升级|串口烧录|hcprogrammer烧录|贴片烧录|
|----|------|-------|----------|-------|----------------|-------|
|优点|开发调试方便，便于跟踪代码，查看疑难问题。开发阶段必备。|较gdb更轻量化。有USB口即可实现。|U盘升级，随插随升。|在没有usb口的板子上容易实现。|只用一条usb公对公的线即可完成，目前主推的烧录方式。|通用烧录器进行烧录，适合于大批量生产，使用的文件路径位于：\output\images\for-factory\spinorflash.bin|
|缺点|需要占用比较多的pin脚，需要硬件设计时预留。|仅二代芯片可用。|仅适用于板子内有程序，且支持hcfota升级，能正常启机的情况，空片无法升级。|速度慢，目前不够稳定，不推荐开发阶段使用。|hc15xx系列芯片不能烧录空片。|需要拆下flash后才能升级。|

**目前使用usb烧录，使用HCprogrammer进行烧录**
