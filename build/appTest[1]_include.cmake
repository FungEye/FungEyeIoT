if(EXISTS "C:/Users/ninaw/OneDrive - ViaUC/Dokumenter/GitHub/FungEyeIoT/build/appTest[1]_tests.cmake")
  include("C:/Users/ninaw/OneDrive - ViaUC/Dokumenter/GitHub/FungEyeIoT/build/appTest[1]_tests.cmake")
else()
  add_test(appTest_NOT_BUILT appTest_NOT_BUILT)
endif()