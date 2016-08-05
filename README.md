# exacore-cef-plugin
Use Chromium Embedded Framework to render live HTML5 graphics for keying

## Requirements
* A working keyer setup using [exacore](https://github.com/exavideo/exacore)
* The [build dependencies for CEF](https://bitbucket.org/chromiumembedded/cef-project)

## Building
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo chown root:root exacore-cef/Release/chrome-sandbox
sudo chmod 4755 exacore-cef/Release/chrome-sandbox
```

## Usage
In your keyer_run.rb do something like:
```
cef = ShmCharacterGenerator.new('/path/to/build/exacore-cef/Release/exacore-cef --url=http://example.com')
cef.set_x 0
cef.set_y 0
keyer.cg cef
```

## Caveats
No runtime control of the browser yet; it just loads the one URL at startup.
You can probably work around this with websockets but this functionality is 
in the works.
