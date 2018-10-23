# ESP32 IPS LCD sample for 1.3" 240x240 and 0.96" 160x80

<a href="https://raw.github.com/ywabiko/esp32/master/images/IPSLCD13.png">
<img src="https://raw.github.com/ywabiko/esp32/master/images/IPSLCD13.png"
 alt="IPS LCD 1.3inch" title="IPS LCD 1.3inch" width="300" />
</a>

<a href="https://raw.github.com/ywabiko/esp32/master/images/IPSLCD096.png">
<img src="https://raw.github.com/ywabiko/esp32/master/images/IPSLCD096.png"
 alt="IPS LCD 0.96inch" title="IPS LCD 0.96inch" width="300" />
</a>

This is pretty straight-forward actually, but it took a while for me to figure out. That's why I'm putting it here just FYI...

## LCD panels
  - [1.3" 240x240](https://www.aliexpress.com/item/High-Definition-1-3-Inch-IPS-TFT-Display-IPS-LCD-Screen-1-3-inch-3-3V/32858069771.html?spm=2114.10010108.1000014.1.5b9c395cDPDbwi&scm=1007.13338.98644.000000000000000&scm_id=1007.13338.98644.000000000000000&scm-url=1007.13338.98644.000000000000000&pvid=56eb900a-1874-4434-af86-8981783a75c0&_t=pvid:56eb900a-1874-4434-af86-8981783a75c0,scm-url:1007.13338.98644.000000000000000)
  - [0.96" 160x80](https://www.aliexpress.com/item/1pcs-IPS-0-96-inch-7P-SPI-HD-65K-Full-Color-OLED-Module-ST7735-Drive-IC/32857836858.html?spm=2114.10010108.1000013.1.49ab2378sNFe3p&scm=1007.13339.90158.0&scm_id=1007.13339.90158.0&scm-url=1007.13339.90158.0&pvid=7943c788-3166-4585-8f1f-e3a2f5d5f12e&_t=pvid:7943c788-3166-4585-8f1f-e3a2f5d5f12e,scm-url:1007.13339.90158.0)

## Pin assignment

  - 1.3"  240x240

| LCD  | <-> | ESP32              |
| ---- | --- | ------------------ |
| GND  | <-> | GND                |
| VCC  | <-> | 3V3                |
| SCL  | <-> | GPIO#18 (VSPI SCK) |
| SDA  | <-> | GPIO#23 (VSPI MOSI)|
| RES  | <-> | GPIO#33            |
| DC   | <-> | GPIO#32            |
| BLK  | <-> | (unused)           |

  - 0.96" 160x80

| LCD  | <-> | ESP32              |
| ---- | --- | ------------------ |
| GND  | <-> | GND                |
| VCC  | <-> | 3V3                |
| SCL  | <-> | GPIO#18 (VSPI SCK) |
| SDA  | <-> | GPIO#23 (VSPI MOSI)|
| RES  | <-> | GPIO#33            |
| DC   | <-> | GPIO#32            |
| CS   | <-> | GPIO#5 (VSPI CS)   |
| BLK  | <-> | (unused)           |

To test 1.3", define USE_IPS_240x240.
To test 0.96", undefine USE_IPS_240x240.



# ESP32 IPS LCD サンプル  (1.3" 240x240 と 0.96" 160x80 用)

最近出回っている安価な IPS LCDを使うサンプルです。
分かってしまえば簡単なんですが意外に苦労したので貼っておきます。

## LCD パネル
  - [1.3" 240x240](https://www.aliexpress.com/item/High-Definition-1-3-Inch-IPS-TFT-Display-IPS-LCD-Screen-1-3-inch-3-3V/32858069771.html?spm=2114.10010108.1000014.1.5b9c395cDPDbwi&scm=1007.13338.98644.000000000000000&scm_id=1007.13338.98644.000000000000000&scm-url=1007.13338.98644.000000000000000&pvid=56eb900a-1874-4434-af86-8981783a75c0&_t=pvid:56eb900a-1874-4434-af86-8981783a75c0,scm-url:1007.13338.98644.000000000000000)
  - [0.96" 160x80](https://www.aliexpress.com/item/1pcs-IPS-0-96-inch-7P-SPI-HD-65K-Full-Color-OLED-Module-ST7735-Drive-IC/32857836858.html?spm=2114.10010108.1000013.1.49ab2378sNFe3p&scm=1007.13339.90158.0&scm_id=1007.13339.90158.0&scm-url=1007.13339.90158.0&pvid=7943c788-3166-4585-8f1f-e3a2f5d5f12e&_t=pvid:7943c788-3166-4585-8f1f-e3a2f5d5f12e,scm-url:1007.13339.90158.0)

## ピン接続

  - 1.3"  240x240

| LCD  | <-> | ESP32              |
| ---- | --- | ------------------ |
| GND  | <-> | GND                |
| VCC  | <-> | 3V3                |
| SCL  | <-> | GPIO#18 (VSPI SCK) |
| SDA  | <-> | GPIO#23 (VSPI MOSI)|
| RES  | <-> | GPIO#33            |
| DC   | <-> | GPIO#32            |
| BLK  | <-> | (unused)           |

  - 0.96" 160x80

| LCD  | <-> | ESP32              |
| ---- | --- | ------------------ |
| GND  | <-> | GND                |
| VCC  | <-> | 3V3                |
| SCL  | <-> | GPIO#18 (VSPI SCK) |
| SDA  | <-> | GPIO#23 (VSPI MOSI)|
| RES  | <-> | GPIO#33            |
| DC   | <-> | GPIO#32            |
| CS   | <-> | GPIO#5 (VSPI CS)   |
| BLK  | <-> | (unused)           |

1.3"を接続する場合、 USE_IPS_240x240 マクロを定義してください。

0.96" を接続する場合, USE_IPS_240x240 マクロを未定義にしてください。



## License

This work is derived from graphicstest in Adafruit-GRFX-Library.
https://github.com/adafruit/Adafruit-GFX-Library

This work is licensed under the Creative Commons Attribution 4.0
International License. To view a copy of this license, visit
http://creativecommons.org/licenses/by/4.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

