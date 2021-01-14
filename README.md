# adb-interface

use Ninja to build

```shell
cmake -DCMAKE_TOOLCHAIN_FILE=${ndk}/build/cmake/android.toolchain.cmake -DANDROID_ABI=armeabi-v7a -DANDROID_STL=c++_static -GNinja ..
```
