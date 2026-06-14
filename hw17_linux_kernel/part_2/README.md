**Задание 17 - по ядру Linux**

## Часть вторая: сборка кросс-компилятором ядра под arm

### Восстанавливаем исходное состояние исходного кода

Зачистил предыдущую сборку с x86\_64

```
$ make mrproper
  CLEAN   arch/x86/boot/compressed
  CLEAN   arch/x86/boot
  CLEAN   arch/x86/entry/vdso/vdso32
  CLEAN   arch/x86/entry/vdso/vdso64
  CLEAN   arch/x86/kernel/cpu
  CLEAN   arch/x86/kernel
  CLEAN   arch/x86/kvm
  CLEAN   arch/x86/purgatory
  CLEAN   arch/x86/realmode/rm
  CLEAN   arch/x86/tools
  CLEAN   arch/x86/lib
  CLEAN   certs
  CLEAN   drivers/firmware/efi/libstub
  CLEAN   drivers/gpu/drm/xe
  CLEAN   drivers/scsi
  CLEAN   drivers/tty/vt
  CLEAN   fs/unicode
  CLEAN   init
  CLEAN   kernel/debug/kdb
  CLEAN   kernel
  CLEAN   lib/crc
  CLEAN   lib/crypto
  CLEAN   lib/test_fortify
  CLEAN   lib
  CLEAN   security/apparmor
  CLEAN   security/ipe
  CLEAN   security/selinux
  CLEAN   security/tomoyo
  CLEAN   usr/include
  CLEAN   usr
  CLEAN   .
  CLEAN   modules.builtin modules.builtin.modinfo modules.builtin.ranges vmlinux.o.map vmlinux.unstripped .vmlinux.objs .vmlinux.export.c
  CLEAN   scripts/basic
  CLEAN   scripts/gdb/linux
  CLEAN   scripts/gendwarfksyms
  CLEAN   scripts/ipe/polgen
  CLEAN   scripts/kconfig
  CLEAN   scripts/mod
  CLEAN   scripts/selinux/mdp
  CLEAN   scripts
  CLEAN   include/config include/generated arch/x86/include/generated debian .config .config.old .version Module.symvers certs/signing_key.pem certs/x509.genkey vmlinux-gdb.py 
```

С помощью git diff и git status нашёл другие файлы, состояние которых необходимо восстановить. Такой файл только один - certs/Makefile:
```
$ git diff
diff --git a/certs/Makefile b/certs/Makefile
index 3ee1960f9f4a..c9a3f38dc62c 100644
--- a/certs/Makefile
+++ b/certs/Makefile
@@ -89,3 +89,6 @@ hostprogs := extract-cert
 
 HOSTCFLAGS_extract-cert.o = $(shell $(HOSTPKG_CONFIG) --cflags libcrypto 2> /dev/null) -I$(srctree)/scripts
 HOSTLDLIBS_extract-cert = $(shell $(HOSTPKG_CONFIG) --libs libcrypto 2> /dev/null || echo -lcrypto)
+
+debian/canonical-revoked-certs.pem:
+       mkdir -p debian && cp -va /usr/lib/linux/7.0.0-14-generic/canonical-revoked-certs.pem $@

$ git restore certs/Makefile

$ git status
Отсоединённый указатель HEAD указывает на v7.0
нечего коммитить, нет изменений в рабочем каталоге
```


