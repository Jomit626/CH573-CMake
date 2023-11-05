# cross compile
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR CH573)
set(CMAKE_CROSSCOMPILING 1)

# setup toolchains

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}-ld)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}-ar)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}-objdump)
set(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}-ranlib)

set(CH573_FLAGS
  -march=rv32imac
  -mabi=ilp32
  -mcmodel=medany
  -msmall-data-limit=8
  -mno-save-restore
  -Os -g
  -fmessage-length=0
  -fsigned-char
  -ffunction-sections
  -fdata-sections
  -fno-common
  -std=c99
)

set(CH573_LINK_FLAGS
  -T ${CMAKE_CURRENT_LIST_DIR}/Ld/Link.ld
  -nostartfiles
  -Wl,--print-memory-usage
  -Wl,--gc-sections
  --specs=nano.specs
  --specs=nosys.specs
)

set(CH573_ASM_FLAGS
  ${CH573_FLAGS}
  -x assembler-with-cpp
)

string(REPLACE ";" " " CH573_FLAGS_STR "${CH573_FLAGS}")
string(REPLACE ";" " " CH573_LINK_FLAGS_STR "${CH573_LINK_FLAGS}")
string(REPLACE ";" " " CH573_ASM_FLAGS_STR "${CH573_ASM_FLAGS}")

set(CMAKE_C_FLAGS_INIT ${CH573_FLAGS_STR})
set(CMAKE_CXX_FLAGS_INIT ${CH573_FLAGS_STR})
set(CMAKE_ASM_FLAGS_INIT ${CH573_ASM_FLAGS_STR})

set(CMAKE_EXE_LINKER_FLAGS_INIT ${CH573_LINK_FLAGS_STR})

set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)

enable_language(C CXX ASM)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/RVMSIS
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/inc
)

link_directories(${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver)
link_libraries(ISP573)


set(CH573_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Startup/startup_CH573.S
  ${CMAKE_CURRENT_LIST_DIR}/RVMSIS/core_riscv.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_adc.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_clk.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_flash.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_gpio.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_pwm.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_pwr.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_spi0.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_sys.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_timer0.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_timer1.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_timer2.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_timer3.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_uart0.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_uart1.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_uart2.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_uart3.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_usbdev.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_usbhostBase.c
  ${CMAKE_CURRENT_LIST_DIR}/StdPeriphDriver/CH57x_usbhostClass.c
)
