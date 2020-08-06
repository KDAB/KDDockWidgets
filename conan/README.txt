In the following example we assume you have the kddockwidgets source available in
/path/to/kddockwidgets-source.  replace '/path/to/kddockwidgets-source' to fit your needs.

$ conan create -s build_type=Release -o kddockwidgets:build_examples=True -o kddockwidgets:build_tests=True /path/to/kddockwidgets-source/conan kdab/stable

Configuration options:
 * build_static
   Builds static versions of the libraries. Default=False

 * build_tests
   Build the test harness. Default=False

 * build_examples
   Build the examples. Default=True

 * builde_python_bindings
   Build/Generate python bindings (always false for Debug or static builds). Default=False

