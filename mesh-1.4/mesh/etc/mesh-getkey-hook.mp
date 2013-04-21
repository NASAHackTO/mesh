#!/bin/sh
# Switch to the Mesh user and retrieve the public key(s) of the user
# given in $1 to the stream given in $2.  The change in user is
# necessary to support proper mesh-getkey functionality, which is used
# to retrieve both local MP keys and foreign MP keys
/usr/bin/env MESH_PUBKEY=1 /bin/su -m -s PREFIX/bin/mash -c "mesh-getkey $1" MESHUSER >&"$2"
