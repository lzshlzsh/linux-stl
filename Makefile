
export stl_root := $(PWD)
export CXX := g++
export CXXFLAGS := -g -Wall -Werror

.PHONY: all clean test test_clean stl stl_clean format

all: stl test

stl:
	$(MAKE) -C src
test:
	$(MAKE) -C testsuite

clean: test_clean stl_clean

test_clean:
	$(MAKE) -C testsuite clean

stl_clean:
	$(MAKE) -C src clean

format:
	@for i in `find src testsuite -name "*.h" -o -name "*.cpp"` \
		`find include -type f`; do \
		sed -i -e 's/	/    /g' -e 's///g' $$i; \
		done
