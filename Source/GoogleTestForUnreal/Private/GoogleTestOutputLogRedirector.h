#pragma once


#include <gtest/gtest.h>


class GoogleTestOutputLogRedirector : public ::testing::EmptyTestEventListener
{
public:
	GoogleTestOutputLogRedirector();
	virtual ~GoogleTestOutputLogRedirector();

	void OnTestProgramStart(const ::testing::UnitTest& unit_test) override;
	void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override;
	void OnTestEnd(const ::testing::TestInfo& test_info) override;
	void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override;
};
