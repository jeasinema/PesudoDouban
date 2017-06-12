### PseudoDouban
To build a douban-like web app.

#### Dependency
- mongodb
- mongocxx
- mstch
- jsoncpp

If you are using macOS, all of these above except jsoncpp can be directly installed by `Homebrew`.
For `jsoncpp`, refer to [this](https://github.com/open-source-parsers/jsoncpp#using-jsoncpp-in-your-project)

#### Build
```bash
$ mkdir build; cd build
$ cmake ..; make
```

#### Run
```bash
$ cd web
$ npm install
$ npm start  #listen@localhost:3000
```

#### Run unit test
```bash
$ mkdir build; cd build
$ cmake -Dtest:=true ../; make test
```

#### Structure
```plain text
./third\_party   external libraries source
    |
    + -- jsoncpp
    |
    + -- mstch
    |
    + -- ...
./crawler       crawler wirtten in c++
./data          mongoDB data
./front_end     web realted sources
./script        some utils
```

#### License 
MIT License
