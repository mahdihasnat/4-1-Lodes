1. Used #define instead of function calling in sub.cpp
2. Used array instead of computing roundConstant in aes.cpp
2. Derived formula of nr from nk & nb , nr = max(nk,nb)+6 used in aes.cpp:: AES()
3. Used addition instead of multiplication in aes.cpp:: encrypt()
5. SubBytes is non-linear layer resistaant for linear & differential attacks
6. Fast Galois Field multiplication using generator function & memoization in gf.cpp


7. Used Decorator design pattern in networking layer for easy code maintenance & extensibility



<!-- link -->

[ctype 1: c side](https://cvstuff.wordpress.com/2014/11/19/warping-c-libraries-with-python-ctypes/)

[ctype 2: py side](https://cvstuff.wordpress.com/2014/11/20/wraping-c-code-with-python-ctypes-the-python-side/)

[ctypes 3: memory](https://cvstuff.wordpress.com/2014/11/27/wraping-c-code-with-python-ctypes-memory-and-pointers/)

[miler robin](https://cp-algorithms.com/algebra/primality_tests.html#miller-rabin-primality-test)

