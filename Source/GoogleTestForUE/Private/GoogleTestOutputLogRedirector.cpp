#include "GoogleTestOutputLogRedirector.h"

#include "GoogleTestLogCategory.h"


namespace
{
	const auto kDefaultColour = static_cast<const TCHAR*>(nullptr);
	const auto kSuccessColour = COLOR_GREEN;
	const auto kFailColour = COLOR_RED;

	void PrintToLog(const std::ostringstream& output);
}


GoogleTestOutputLogRedirector::GoogleTestOutputLogRedirector()
{}


GoogleTestOutputLogRedirector::~GoogleTestOutputLogRedirector()
{}

// Fired before any test activity starts.
void GoogleTestOutputLogRedirector::OnTestProgramStart(const ::testing::UnitTest& unit_test)
{
	std::ostringstream output;

	output << "*** STARTING TEST RUN ***" << std::endl;

	PrintToLog(output);
}

// Fired before each iteration of tests starts. There may be more than
// one iteration if GTEST_FLAG(repeat) is set. iteration is the iteration
// index, starting from 0.
void GoogleTestOutputLogRedirector::OnTestIterationStart(const ::testing::UnitTest& unit_test, int iteration)
{}

// Fired before environment set-up for each iteration of tests starts.
void GoogleTestOutputLogRedirector::OnEnvironmentsSetUpStart(const ::testing::UnitTest& unit_test)
{}

// Fired after environment set-up for each iteration of tests ends.
void GoogleTestOutputLogRedirector::OnEnvironmentsSetUpEnd(const ::testing::UnitTest& unit_test)
{}

// Fired before the test case starts.
void GoogleTestOutputLogRedirector::OnTestCaseStart(const ::testing::TestCase& test_case)
{}

// Fired before the test starts.
void GoogleTestOutputLogRedirector::OnTestStart(const ::testing::TestInfo& test_info)
{
	/*std::ostringstream output;

	output << "Starting test " << test_info.test_case_name() << "." << test_info.name() << std::endl;

	PrintToLog(output);
	*/
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

// Fired after the test case ends.
void GoogleTestOutputLogRedirector::OnTestCaseEnd(const ::testing::TestCase& test_case)
{}

// Fired before environment tear-down for each iteration of tests starts.
void GoogleTestOutputLogRedirector::OnEnvironmentsTearDownStart(const ::testing::UnitTest& unit_test)
{}

// Fired after environment tear-down for each iteration of tests ends.
void GoogleTestOutputLogRedirector::OnEnvironmentsTearDownEnd(const ::testing::UnitTest& unit_test)
{}

// Fired after each iteration of tests finishes.
void GoogleTestOutputLogRedirector::OnTestIterationEnd(const ::testing::UnitTest& unit_test, int iteration)
{}

// Fired after all test activities have ended.
void GoogleTestOutputLogRedirector::OnTestProgramEnd(const ::testing::UnitTest& unit_test)
{
	std::ostringstream output;

	output << "*** FINISHED TEST RUN (" << unit_test.elapsed_time() << " ms): TEST RUN "
		<< (unit_test.Passed()? "PASSED" : "FAILED") << " ***" << std::endl;

	PrintToLog(output);
}

namespace
{
	void PrintToLog(const std::ostringstream& output)
	{
		UE_LOG(GoogleTest, GOOGLE_TEST_LOG_VERBOSITY, TEXT("%s"), *FString(output.str().c_str()));
	}
}
