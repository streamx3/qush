TEMPLATE = subdirs

SUBDIRS += \
    libqush \
    qush_shell_demo

qush_shell_demo.depends = libqush
