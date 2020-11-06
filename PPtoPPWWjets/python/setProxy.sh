#!/bin/bash

echo "Setting user proxy"
voms-proxy-init --voms cms --rfc --valid 120:00
cp /tmp/x509up_u${UID} .
export X509_USER_PROXY=`pwd`/x509up_u${UID}
