HOST=tif.inria.fr
DIR=squeak/devel-4
BLD=bld

REMOTE=$(HOST):$(DIR)

SSH='ssh -oCompression=no' --blocking-io -P

all : .force
	[ -d $(BLD) ] || mkdir $(BLD)
	[ -f $(BLD)/Makefile ] || ( cd $(BLD); ../platforms/unix/config/configure; )
	( cd $(BLD); $(MAKE) $(MFLAGS); )

config : .force
	make -C platforms/unix/config

configure : .force
	[ -d $(BLD) ] || mkdir $(BLD)
	( cd $(BLD); ../platforms/unix/config/configure; )

put :
	rsync -pazbv --delete --rsh=$(SSH) --exclude-from EXCLUDE . $(REMOTE)/

get :
	rsync -pazbv --delete --rsh=$(SSH) --exclude-from EXCLUDE $(REMOTE)/ .

cmp :
	rsync -pazbvn --rsh=$(SSH) --exclude-from EXCLUDE $(REMOTE)/ .

dist-src : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) dist-src; )

dist-bin : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-bin; )

dist-image : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-image; )

dist-deb : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-deb; )

dist-rpm : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-rpm; )

dist-rpm-bin : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-rpm-bin; )

dist-rpm-image : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-rpm-image; )

dist-rpm-sources : .force
	[ -d dist ] || mkdir dist
	( cd $(BLD); $(MAKE) $(MFLAGS) dist-rpm-sources; )

app : .force
	$(MAKE) -C $(BLD) Squeak.app

dist-app : .force
	[ -d dist ] || mkdir dist
	$(MAKE) -C $(BLD) dist-app

dist-dmg : .force
	[ -d dist ] || mkdir dist
	$(MAKE) -C $(BLD) dist-dmg

dist-cvs : .force
	$(MAKE) -C $(BLD) dist-cvs

j5.tar : .force
	$(MAKE) -C j5 spotless
	tar cvfj j5.tar.bz2 --exclude CVS --exclude ckpt --exclude '*~' \
		j5 platforms src

clean : .force
	/bin/rm -rf $(BLD)

.force :
