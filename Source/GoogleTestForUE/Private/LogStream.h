#pragma once

#include <sstream>
#include <LogMacros.h>


DECLARE_LOG_CATEGORY_EXTERN(GoogleTest, Log, All);


class LogStream : public std::stringbuf
{
protected:
	int sync() override;
};
