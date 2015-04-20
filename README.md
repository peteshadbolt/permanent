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
Please note that the function assumes that the array contains complex numbers. So for example:
```python
>>> permanent(array([[0,1],[1,1]]), dtype=complex)
(1+0j)
```
whereas using ```permanent(array([[0,1],[1,1]]))``` will not produce the expected result.
