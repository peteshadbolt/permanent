# permanent
Implements Ryser's algorithm for the [permanent](https://en.wikipedia.org/wiki/Permanent).

Install:
```bash
$ pip install permanent
```
Use:
```python
>>> from numpy import *
>>> from permanent import permanent
>>> permanent(eye(15))
(1-0j)
```
Please note that for now we assume that the input array's `dtype` is `complex`. So for example:
```python
>>> permanent(array([[0,1],[1,1]]), dtype=complex)
(1+0j)
```
whereas ```permanent(array([[0,1],[1,1]]))``` will not produce the expected result.
