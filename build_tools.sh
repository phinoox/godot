
build_godot(){

if [ "$1" == "windows" ]; then
 wine="wine "
 export MONO64_PREFIX="${HOME}/.wine/drive_c/Program Files/Mono/"
 extension=".exe"
else
 wine=""
 export MONO64_PREFIX=""
fi

scons -j12  platform=$1 target=debug tools=yes module_mono_enabled=yes mono_glue=no &&
# Generate glue sources
$wine bin/godot.$1.tools.64.mono$extension --generate-mono-glue modules/mono/glue &&

### Build binaries normally
# Editor
scons platform=$1  -j12  target=debug tools=yes module_mono_enabled=yes mono_glue=yes

}

PLATFORMS=("windows" "x11" "all")

if [ -z "$1" ]; then
  PLATFORM="x11"
else
 PLATFORM=$1
fi

if [[ ! " ${PLATFORMS[@]} " =~ " ${PLATFORM} " ]]; then
  echo "Platform ${PLATFORM} not found,maybe misspelled?"
  exit
fi
if [  "$PLATFORM" == "all" ]; then
 for plat in $PLATFORMS; do
   if [ ! "$plat" == "all" ]; then
   build_godot $plat
   fi
 done 
else
 build_godot $PLATFORM
fi

