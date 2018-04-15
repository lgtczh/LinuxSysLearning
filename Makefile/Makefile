SUBDIRS=test01 test02
.PHONY:all clean default $(SUBDIRS)

default:all

all clean:
	$(MAKE) $(SUBDIRS) TARGET=$@

$(SUBDIRS):
	$(MAKE) -C $@ $(TARGET)

