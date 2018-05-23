#include "LogStream.h"


DEFINE_LOG_CATEGORY(GoogleTest);


int LogStream::sync()
{
	UE_LOG(GoogleTest, Log, TEXT("%s"), *FString(str().c_str()));
	str("");

	return std::stringbuf::sync();
}
