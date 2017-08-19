#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/royalempirecoin.ico

convert ../../src/qt/res/icons/royalempirecoin-16.png ../../src/qt/res/icons/royalempirecoin-32.png ../../src/qt/res/icons/royalempirecoin-48.png ${ICON_DST}
