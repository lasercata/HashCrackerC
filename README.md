# HashCracker

Multithreaded hash cracker.

This is a rewrite in C of [lasercata/HashCracker](https://github.com/lasercata/HashCracker)

## Usage
### Installation
Get the code :
```
git clone --depth=1 https://github.com/lasercata/HashCrackerC.git
```

Compile the program :
```
cd HashCrackerC
make
```

If you want to install it globally, you can create a link :
```
ln -s /path/to/HashCrackerC/bin/main /bin/HashCracker
```

### Run
```
$ ./bin/main -h
Usage : ./bin/main [-h] [-V] [-s] [-A ALGORITHM] [-a ALPHABET] [-t NB_THREADS] [-m MIN] [-l LIMIT] HASH

Multithreaded hash cracker

Positional arguments :
    HASH                         The hash digest to crack (hex format)

Optional arguments :
    -h, --help                   Show this help message and exit
    -V, --version                Show version and exit
    -s, --silent                 Only print the password and nothing else
    -A, --algorithm ALGORITHM    The hash algorithm. Defaults to 'md5'
    -a, --alphabet ALPHABET      The alphabet to use. Can be '09', 'az', 'AZ', 'az09', 'azAZ', 'azAZ09', or a custom one
    -t, --nb-threads NB_THREADS  Specify the number of threads to use
    -m, --min MIN                try only words with at least MIN characters
    -l, --limit LIMIT            If used, limit the length of words to LIMIT

Examples :
    ./HashCracker [hash]
    ./HashCracker -m 5 -l 6 [hash]
    ./HashCracker -a 0123456789 [hash]
    ./HashCracker -a azAZ09 -A sha256 [hash]
    ./HashCracker -t 12 [hash]
```

## Licence
This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.
