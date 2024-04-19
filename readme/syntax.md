# 코드에서 사용된 문법 정리

## stringStream

### stringstream 사용방법

``` c++
#include <sstream>
std::stringstream ss;
ss << std::setw(2) << std::setfill('0') << hours << ":"
   << std::setw(2) << std::setfill('0') << minutes << ":"
   << std::setw(2) << std::setfill('0') << seconds << "."
   << std::setw(3) << std::setfill('0') << milliseconds;

return ss.str();
```
