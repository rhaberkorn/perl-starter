# Preliminary new Win32 kephra starter/wrapper

* install [MinGW and MSYS](http://www.mingw.org/)
* install [Strawberry Perl](http://strawberryperl.com/), presumably to `c:\strawberry`. otherwise adapt `Makefile` since `LDOPTS` returned by `ExtUtils::Embed` are unusable
* `make` in MSYS shell should build `kephra.exe`

## TODO

* display Perl errors in MessageBox

due to popular demand the starter might evolve into a generic Perl interpreter wrapper with support for reconfiguration without recompilation...
