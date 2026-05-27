#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build
  make -f /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build
  make -f /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build
  make -f /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build
  make -f /Users/dominikszasz/Programming/SummerArchitects/Archicad/SetOnTabTest/archicad-addon-cmake/Build/CMakeScripts/ReRunCMake.make
fi

