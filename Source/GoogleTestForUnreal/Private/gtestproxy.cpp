#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable:4668)

	#undef TEXT
#endif

#include "src/gtest-all.cc"

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif
