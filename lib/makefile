STANDALONE_MK = $(PTOLEMY)/mk/standalone.mk
#STL_INCLUDE_DIRS = $(PTOLEMY)/src/gnu/src/libg++-2.7.2/libstdc++/
#STL_LIBS = -lstdc++

breadthfirst.debug:breadthfirst.cc
	gmake -f $(STANDALONE_MK) breadthfirst.debug

breadthfirst.bin:breadthfirst.cc
	gmake -f $(STANDALONE_MK) breadthfirst.bin

breadthfirst.purify:breadthfirst.cc
	gmake -f $(STANDALONE_MK) breadthfirst.purify

standalone.debug:standalone.cc
	gmake -f $(STANDALONE_MK) standalone.debug

standalone.bin:standalone.cc
	gmake -f $(STANDALONE_MK) standalone.bin

standalone.purify:standalone.cc
	gmake -f $(STANDALONE_MK) standalone.purify

template_test.debug:template_test.cc
	gmake -f $(STANDALONE_MK) template_test.debug

template_test.bin:template_test.cc
	gmake -f $(STANDALONE_MK) template_test.bin

template_test.purify:template_test.cc
	gmake -f $(STANDALONE_MK) template_test.purify

sources:Association.h Association.cc AssociationList.h AssociationList.cc \
AssociatedObj.h AssociatedObj.cc ListAssociation.h ListAssociation.cc \
MemberAssociation.h MemberAssociation.cc VanillaNode.h VanillaNode.cc

clean:
	rm -f .pure *.o *~ *.debug *.bin *.purify
	rcsclean -u
