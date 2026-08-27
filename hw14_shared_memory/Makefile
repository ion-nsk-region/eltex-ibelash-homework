BUILD_DIR = $(CURDIR)/build
EX1_SYSV_DIR = ex1_sysv
EX1_POSIX_DIR = ex1_posix
EX2_DIR = ex2

all: ex1_sysv ex1_posix ex2

$(BUILD_DIR):
	mkdir -p $@

ex1_sysv: $(BUILD_DIR)
	-$(MAKE) -C $(EX1_SYSV_DIR)

ex1_posix: $(BUILD_DIR)
	-$(MAKE) -C $(EX1_POSIX_DIR)

ex2: $(BUILD_DIR)
	-$(MAKE) -C $(EX2_DIR)

clean:
	find -name "*~" -delete
	rm -rvf build

.PHONY: all ex1_sysv ex1_posix ex2 clean
