#! /bin/bash

DIR=/home-new/bat618/github/rimlesswheel/matlab/rimless_wheel/network
BARENETWORKS="$(ls $DIR/../data/network_desired*)"
CONNNETWORKS="$(ls $DIR/../data/connected_network/network_desired*)"
EVALNETWORKS="$(ls $DIR/../data/evaluated_network/network_desired*)"


rm $BARENETWORKS
rm $CONNNETWORKS
rm $EVALNETWORKS
