# qtquick_customseparator

In this example we illustrate how to provide a custom resize separator.<br>

Here we list the main things to remember:

- In your `CustomViewFactory` override `separatorFilename()`

- Tell KDDW about your view factory `config.setViewFactory(new CustomViewFactory());`.

- Optionally, call `config.setSeparatorThickness(2);` to control the thickness.
  This is not done via styling, as the layouting engine needs to know the value.
  The default is 5 pixels.

- Implement your `MySeparator.qml` and put it into your QRC.
  Base it from our example, as we take care of some boilerplate.

- If you set the thickness too small it might not detect mouse hover,
  but we improve that by increasing the `MouseArea`'s size by manipulating
  its margins
