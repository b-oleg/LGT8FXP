# Tiny library for the LGT8F328P microcontroller

The LGT8F328P microcontroller is hardware compatible with the ATMega328P, but has more features, this library allows you to take advantage of them.

The library is designed for use with PlatformIO for native C/C++ development using only the AVR-GCC compiler (without Arduino libraries).

Minimum configuration for setting up PlatformIO:

**platformio.ini**

```ini
[env:lgt]
platform = lgt8f
board = LGT8F328P  ; Or your specific MCU board
; framework = <-- Comment or remove this line

; change MCU frequency
board_build.f_cpu = 30000000L

lib_deps =
    https://github.com/b-oleg/LGT8FXP.git
```

In addition, there is a translation of part of the [documentation](https://b-oleg.github.io/LGT8FXP) for the microcontroller.