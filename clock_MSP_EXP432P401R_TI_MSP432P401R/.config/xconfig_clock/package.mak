#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = xconfig_clock
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/utils.js:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/utils.js
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/xdc.tci:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/xdc.tci
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/template.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/template.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/om2.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/om2.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/xmlgen.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/xmlgen.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/xmlgen2.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/xmlgen2.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/Warnings.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/Warnings.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/IPackage.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/IPackage.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/package.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/package.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/global/Clock.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/global/Clock.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/global/Trace.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/global/Trace.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/bld.js:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/bld.js
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/BuildEnvironment.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/PackageContents.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/PackageContents.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/_gen.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/_gen.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Library.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Library.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Executable.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Executable.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Repository.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Repository.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Configuration.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Configuration.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Script.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Script.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Manifest.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Manifest.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Utils.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/Utils.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITarget.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITarget.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITarget2.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITarget2.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITarget3.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITarget3.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/ITargetFilter.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/package.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/bld/package.xs
package.mak: config.bld
/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/ITarget.xs:
package.mak: /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/ITarget.xs
/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/C28_large.xs:
package.mak: /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/C28_large.xs
/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/C28_float.xs:
package.mak: /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/C28_float.xs
/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/package.xs:
package.mak: /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/package.xs
/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/arm/elf/IArm.xs:
package.mak: /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/arm/elf/IArm.xs
/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/arm/elf/package.xs:
package.mak: /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/arm/elf/package.xs
package.mak: package.bld
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/compiler.opt.xdt
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/io/File.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/io/File.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/io/package.xs:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/services/io/package.xs
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/compiler.defs.xdt
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
/Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: /Applications/ti/xdctools_3_31_01_33_core/packages/xdc/tools/configuro/template/package.xs.xdt
endif

ti.targets.arm.elf.M4F.rootDir ?= /Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6
ti.targets.arm.elf.packageBase ?= /Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages/ti/targets/arm/elf/
.PRECIOUS: $(XDCCFGDIR)/%.oem4f
.PHONY: all,em4f .dlls,em4f .executables,em4f test,em4f
all,em4f: .executables,em4f
.executables,em4f: .libraries,em4f
.executables,em4f: .dlls,em4f
.dlls,em4f: .libraries,em4f
.libraries,em4f: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,em4f
	@$(ECHO) xdc .executables,em4f
	@$(ECHO) xdc .libraries,em4f
	@$(ECHO) xdc .dlls,em4f


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_xconfig_clock.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package xconfig_clock" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,em4f .dlls: clock.pem4f

-include package/cfg/clock_pem4f.mak
-include package/cfg/clock_pem4f.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/clock_pem4f.dep
endif
clock.pem4f: package/cfg/clock_pem4f.xdl
	@


ifeq (,$(wildcard .libraries,em4f))
clock.pem4f package/cfg/clock_pem4f.c: .libraries,em4f
endif

package/cfg/clock_pem4f.c package/cfg/clock_pem4f.h package/cfg/clock_pem4f.xdl: override _PROG_NAME := clock.xem4f
package/cfg/clock_pem4f.c: package/cfg/clock_pem4f.cfg
package/cfg/clock_pem4f.xdc.inc: package/cfg/clock_pem4f.xdl
package/cfg/clock_pem4f.xdl package/cfg/clock_pem4f.c: .interfaces

clean:: clean,em4f
	-$(RM) package/cfg/clock_pem4f.cfg
	-$(RM) package/cfg/clock_pem4f.dep
	-$(RM) package/cfg/clock_pem4f.c
	-$(RM) package/cfg/clock_pem4f.xdc.inc

clean,em4f::
	-$(RM) clock.pem4f
.executables,em4f .executables: clock.xem4f

clock.xem4f: |clock.pem4f

-include package/cfg/clock.xem4f.mak
clock.xem4f: package/cfg/clock_pem4f.oem4f 
	$(RM) $@
	@$(MSG) lnkem4f $@ ...
	$(RM) $(XDCCFGDIR)/$@.map
	$(ti.targets.arm.elf.M4F.rootDir)/bin/armcl -fs $(XDCCFGDIR)$(dir $@) -q -u _c_int00 --silicon_version=7M4 -z --strict_compatibility=on  -o $@ package/cfg/clock_pem4f.oem4f   package/cfg/clock_pem4f.xdl  -w -c -m $(XDCCFGDIR)/$@.map -l $(ti.targets.arm.elf.M4F.rootDir)/lib/libc.a
	
clock.xem4f: export C_DIR=
clock.xem4f: PATH:=$(ti.targets.arm.elf.M4F.rootDir)/bin/;$(PATH)
clock.xem4f: Path:=$(ti.targets.arm.elf.M4F.rootDir)/bin/;$(PATH)

clock.test test,em4f test: clock.xem4f.test

clock.xem4f.test:: clock.xem4f
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 clock.xem4f.test
else
	@$(MSG) running $<  ...
	$(call EXEC.clock.xem4f, ) 
endif

clean,em4f::
	-$(RM) $(wildcard .tmp,clock.xem4f,*)


clean:: clean,em4f

clean,em4f::
	-$(RM) clock.xem4f
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
clock_pem4f.oem4f,copy : package/cfg/clock_pem4f.oem4f
clock_pem4f.sem4f,copy : package/cfg/clock_pem4f.sem4f

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,xconfig_clock
ifeq (,$(MK_NOGENDEPS))
-include package/rel/xconfig_clock.tar.dep
endif
package/rel/xconfig_clock/xconfig_clock/package/package.rel.xml: package/package.bld.xml
package/rel/xconfig_clock/xconfig_clock/package/package.rel.xml: package/build.cfg
package/rel/xconfig_clock/xconfig_clock/package/package.rel.xml: package/package.xdc.inc
package/rel/xconfig_clock/xconfig_clock/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

xconfig_clock.tar: package/rel/xconfig_clock.xdc.inc package/rel/xconfig_clock/xconfig_clock/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/xconfig_clock.xdc.inc,package/rel/xconfig_clock.tar.dep)


release release,xconfig_clock: all xconfig_clock.tar
clean:: .clean
	-$(RM) xconfig_clock.tar
	-$(RM) package/rel/xconfig_clock.xdc.inc
	-$(RM) package/rel/xconfig_clock.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak