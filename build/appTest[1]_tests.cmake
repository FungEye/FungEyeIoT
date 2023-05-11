add_test([=[Test_production.Test1]=]  [==[C:/Users/ninaw/OneDrive - ViaUC/Dokumenter/GitHub/FungEyeIoT/build/Debug/appTest.exe]==] [==[--gtest_filter=Test_production.Test1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Test_production.Test1]=]  PROPERTIES WORKING_DIRECTORY [==[C:/Users/ninaw/OneDrive - ViaUC/Dokumenter/GitHub/FungEyeIoT/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  appTest_TESTS Test_production.Test1)
