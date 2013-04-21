#!/bin/sh
# ssh to the MAP using the private key stored in PREFIX/etc/mesh/root/mapkey
# and retrieve the public key(s) for the user given in $1 to the stream
# given in $2
/usr/bin/ssh -qxp 22 -oBatchMode=yes -i PREFIX/etc/mesh/root/mapkey MESHUSER@MAPHOST mesh-getkey "$1" >&"$2"
