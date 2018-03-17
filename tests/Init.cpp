#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <snowhouse/assertionexception.h>

CATCH_TRANSLATE_EXCEPTION(snowhouse::AssertionException& ex) {
    return ex.GetMessage();
}