## Thales Arduino Challenge

### Authors
    * Rémi BILLON
    * Quentin L'HOURS
    * Robin REBISCHUNG
    * Anaïs TAING

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
