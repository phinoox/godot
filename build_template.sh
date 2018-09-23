
build_godot(){

if [ "$1" == "windows" ]; then

 export MONO64_PREFIX="${HOME}/.wine/drive_c/Program Files/Mono/"

else

 export MONO64_PREFIX=""
fi

# Export templates
scons platform=$1 -j12  target=debug tools=no module_mono_enabled=yes mono_glue=yes&&
scons platform=$1 -j12  target=release tools=no module_mono_enabled=yes mono_glue=yes

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

