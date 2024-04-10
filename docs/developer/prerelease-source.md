# Pre-release source code review

Before creating the tag for the new release check the following:

* sync KDAB cmake files to upstream

  compare the cmake/KDE files to their upstream versions in ssh://codereview.kdab.com:29418/kdab/extra-cmake-modules

* sync KDE cmake files to upstream

  compare the cmake/ECM files to their upstream versions in git@invent.kde.org:frameworks/extra-cmake-modules

* ensures the Doxygen.cmake file is up-to-date for the doxygen version we use on KDABCI

    ```shell
    doxygen -u  docs/api/Doxyfile.cmake
    ```

* run a pre-commit check

    ```shell
    pre-commit run --all-files
    ```

* verify ${PROJECT_NAME}_VERSION and ${PROJECT_NAME}_SOVERSION values in the top-level CMakeLists.txt

* Add the real release date to the Changelog section header "vX.Y.Z (unreleased)"

* updates distro/.spec and distro/.dsc files
* (TODO) script to do that^^

* git commit any changes made above and make sure the CIs are green before continuing.

Then create the new tag using the command:

```shell
git tag -m KDDockWidgets vX.Y.Z X.Y.Z"
```

**DO NOT PUSH THE TAG YET!**
