#ifndef KALMAN_FILTER_CUSTOMASSERTIONFORSNOWHOUSE_HPP
#define KALMAN_FILTER_CUSTOMASSERTIONFORSNOWHOUSE_HPP


#include "catch2/catch.hpp"
#include <snowhouse/assertionexception.h>

CATCH_TRANSLATE_EXCEPTION(snowhouse::AssertionException& ex) {
    return ex.GetMessage();
}


#endif //KALMAN_FILTER_CUSTOMASSERTIONFORSNOWHOUSE_HPP