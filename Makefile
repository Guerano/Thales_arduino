ARDUINO?=arduino
ARDUINO_COMPILE=--verify
ARDUINO_UPLOAD=--upload
ARDUINO_BOARD?=uno
ARDUINO_PORT?=/dev/ttyACM0
ARDUINO_BAUD_RATE?=9600
ARDUINO_FLAGS=--pref board=$(ARDUINO_BOARD) --pref serial.port=$(ARDUINO_PORT) \
	      --pref serial.debug_rate=$(ARDUINO_BAUD_RATE)

SRC_DIR=thales
MAIN_INO=$(SRC_DIR).ino

all:upload

upload:ARDUINO_FLAGS+=$(ARDUINO_UPLOAD)
upload:launch

check:ARDUINO_FLAGS+=$(ARDUINO_COMPILE)
check:launch

# Hit ctrl+a k to quit
debug:
	screen $(ARDUINO_PORT) $(ARDUINO_BAUD_RATE)

.ONESHELL:
launch:$(addprefix $(SRC_DIR)/,$(MAIN_INO))
	cd $(SRC_DIR)
	$(ARDUINO) $(ARDUINO_FLAGS) $(notdir $^)

.PHONY: upload check launch debug
