SUMMARY = "Pickler class to extend the standard pickle.Pickler functionality"
DESCRIPTION = "cloudpickle makes it possible to serialize Python constructs \
not supported by the default pickle module from the Python standard library.\
\
cloudpickle is especially useful for cluster computing where Python code is \
shipped over the network to execute on remote hosts, possibly close to the \
data."
HOMEPAGE = "https://github.com/cloudpipe/cloudpickle"

LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${UNPACKDIR}/LICENSE.cloudpickle;md5=b4d59aa5e2cc777722aac17841237931"

inherit pypi python_flit_core

SRC_URI += "https://raw.githubusercontent.com/cloudpipe/cloudpickle/v${PV}/LICENSE;downloadfilename=LICENSE.cloudpickle;name=license"

SRC_URI[sha256sum] = "b216fa8ae4019d5482a8ac3c95d8f6346115d8835911fd4aefd1a445e4242c64"
SRC_URI[license.sha256sum] = "3029ea34173e9fdc233ad315dc6b100bd1ea71f529b1c1af97664a272fdc55f5"
