# Compute the Permanent
Implements Ryser's algorithm for the [permanent](https://en.wikipedia.org/wiki/Permanent)
Should install with
```bash
$ pip install permanent
```
Then
```python
>>> from numpy import *
>>> from permanent import permanent
>>> permanent(eye(15))
(1-0j)
```
