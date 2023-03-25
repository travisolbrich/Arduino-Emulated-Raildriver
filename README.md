# Arduino Emulated RailDriver
 
This is an extremely barebones, first-pass POC that shows how an Arduino Leonardo could be used to emulate a RailDriver's main analog inputs for Run8.

To use this project, you'll need [HID-Project by NicoHood](https://github.com/NicoHood/HID). This can be installed from the Arduino Library Manager. You also must modify your `boards.txt` file to reference the Raildriver's VID and PID:

```
...
leonardo.build.vid=0x05f3
leonardo.build.pid=0x0d2
leonardo.build.usb_product="Emulated RailDriver"
...
```

The RailDriver's HID documentation can be found [here](https://xkeys.com/software/developer/developerhiddatareports.html).
