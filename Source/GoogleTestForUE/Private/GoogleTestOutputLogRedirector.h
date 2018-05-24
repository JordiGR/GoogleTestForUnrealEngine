#pragma once


#include <gtest/gtest.h>


class GoogleTestOutputLogRedirector : public ::testing::TestEventListener
{
public:
	GoogleTestOutputLogRedirector();
	virtual ~GoogleTestOutputLogRedirector();

	void OnTestProgramStart(const ::testing::UnitTest& unit_test) override;
	void OnTestIterationStart(const ::testing::UnitTest& unit_test, int iteration) override;
	void OnEnvironmentsSetUpStart(const ::testing::UnitTest& unit_test) override;
	void OnEnvironmentsSetUpEnd(const ::testing::UnitTest& unit_test) override;
	void OnTestCaseStart(const ::testing::TestCase& test_case) override;
	void OnTestStart(const ::testing::TestInfo& test_info) override;
	void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override;
	void OnTestEnd(const ::testing::TestInfo& test_info) override;
	void OnTestCaseEnd(const ::testing::TestCase& test_case) override;
	void OnEnvironmentsTearDownStart(const ::testing::UnitTest& unit_test) override;
	void OnEnvironmentsTearDownEnd(const ::testing::UnitTest& unit_test) override;
	void OnTestIterationEnd(const ::testing::UnitTest& unit_test, int iteration) override;
	void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override;
};
