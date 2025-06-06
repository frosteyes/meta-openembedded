SUMMARY = "Graphics library for creating hardware-accelerated user interfaces"
DESCRIPTION = "Clutter is an Open GL based interactive canvas library, \
designed for creating fast, mainly 2D single window applications such as media \
box UIs, presentations, kiosk style applications and so on."
HOMEPAGE = "http://www.clutter-project.org/"
LICENSE = "LGPL-2.1-or-later"

inherit clutter ptest-gnome features_check upstream-version-is-even gobject-introspection
# depends on cogl-1.0 which needs opengl
REQUIRED_DISTRO_FEATURES ?= "opengl"

DEPENDS = "pango glib-2.0 json-glib atk udev cogl-1.0"
PACKAGE_BEFORE_PN += "${PN}-examples"
AUTOTOOLS_AUXDIR = "${S}/build-aux"

EDEPENDS_X11 = "virtual/libx11 libxi libxfixes"
EDEPENDS_GLX = "virtual/libgl"
EDEPENDS_EGL = "virtual/egl"
EDEPENDS_WAYLAND = "wayland libxkbcommon gdk-pixbuf"

EDEPENDS_EVDEV = "libxkbcommon"
ERDEPENDS_EVDEV = "xkeyboard-config"

# Needed for finding introspection.m4
EXTRA_AUTORECONF += "-I m4"

# Disable pretty much everything, override in platform specific set up
EXTRA_OECONF += "--disable-quartz-backend	\
	     	 --disable-win32-backend	\
	     	 --disable-cex100-backend	\
	     	 --disable-tslib-input		\
	    	"

PACKAGECONFIG[gdk] = "--enable-gdk-backend,--disable-gdk-backend,gtk+3"
PACKAGECONFIG[x11] = "--enable-x11-backend,--disable-x11-backend,${EDEPENDS_X11}"
PACKAGECONFIG[glx] = ",,${EDEPENDS_X11} ${EDEPENDS_GLX}"
PACKAGECONFIG[egl] = "--enable-egl-backend,--disable-egl-backend,${EDEPENDS_EGL}"
PACKAGECONFIG[evdev] = "--enable-evdev-input,--disable-evdev-input,${EDEPENDS_EVDEV},${ERDEPENDS_EVDEV}"
PACKAGECONFIG[wayland] = "--enable-wayland-backend,--disable-wayland-backend,${EDEPENDS_WAYLAND}"
PACKAGECONFIG[wayland-compositor] = "--enable-wayland-compositor,--disable-wayland-compositor,wayland"

# Default configuration, distros might want to override
PACKAGECONFIG ??= "egl gdk \
                   ${@bb.utils.filter('DISTRO_FEATURES', 'wayland', d)} \
                   ${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'glx x11', '', d)}"

FILES:${PN}-examples = "${libdir}/clutter/examples"

do_configure:prepend() {
	# see https://bugzilla.gnome.org/show_bug.cgi?id=661128 for this
	touch -t 200001010000 ${S}/po/clutter-1.0.pot
}
