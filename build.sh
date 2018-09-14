#! /bin/bash
# Build temporary binary
scons -j6  platform=x11 tools=yes module_mono_enabled=yes mono_glue=no &&
# Generate glue sources
bin/godot.x11.tools.64.mono --generate-mono-glue modules/mono/glue &&

### Build binaries normally
# Editor
scons platform=x11  -j6  target=release_debug tools=yes module_mono_enabled=yes &&
# Export templates
scons platform=x11 -j6  target=debug tools=no module_mono_enabled=yes &&
scons platform=x11 -j6  target=release tools=no module_mono_enabled=yes 
