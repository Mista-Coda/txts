# Text Statistics

A small CLI for seeing statistics of a text file. You simply pass in any amount of files into the program and it will print out the line, word and character count of all the files.

```console
txts ./examples/another.txt ./example/awesome.txt
```

You can also use the `--total` (`-t`) flag to just get the total from all the files that were passed in.

```console
./txts examples/another.txt examples/awesome.txt --total
```

## Compiling

Simply run `make` in the root of the project. You can also run
- `make install`: To install to /usr/bin
- `make uninstall`: To delete it from /usr/bin
- `make clean`: Remove all build artifacts