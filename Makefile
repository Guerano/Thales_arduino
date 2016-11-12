ARDUINO?=arduino
ARDUINO_COMPILE=--verify
ARDUINO_UPLOAD=--upload
ARDUINO_BOARD?=uno
ARDUINO_PORT?=/dev/ttyACM0
ARDUINO_FLAGS=--pref board=$(ARDUINO_BOARD) --pref serial.port=$(ARDUINO_PORT)

SRC_DIR=thales
MAIN_INO=$(SRC_DIR).ino

all:upload

upload:ARDUINO_FLAGS+=$(ARDUINO_UPLOAD)
upload:launch

check:ARDUINO_FLAGS+=$(ARDUINO_COMPILE)
check:launch

.ONESHELL:
launch:$(addprefix $(SRC_DIR)/,$(MAIN_INO))
	cd $(SRC_DIR)
	$(ARDUINO) $(ARDUINO_FLAGS) $(notdir $^)

.PHONY: upload check launch
