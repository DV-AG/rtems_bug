To reproduce this bug the following requirements must be must:

- configured, built and installed zynqmp_qemu BSP of aarch64 toolchain.
- Having RTEMS built with RTEMS_DEBUG = True in your config.ini.

Do the following things to reproduce the bug:

- Go to your app folder in quick-start.
- clone this repo into a folder named rtems_bug
- run the following commands:

./waf clean

./waf configure --rtems=$(Your path to quick-start folder)/quick-start/rtems/7 --rtems-bsp=aarch64/zynqmp_qemu

./waf

qemu-system-aarch64 \
-machine xlnx-zcu102 \
-m 1024 \
-nographic \
-no-reboot \
-kernel build/aarch64-rtems7-zynqmp_qemu/hello.exe
