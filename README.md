# Cut

This is my re-implementation of the ```cut``` command line utility.

## Usage
cut <OPTIONS> [FILE]

  -b, --bytes=LIST       Select only these bytes\n
  -c, --characters=LIST  Select only these characters\n
  -d, --delimiter=DELIM  Character to use as field delimiter\n
  -f, --fields=LIST      Select only these fields\n
  -h, --help             Display this help message and quit\n
  -v, --version          Display version number and quit\n

## Building from source
Working on Arch Linux using:
* gcc 10.2.0
* gnu make 4.3
* scdoc 1.11.1

### Make Dependencies
* GCC/Clang/equivalent
* make
* scdoc (manpages)

### Compiling
```
git clone https://github.com/acly7946/cut.git
cd cut
make

sudo make install # To install
sudo make uninstall # To uninstall
```
