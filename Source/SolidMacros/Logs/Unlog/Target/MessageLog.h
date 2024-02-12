// Copyright 2022 Guganana. All Rights Reserved.
#pragma once

#include <Developer/MessageLog/Public/MessageLogModule.h>
#include <Developer/MessageLog/Public/IMessageLogListing.h>
#include <Modules/ModuleManager.h>

#include "Unlog/UnlogImplementation.h"

namespace Target
{
    struct MessageLog
    {
        static TSharedRef<IMessageLogListing> GetLogListing(FMessageLogModule& MessageLogModule, const FName& CategoryName)
        {
            TSharedRef<IMessageLogListing> Listing = MessageLogModule.GetLogListing(CategoryName);
            Listing->SetLabel(FText::FromString(CategoryName.ToString()));
            return Listing;
        }

        static EMessageSeverity::Type VerbosityToSeverity(const ELogVerbosity::Type Verbosity)
        {
            switch (Verbosity)
            {
            case ELogVerbosity::Error:
                return EMessageSeverity::Error;
            case ELogVerbosity::Warning:
                return EMessageSeverity::Warning;
            default: ;
            }
            return EMessageSeverity::Info;
        }

        static void Call(const UnlogCategoryBase& Category, const ELogVerbosity::Type Verbosity, const FString& Message)
        {
            FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");

            const TSharedRef<IMessageLogListing> LogListing = GetLogListing(MessageLogModule, Category.GetName());
            LogListing->AddMessage(
                FTokenizedMessage::Create(
                    VerbosityToSeverity(Verbosity),
                    FText::FromString(Message)
                )
            );

            if (Verbosity == ELogVerbosity::Error)
            {
                MessageLogModule.OpenMessageLog(Category.GetName());
            }
        }
    };
}
