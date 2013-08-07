
export stl_root := $(PWD)

.PHONY: all clean test test_clean

all: test

test:
	$(MAKE) -C testsuite

clean: test_clean

test_clean:
	$(MAKE) -C testsuite clean

