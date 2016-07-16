# This *makefile* allows you to compile the available examples
# and run them. Type *make* to make an example. Type *make run*
# to run the compiled example.
#
# For more information, refer to *example/Makefile*


.PHONY: example-default

example-default:
	cd example; $(MAKE) $(MFLAGS)

%:
	cd example; $(MAKE) $(MFLAGS) $@
