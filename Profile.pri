CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else {
    DESTDIR = build/release
}

UI_DIR      = $$DESTDIR/.ui
RCC_DIR     = $$DESTDIR/.rcc
MOC_DIR     = $$DESTDIR/.moc
OBJECTS_DIR = $$DESTDIR/.obj

CONFIG      -= \
    debug_and_release