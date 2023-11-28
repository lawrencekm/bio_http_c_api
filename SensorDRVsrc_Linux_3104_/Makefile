#
# USB PalmSecure Sensor driver Makefile
#
# Copyright (C) 2015 - 2016 FUJITSU FRONTECH LIMITED
#
#	This program is free software; you can redistribute it and/or
#	modify it under the terms of the GNU General Public License
#	version 2 as published by the Free Software Foundation.
#
# Notes:
#
# History:
#
# 2015-02-04 - V31L02
#	- first version
# 2016-11-02 - V31L03
#	- supported PalmSecure-F Pro
#

obj-m = fjveincam.o

#KERNDIR ?= # Set your target kernel source path.(Full path)
KERNDIR ?= /lib/modules/$(shell uname -r)/build
#KERNDIR := /lib/modules/$(shell uname -r)/build

MAKE := make -C $(KERNDIR) SUBDIRS=$(shell pwd)

all:
	@if test -f $(KERNDIR)/Makefile; then \
		$(MAKE) modules; \
	else \
		echo "Path \"$(KERNDIR)\" not found."; \
		echo "You have to configure your Makefile."; \
		echo "And, set your target kernel source path to KERNDIR."; \
	fi

install:
	@$(MAKE) modules_install

clean:
	@$(MAKE) clean
