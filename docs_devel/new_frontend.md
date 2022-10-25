# Creating a new frontend

- Copy `src/dummy/` into `src/yourfrontend/`
- Rename the files from `_dummy` to `_yourfrontend`
- Edit `CMakeLists.txt` and `src/CMakeLists.txt`
- Edit the `FrontendType` enum in `KDDockWidgets.h` and add a new enumerator for your frontend
- Edit `Platform::frontendTypes()` in `Platform.cpp` and honour your new enumerator, properly ifdefed
- In `Platform.cpp` add the needed `#include "yourplatform/Platform_yourplatform.h` include
- Edit `Platform::tests_initPlatform()` and add your enumerator
- Edit `Platform_yourfrontend::name()` to return an ID for your frontend
- Run `./bin/tst_platform -tc="Platform::Platform,Platform::name"` , make sure it passes
