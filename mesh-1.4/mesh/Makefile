-include Makefile.config

all: $(TYPE)

upgrade: root all $(TYPE)_upgrade

install: root prefix $(TYPE)_install upgrade

clean:
	cd bypass; make clean

distclean: clean
	rm -f Makefile.config
	cd bypass; make distclean
	cd ../bypass; make realclean

dist:
	mkdir ../mesh-$(VERSION)
	cp -r ../bypass ../mesh-$(VERSION)
	cp -r ../mesh ../mesh-$(VERSION)
	echo 'Go to mesh directory and read "README"' >../mesh-$(VERSION)/README
	rm -f ../mesh-$(VERSION)/bypass/.todo
	rm -f ../mesh-$(VERSION)/mesh/.todo
	rm -f ../mesh-$(VERSION)/mesh/perl/mc.new
	rm -f ../mesh-$(VERSION)/mesh/perl/shift*
	find -d ../mesh-$(VERSION) -name CVS -exec rm -rf {} \;
	cd .. && tar zcvf mesh-$(VERSION).tgz mesh-$(VERSION)
	rm -rf ../mesh-$(VERSION)


#############################################################
#### DO NOT DIRECTLY INVOKE ANY TARGETS BELOW THIS POINT ####
#############################################################

VERSION = 1.4
MP_BIN = mc mesh-getmp mesh-keygen mesh-keykill mesh-keytime mesh-setmp \
         mesh-update
MP_SBIN = mesh-getkey mesh-logstats
MAP_BIN = mesh-keygen mesh-keykill mesh-setmp
MAP_SBIN = mesh-getkey mesh-logstats
MASH_LIB = Command.pm Policy.pm Proxy.pm Proxy/None.pm Proxy/Ssh.pm \
           Rule/Argument.pm Rule/Connection.pm Rule/Environment.pm \
           Rule/Group.pm Rule/Option.pm Rule/User.pm
.PHONY = all upgrade install clean distclean root dist \
         mp mp_upgrade mp_install \
         map map_upgrade map_install \
         mash mash_upgrade mash_install \
         resource resource_upgrade resource_install \
         mess mess_upgrade mess_install mia_upgrade \
         prefix mia_prefix extra_prefix


##############
#### MAKE ####
##############

mp: mia mash

map: mia mash

mash:

resource: mia

mess: mia

mia:
	cd ../bypass; make
	cd bypass; make


######################
#### MAKE UPGRADE ####
######################

root:
	test `whoami` = "root"

mp_upgrade: mash_upgrade mia_upgrade
	cd perl; for file in $(MP_BIN); do \
		sed 's?PREFIX/?$(PREFIX)?' <$$file \
		    |sed 's?MAPHOST?$(MAPHOST)?' \
		    |sed 's?MAPPRINT?$(MAPPRINT)?' \
		    |sed 's?MPHOST?$(MPHOST)?' \
		    |sed 's?MPPRINT?$(MPPRINT)?' \
            >$(PREFIX)bin/$$file; \
	done
	cd $(PREFIX)bin; chown root:root $(MP_BIN)
	cd $(PREFIX)bin; chmod 0755 $(MP_BIN)
	cd perl; for file in $(MP_SBIN); do \
		sed 's?PREFIX/?$(PREFIX)?' <$$file >$(PREFIX)sbin/$$file; \
	done
	cd $(PREFIX)sbin; chown root:root $(MP_SBIN)
	cd $(PREFIX)sbin; chmod 0755 $(MP_SBIN)

map_upgrade: mash_upgrade mia_upgrade
	cd perl; for file in $(MAP_BIN); do \
		sed 's?PREFIX/?$(PREFIX)?' <$$file >$(PREFIX)bin/$$file; \
	done
	cd $(PREFIX)bin; chown root:root $(MAP_BIN)
	cd $(PREFIX)bin; chmod 0755 $(MAP_BIN)
	cd perl; for file in $(MAP_SBIN); do \
		sed 's?PREFIX/?$(PREFIX)?' <$$file >$(PREFIX)sbin/$$file; \
	done
	cd $(PREFIX)sbin; chown root:root $(MAP_SBIN)
	cd $(PREFIX)sbin; chmod 0755 $(MAP_SBIN)

mash_upgrade:
	sed 's?PREFIX/?$(PREFIX)?' <perl/mash.pl >$(PREFIX)bin/mash
	chown root:root $(PREFIX)bin/mash
	chmod 0755 $(PREFIX)bin/mash
	cd perl/Mash; for file in $(MASH_LIB); do \
		sed 's?PREFIX/?$(PREFIX)?' <$$file >$(PREFIX)lib/Mash/$$file; \
	done
	cd $(PREFIX)lib/Mash; chown root:root $(MASH_LIB)
	cd $(PREFIX)lib/Mash; chmod 0644 $(MASH_LIB)

resource_upgrade: mess_upgrade

mess_upgrade: mia_upgrade
	sed 's?PREFIX/?$(PREFIX)?' <perl/mess >$(PREFIX)bin/mess
	chmod 0755 $(PREFIX)bin/mess

mia_upgrade:
	cd bypass; make install


######################
#### MAKE INSTALL ####
######################

prefix:
	install -d $(PREFIX)
	chown root:root $(PREFIX)
	chmod 0755 $(PREFIX)
	cd $(PREFIX); install -d bin etc lib etc/mesh
	cd $(PREFIX); chown root:root bin etc lib etc/mesh
	cd $(PREFIX); chmod 0755 bin etc lib etc/mesh

mp_install: mash_install mia_prefix extra_prefix
	grep ^$(USER): /etc/passwd
	sed 's?PREFIX/?$(PREFIX)?' <etc/mashrc.mp |sed 's?MESHGROUP?$(GROUP)?' \
		>$(PREFIX)etc/mesh/mashrc 
	echo '$(MPHOST):$(MPPORT)' >$(PREFIX)etc/mesh/localhost
	echo '$(MAPHOST):$(MAPPORT)' >$(PREFIX)etc/mesh/maphost
	echo '0.0.0.0/0 localhost $(MAPPORT)' >$(PREFIX)etc/mesh/mps
	cd $(PREFIX)etc/mesh; chown root:root mashrc localhost maphost mps
	cd $(PREFIX)etc/mesh; chmod 644 mashrc localhost maphost mps
	sed 's?PREFIX/?$(PREFIX)?' <etc/mesh-getkey-hook.mp \
		|sed 's?MESHUSER?$(USER)?' >$(PREFIX)etc/mesh/root/mesh-getkey-hook
	chown root:root $(PREFIX)etc/mesh/root/mesh-getkey-hook
	chmod 700 $(PREFIX)etc/mesh/root/mesh-getkey-hook

map_install: mash_install mia_prefix extra_prefix
	grep ^$(USER): /etc/passwd
	sed 's?PREFIX/?$(PREFIX)?' <etc/mashrc.map |sed 's?MESHGROUP?$(GROUP)?' \
		|sed 's?MPIP?$(MPIP)?' >$(PREFIX)etc/mesh/mashrc 
	echo $(MAPHOST):$(MAPPORT) >$(PREFIX)etc/mesh/localhost
	cd $(PREFIX)etc/mesh; chown root:root mashrc localhost
	cd $(PREFIX)etc/mesh; chmod 644 mashrc localhost
	sed 's?/HOME?$(HOME)?' <etc/mesh-getkey-hook.map \
		>$(PREFIX)etc/mesh/root/mesh-getkey-hook
	chown root:root $(PREFIX)etc/mesh/root/mesh-getkey-hook
	chmod 700 $(PREFIX)etc/mesh/root/mesh-getkey-hook

mash_install:
	sed 's?PREFIX/?$(PREFIX)?' <etc/mashrc.mp |sed 's?MESHGROUP?$(GROUP)?' \
		>$(PREFIX)etc/mesh/mashrc 
	chown root:root $(PREFIX)etc/mesh/mashrc
	chmod 644 $(PREFIX)etc/mesh/mashrc
	cd $(PREFIX)lib; install -d Mash Mash/Proxy Mash/Rule
	cd $(PREFIX)lib; chown root:root Mash Mash/Proxy Mash/Rule
	cd $(PREFIX)lib; chmod 0755 Mash Mash/Proxy Mash/Rule

resource_install: mess_install mia_prefix
	sed 's?PREFIX/?$(PREFIX)?' <etc/mesh-getkey-hook.resource \
		|sed 's?MESHUSER@MAPHOST?$(USER)@$(MAPHOST)?' \
		|sed 's?22?$(MAPPORT)?' |sed 's?/usr/bin/ssh?$(SSHPATH)?' \
		>$(PREFIX)etc/mesh/root/mesh-getkey-hook
	chown root:root $(PREFIX)etc/mesh/root/mesh-getkey-hook
	chmod 700 $(PREFIX)etc/mesh/root/mesh-getkey-hook

mess_install:
	sed 's?PREFIX/?$(PREFIX)?' <etc/meshrc.resource >$(PREFIX)etc/mesh/meshrc
	chown root:root $(PREFIX)etc/mesh/meshrc
	chmod 644 $(PREFIX)etc/mesh/meshrc

mia_prefix:
	install -d $(PREFIX)etc/mesh/root
	chown root:root $(PREFIX)etc/mesh/root
	chmod 0700 $(PREFIX)etc/mesh/root

extra_prefix:
	grep ^$(GROUP): /etc/group
	cd $(PREFIX); install -d etc/mesh/mapkeys sbin var var/meshkeys var/meshmps
	cd $(PREFIX); chown root:$(GROUP) etc/mesh/mapkeys var/meshkeys
	cd $(PREFIX); chown root:root var sbin var/meshmps
	chmod 0750 $(PREFIX)etc/mesh/mapkeys
	chmod 1753 $(PREFIX)var/meshkeys $(PREFIX)var/meshmps
	cd $(PREFIX); chmod 0755 var sbin

