## Thales Arduino Challenge

### Authors
    * Quentin L'HOURS
    * Anaïs TAING
    * Robin REBISCHUNG
    * Rémi BILLON

### Usage

The directory name of the ino file must be the same as the basename of this file
in order to compile it.

Run `make` to compile your files and to upload the binary to the board.
Run `make check` to compile your files without uploading them.

If you're not in the `dialout` group, you will need to execute these commands
with sudo. Or, you can add yourself to the group with the following command:

    `> sudo usermod -a -G dialout $USER`

By default, the board used is an `arduino UNO` and the serial port used is
`/dev/ttyACM0`.
You can change these by either change the make variable `ARDUINO_BOARD` and
`ARDUINO_PORT` or overriding them through your shell environment variable like
the following:

    `> ARDUINO_BOARD="my_board" ARDUINO_PORT="my_port" make`

### Taking pictures

Currently, you can take picture with the Arduino, pressing the button, and it
the picture will be send through Wi-Fi thanks by the ESP8266 Wi-Fi module.

The file `module_ardu.ino` should be flashed on the Arduino UNO. The file
`module_wif.ino` should be flashed on the ESP8266.

#### Wiring

* ESP8266: on the bottom, GND on Arduino GND, V+ on Arduino 5V, Rx and Tx on
  Arduino Tx and Rx
* myled: on Arduino PIN 11
* BUTTon: on Arduino PIN 8
* camera: GND on Arduino GND, 5V on Arduino 5V, TX_A on Arduino PIN 2, RX_A on
  Arduino 3 with two resistors (10k ohm each)

#### Server

The Wi-Fi module will connect on the Wi-Fi network ".wifi-secret" and the given
password (see in file `module_wif.ino`). It will send the picture on the given
server (host: "192.168.43.54", port: "8000", see in the file).

You can set the server as following :

    `nc -l 8000 > img.jpg`

The send picture will be saved in `img.jpg`.
