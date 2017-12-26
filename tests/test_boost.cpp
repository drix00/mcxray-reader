/**
 * @file
 *
 * @date Jul 25, 2013
 * @author H. Demers: Post Doctoral 2012.
 * @copyright 2013 McGill University.
 */

// C system headers
// C++ system header
// Library headers
#include <boost/test/unit_test.hpp>
#include <boost/version.hpp>
// Precompiled header
#pragma hdrstop
// Current declaration header file of this implementation file.
// Project headers
// Project private headers

// Global and constant variables/functions.

BOOST_AUTO_TEST_SUITE(test_boost)

BOOST_AUTO_TEST_CASE( test_is_working )
{
    //BOOST_FAIL( "Nothing to test" );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE( test_version_1_49 )
{
    BOOST_CHECK_NE("1_49", BOOST_LIB_VERSION);

    //BOOST_FAIL( "Nothing to test" );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE( test_version_1_54 )
{
#ifdef _WIN32
    BOOST_CHECK_NE("1_54", BOOST_LIB_VERSION);
#else
    BOOST_CHECK_EQUAL("1_54", BOOST_LIB_VERSION);
#endif

    //BOOST_FAIL( "Nothing to test" );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_version_1_55)
    {
#ifdef _WIN32
    BOOST_CHECK_NE("1_55", BOOST_LIB_VERSION);
#else
    BOOST_CHECK_NE("1_55", BOOST_LIB_VERSION);
#endif

    //BOOST_FAIL( "Nothing to test" );
    BOOST_CHECK(true);
    }

BOOST_AUTO_TEST_CASE(test_version_1_60)
{
#ifdef _WIN32
    BOOST_CHECK_NE("1_60", BOOST_LIB_VERSION);
#else
    BOOST_CHECK_NE("1_60", BOOST_LIB_VERSION);
#endif

    //BOOST_FAIL( "Nothing to test" );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_version_1_66)
{
    BOOST_CHECK_EQUAL("1_66", BOOST_LIB_VERSION);

    //BOOST_FAIL( "Nothing to test" );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
