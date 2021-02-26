.DEFAULT_GOAL := all
.PHONY: run clean gen

include smk_out.mk

gen:
	smk tungsten.smk smk_out.mk

all: $(BUILD_DIR)/tungsten $(BUILD_DIR)/slev
slev: $(BUILD_DIR)/slev

run: all
	$(BUILD_DIR)/tungsten

debug: FLAGS += -g
debug: clean all

clean:
	rm $(BUILD_DIR)/*
