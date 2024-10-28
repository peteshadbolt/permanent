# permanentbis
This is a fork of package [permanent](https://pypi.org/project/permanent/). The
fork fixes pointer arithmetics in the C module of this package. Without this
fix, compiling the module for Windows is impossible due to (defensive)
compiler's errors.

A suggested fix has been proposed as [pull
request](https://github.com/peteshadbolt/permanent/pull/2), but was so far
not accepted. This is the reason why this fork is published on PyPi.

The remaining part of the readme just repeats the original pacakge description.

# Original description of permanent

Implements Ryser's algorithm for the [permanent](https://en.wikipedia.org/wiki/Permanent).

Install:
```bash
$ pip install permanent
```
Use:
```python
>>> from numpy import *
>>> from permanent import permanent
>>> permanent(eye(15, dtype=complex))
(1-0j)
```
