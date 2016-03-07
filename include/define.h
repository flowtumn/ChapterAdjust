#ifndef DEFINE_H_INCLUDE
#define DEFINE_H_INCLUDE

#include <string>

namespace flowTumn {

#if (1800 < _MSC_VER)
  #define CONSTEXPR   constexpr
#else
  #define CONSTEXPR
#endif

#if defined(UNICODE) || defined(_UNICODE)
  using tstr = std::wstring;
  #define _T(x)	L##x
#else
  using tstr = std::string;
  #define _T(x)	x
#endif

};


#endif
