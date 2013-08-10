stl_root ?= ..

inc_path := $(stl_root)/include
stl_path := $(stl_root)/src/obj
dep_dir := .dep
obj_dir := .obj

__mkdir := $(shell for i in $(dep_dir) $(obj_dir); do \
		[ -d $$i ] || mkdir -p $$i; \
	done \
	)

CXX := g++
CFLAGS := -Wall -g 
LDFLAGS := #-ldl -lpthread #-static

CFLAGS += $(addprefix -I,$(inc_path))
CFLAGS += $(addprefix -L,$(stl_path))
LDFLAGS += -lstl

CXXFLAGS := ${CFLAGS}

files := $(wildcard *.cpp)
target_obj := $(patsubst %.cpp,%.o,${files})
targerts := $(patsubst %.o,%,${target_obj})

ifneq "$(MAKECMDGOALS)" "clean"
    -include $(addprefix $(dep_dir)/,$(patsubst %.cpp,%.d,$(files)))
endif

.PHONY: all clean

all: ${targerts}

$(targerts): $(target_obj) 

clean:
	${RM} -r ${targerts} $(obj_dir) $(dep_dir)

%: %.o
	$(CXX) ${CXXFLAGS} -o $@ $(addprefix $(obj_dir)/,$(notdir $^)) ${LDFLAGS}

%.o: %.cpp
	@$(call make-depend,$<,$(patsubst %.cpp,%.d,$<))
	$(CXX) ${CXXFLAGS} -c -o $(addprefix $(obj_dir)/,$(notdir $@)) $<

define make-depend
    $(CXX) $(CXXFLAGS) -M $1 >$(dep_dir)/$2
endef

vpath %.h $(inc_dir)
vpath %.d $(dep_dir)
vpath %.o $(obj_dir)


