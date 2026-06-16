ROOTFS = rootfs
ARCHIVE = initramfs.cpio

all: $(ROOTFS) dirs archive

$(ROOTFS):
	mkdir $(ROOTFS)

dirs: 
	mkdir -p $(ROOTFS)/bin
	mkdir -p $(ROOTFS)/dev
	mkdir -p $(ROOTFS)/etc
	mkdir -p $(ROOTFS)/home
	mkdir -p $(ROOTFS)/lib
	mkdir -p $(ROOTFS)/proc
	mkdir -p $(ROOTFS)/root
	mkdir -p $(ROOTFS)/sbin
	mkdir -p $(ROOTFS)/sys
	mkdir -p $(ROOTFS)/tmp
	mkdir -p $(ROOTFS)/usr
	mkdir -p $(ROOTFS)/var
	mkdir -p $(ROOTFS)/usr/bin
	mkdir -p $(ROOTFS)/usr/lib
	mkdir -p $(ROOTFS)/usr/sbin
	mkdir -p $(ROOTFS)/var/log
	mkdir -p $(ROOTFS)/etc/init.d

$(ROOTFS)/etc/init.d/rcS:
	cp -va ./rcS $(ROOTFS)/etc/init.d/
	chmod +x $(ROOTFS)/etc/init.d/rcS

archive: dirs $(ROOTFS)/etc/init.d/rcS $(ROOTFS)/bin/busybox
	cd $(ROOTFS) && \
	find . | cpio -H newc -ov --owner root:root > ../$(ARCHIVE) && \
	cd .. && gzip $(ARCHIVE)

clean:
	rm -rvf $(ROOTFS) $(ARCHIVE)

.PHONY: all dirs clean 
