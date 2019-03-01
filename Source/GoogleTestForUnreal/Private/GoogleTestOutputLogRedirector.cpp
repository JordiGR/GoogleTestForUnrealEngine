#include "GoogleTestOutputLogRedirector.h"

#include "GoogleTestLogCategory.h"


namespace
{
	void PrintToLog(const std::ostringstream& output)
	{
		UE_LOG(GoogleTest, GOOGLE_TEST_LOG_VERBOSITY, TEXT("%s"), *FString(output.str().c_str()));
	}
}


GoogleTestOutputLogRedirector::GoogleTestOutputLogRedirector()
{}


GoogleTestOutputLogRedirector::~GoogleTestOutputLogRedirector()
{}

// Fired before any test activity starts.
void GoogleTestOutputLogRedirector::OnTestProgramStart(const ::testing::UnitTest& unit_test)
{
	std::ostringstream output;

	output << std::endl << "*** STARTING TEST RUN ***" << std::endl;

	PrintToLog(output);
}

// Fired after a failed assertion or a SUCCEED() invocation.
void GoogleTestOutputLogRedirector::OnTestPartResult(const ::testing::TestPartResult& test_part_result)
{
	std::ostringstream output;

	output << (test_part_result.failed() ? "Failure" : "Success") << " in " << test_part_result.file_name() << ":" << test_part_result.line_number() << std::endl
		<< test_part_result.summary() << std::endl;

	PrintToLog(output);
}

// Fired after the test ends.
void GoogleTestOutputLogRedirector::OnTestEnd(const ::testing::TestInfo& test_info)
{
	std::ostringstream output;
	const auto testSuccess = test_info.result()->Passed();

	output << (testSuccess ? "[PASSED] " : "[FAILED] ")
		<< test_info.test_case_name() << "." << test_info.name() << std::endl;

	PrintToLog(output);
}

// Fired after all test activities have ended.
void GoogleTestOutputLogRedirector::OnTestProgramEnd(const ::testing::UnitTest& unit_test)
{
	std::ostringstream output;

	output << "*** FINISHED TEST RUN (" << unit_test.elapsed_time() << " ms): TEST RUN "
		<< (unit_test.Passed()? "PASSED" : "FAILED") << " ***" << std::endl << std::endl;

	PrintToLog(output);
}
