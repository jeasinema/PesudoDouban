### PesudoDouban
To build a douban-like web app.

#### Build
```bash
$ mkdir build; cd build
$ cmake ..; make
```

#### Run
```bash
$ cd web
$ npm install
$ npm start  #listen@localhost:8088
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
    + -- lib 1
    |
    + -- lib 2

./web web front
```

#### License 
MIT License
