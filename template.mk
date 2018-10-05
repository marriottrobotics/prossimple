LIBNAME=prossimple
VERSION=1.0.1

# extra files (like header files)
TEMPLATEFILES = include/GameState.h include/Movement.h include/PidCore.h include/Sensors.h
# basename of the source files that should be archived
TEMPLATEOBJS = GameState Movement PidCore Sensors

TEMPLATE=$(ROOT)/$(LIBNAME)-template

.DEFAULT_GOAL: all

library: clean $(BINDIR) $(SUBDIRS) $(ASMOBJ) $(COBJ) $(CPPOBJ)
		$(MCUPREFIX)ar rvs $(BINDIR)/$(LIBNAME).a $(foreach f,$(TEMPLATEOBJS),$(BINDIR)/$(f).o)
		mkdir -p $(TEMPLATE) $(TEMPLATE)/firmware $(addprefix $(TEMPLATE)/, $(dir $(TEMPLATEFILES)))
		cp $(BINDIR)/$(LIBNAME).a $(TEMPLATE)/firmware/$(LIBNAME).a
		$(foreach f,$(TEMPLATEFILES),cp $(f) $(TEMPLATE)/$(f);)
		pros conduct create-template $(LIBNAME) $(VERSION) $(TEMPLATE) --ignore template.pros --upgrade-files firmware/$(LIBNAME).a $(foreach f,$(TEMPLATEFILES),--upgrade-files $(f))
		@echo Need to zip $(TEMPLATE) without the base directory
		# cd $(TEMPLATE) && zip -r ../$(basename $(TEMPLATE)) *
