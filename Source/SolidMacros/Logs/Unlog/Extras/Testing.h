// Copyright 2022 Guganana. All Rights Reserved.
#pragma once

#include "SolidMacros/Macros.h"
#include "Unlog/Unlog.h"
// ------------------------------------------------------------------------------------
// Testing
// ------------------------------------------------------------------------------------

struct UnlogTesting
{
    // Simple test to ensure everything compiles correctly; outputs are not tested
    static void CompileTest()
    {
        DECLARE_UNLOG_TYPE(UnlogTest);
        UNLOG_CATEGORY(TestCategory)

        // Specific category
        UN_LOG(TestCategory, Log, "A");
        UN_LOG(TestCategory, Warning, "B");
        UN_LOG(TestCategory, Error, "C");
        UN_LOG(TestCategory, Verbose, "D");

        UNLOG(TestCategory, Log)("A");
        UNLOG(TestCategory, Warning)("B");
        UNLOG(TestCategory, Error)("C");
        UNLOG(TestCategory, Verbose)("D");

        Unlog::Log<TestCategory>("A");
        Unlog::Warn<TestCategory>("B");
        Unlog::Error<TestCategory>("C");
        Unlog::Verbose<TestCategory>("D");

        // Derive category
        UN_LOG(, Log, "A");
        Unlog::Log("A");

        // Format - numbered args
        const FString ExampleString(TEXT("Hey"));
        constexpr int32 ExampleInt = 42;
        Unlog::Log("{0}: {1}", ExampleString, ExampleInt);
        UNLOG(Log)("{0}: {1}", ExampleString, ExampleInt);
        UN_LOG(, Log, "{0}: {1}", ExampleString, ExampleInt);

        // Format - printf
        UnlogTest::Logf(TEXT("%s: %d"), *ExampleString, ExampleInt);
        UNLOGF(Log)("%s: %d", *ExampleString, ExampleInt);
        UN_LOGF(, Log, "%s: %d", *ExampleString, ExampleInt);

        // Using custom logger
        using CustomUnlog = TUnlog<>::WithCategory< TestCategory >::WithTargets< Target::TViewport< 10, FColor::Yellow > >;
        CustomUnlog::Error("X");
        UNLOG(CustomUnlog, Error)("X");
        UN_LOG(CustomUnlog, Error, "X");

        // Contional logging
        constexpr bool Value = false;
        UnlogTest::Warn(Value, "Y");
        //Unlog::Warn([]{return false;}, "Y");
        UnlogTest::Warnf(Value, TEXT("Y"));
        //Unlog::Warnf([] {return false; }, TEXT("Y"));
        UNCLOG(Value, CustomUnlog, Error)("X");
        UN_CLOG(Value, , Warning, "Y");

        UNCLOGF(Value, CustomUnlog, Error)("X");
        UN_CLOGF(Value, , Warning, "Y");

        // Scoped Category
        {
            UNLOG_CATEGORY_SCOPED(TestScopedCategory);
            UNLOG(Log)("Test Scoped Category");
        }
        
    }
    
}; // struct UnlogTesting
