// UnitTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <igloo/igloo_alt.h>

//Describe( a_guitar_with_a_fuzzbox )
//{
//    void SetUp()
//    {
//        guitar.AddEffect( fuzzbox );
//    }
//
//    It( starts_in_clean_mode )
//    {
//        Assert::That( guitar.Sound(), Equals( Clean ) );
//    }
//
//    Describe( in_distorted_mode )
//    {
//        void SetUp()
//        {
//            Parent().fuzzbox.Switch();
//        }
//
//        It( sounds_distorted )
//        {
//            Assert::That( Parent().guitar.Sound(), Equals( Distorted ) );
//        }
//
//        It( sounds_clean_when_I_switch_the_fuzzbox )
//        {
//            Parent().fuzzbox.Switch();
//            Assert::That( Parent().guitar.Sound(), Equals( Clean ) );
//        }
//    };
//
//    Fuzzbox fuzzbox;
//    Guitar guitar;
//};

int main( int argc, const char *argv[] )
{
    return igloo::TestRunner::RunAllTests( argc, argv );
}

