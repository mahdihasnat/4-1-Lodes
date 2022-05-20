1. Used #define instead of function calling in sub.cpp
2. Used array instead of computing roundConstant in aes.cpp
2. Derived formula of nr from nk & nb , nr = max(nk,nb)+6 used in aes.cpp:: AES()
3. Used addition instead of multiplication in aes.cpp:: encrypt()
5. SubBytes is non-linear layer resistaant for linear & differential attacks

