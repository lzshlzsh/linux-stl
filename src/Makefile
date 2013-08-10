stl_root ?= ..

inc_dir := $(stl_root)/include
src_dir := .
obj_dir := obj
dep_dir := .dep

target_lib := libstl.so
target_obj := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
lib := $(addprefix $(obj_dir)/,$(notdir $(target_lib)))
objs := $(addprefix $(obj_dir)/,$(notdir $(target_obj)))

__mkdir := $(shell \
	for i in $(dep_dir) $(obj_dir); do \
		[ -d $$i ] || mkdir -p $$i; \
	done \
	)

CXXFLAGS += -fPIC
CXXFLAGS += $(addprefix -I,$(inc_dir))

.PHONY: all clean

all: $(target_lib)

$(target_lib): $(target_obj)
	$(CXX) -fPIC -shared -o $(lib) $(objs)

%.o: %.cpp
	@$(call make-depend,$<,$(patsubst %.o,%.d,$@))
	$(CXX) $(CXXFLAGS) -c -o $(addprefix $(obj_dir)/,$(notdir $@)) $<

clean:
	$(RM) -r $(dep_dir) $(obj_dir) 

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(addprefix $(dep_dir)/,$(patsubst %.o,%.d,$(target_obj)))
endif

define make-depend
    $(CXX) $(CXXFLAGS) -M $1 >$(dep_dir)/$2
    #sed -e 's/#.*//' -e 's/^[^:]*: //' -e 's/ *//' -e 's/ \\$$//' \
    #    -e 's/\.[ch]$$/&:/' $(dep_dir)/$2 > $(dep_dir)/$2.append
    #cat $(dep_dir)/$2.append >> $(dep_dir)/$2
    #rm $(dep_dir)/$2.append
endef

vpath %.h $(inc_dir)
vpath %.c $(src_dir)
vpath %.o $(obj_dir)
vpath %.so $(obj_dir)
vpath %.d $(dep_dir)

