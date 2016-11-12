ARDUINO?=arduino
ARDUINO_COMPILE=--verify
ARDUINO_UPLOAD=--upload
ARDUINO_BOARD?=uno
ARDUINO_PORT?=/dev/ttyACM0
ARDUINO_FLAGS=--pref board=$(ARDUINO_BOARD) --pref serial.port=$(ARDUINO_PORT)

CUR_DIR=$(shell pwd)
MAIN_INO=$(notdir $(CUR_DIR)).ino

all:upload

upload:ARDUINO_FLAGS+=$(ARDUINO_UPLOAD)
upload:launch

check:ARDUINO_FLAGS+=$(ARDUINO_COMPILE)
check:launch

launch:$(MAIN_INO)
	$(ARDUINO) $(ARDUINO_FLAGS) $^

.PHONY: upload check launch
