# Build temporary binary
set vsp=false
set clean=
scons -j6 %clean% p=windows tools=yes vsproj=%vsp% module_mono_enabled=yes mono_glue=no
# Generate glue sources
bin\godot.windows.tools.64.mono --generate-mono-glue modules/mono/glue

### Build binaries normally
# Editor
scons p=windows %clean% -j6 vsproj=%vsp%  target=release_debug tools=yes module_mono_enabled=yes
# Export templates
scons p=windows -j6 %clean% vsproj=%vsp%  target=debug tools=no module_mono_enabled=yes
scons p=windows -j6 %clean% vsproj=%vsp%  target=release tools=no 
module_mono_enabled=yes
