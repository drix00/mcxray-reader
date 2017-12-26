/**
 * @file
 * 
 * Theses tests are used to verify if the hdf5 library is correctly installed
 * and project are setup correctly.
 *
 * Also the tests are used to learn how to use the hdf5 library.
 * 
 * Compile the hdf5 library
 * ========================
 * Download and unzip the source code.
 * We need to compile your MSVC application with /MT instead of /MD.
 * Create two files c_flag_overrides.cmake and cxx_flag_overrides.cmake in the source directory.
 * 
 * c_flag_overrides.cmake:
 * 
 * @code{.cmake}
 * if(MSVC)
 *     set(CMAKE_C_FLAGS_DEBUG_INIT "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
 *     set(CMAKE_C_FLAGS_MINSIZEREL_INIT     "/MT /O1 /Ob1 /D NDEBUG")
 *     set(CMAKE_C_FLAGS_RELEASE_INIT        "/MT /O2 /Ob2 /D NDEBUG")
 *     set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "/MT /Zi /O2 /Ob1 /D NDEBUG")
 * endif()
 * @endcode
 *
 * cxx_flag_overrides.cmake:
 *
 * @code{.cmake}
 * if(MSVC)
 *     set(CMAKE_CXX_FLAGS_DEBUG_INIT "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
 *     set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "/MT /O1 /Ob1 /D NDEBUG")
 *     set(CMAKE_CXX_FLAGS_RELEASE_INIT        "/MT /O2 /Ob2 /D NDEBUG")
 *     set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "/MT /Zi /O2 /Ob1 /D NDEBUG")
 * endif()
 * @endcode
 *
 * And modify the CMakeLists.txt file by adding these lines before `PROJECT (HDF5 C CXX)`:
 *
 * @code{.cmake}
 * set(CMAKE_USER_MAKE_RULES_OVERRIDE ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides.cmake)
 * set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides.cmake)
 * @endcode
 *
 * Using cmake generate the 32 bit solution (Visual Studio 14 2015) and
 * 64 bit solution (Visual Studio 14 2015 Win64).
 * Uncheck BUILD_SHARED_LIBS and check BUILD_STATIC_EXECS.
 * After compiling both solutions and from the zip file created `HDF5-1.8.16-win32.zip` and `HDF5-1.8.16-win64.zip`:
 *  - copy the libhdf5*.lib into lib and lib64 directories.
 *  - copy the content of include folder into `Casino v3.x\headers\hdf5_32` and `Casino v3.x\headers\hdf5_64`, respectively.
 * 
 * @note cmake generate different .h configuration files for 32 and 64 bits and we need to have two sets of include folder.
 *
 * @author Hendrix Demers <hendrix.demers@mail.mcgill.ca>
 */

// C system headers
// C++ system header
#include <iostream>
#include <string>
// Library headers
#include <boost/test/unit_test.hpp>
#include "H5Cpp.h"
// Precompiled header
#pragma hdrstop
// Current declaration header file of this implementation file.
// Project headers
// Project private headers

// Global and constant variables/functions.

BOOST_AUTO_TEST_SUITE(test_hdf5)

/**
 * Minimal test to see if the this test suite is included by the testing project.
 *
 * Uncomment the `BOOST_FAIL("Nothing to test")` to make it fail.
 */
BOOST_AUTO_TEST_CASE(test_is_working)
{
    //BOOST_FAIL("Nothing to test");
    BOOST_CHECK(true);
}

/**
 * Fixture for hdf5 tests.
 */
struct Fixture
{
    Fixture(): FILE_NAME( "test_hdf5.hdf5" ), DATASET_NAME( "IntArray" )
    {
        /*
         * Turn off the auto-printing when failure occurs so that we can
         * handle the errors appropriately
         */
        H5::Exception::dontPrint();

        /*
         * Create a new file using H5F_ACC_TRUNC access,
         * default file creation properties, and default file
         * access properties.
         */
        H5::FileAccPropList file_access_property_list;
        file_access_property_list.setCore(1024, false);
        hdf5_file = H5::H5File( FILE_NAME, H5F_ACC_TRUNC, H5::FileCreatPropList::DEFAULT,
                file_access_property_list);
    }

    ~Fixture()
    {
        hdf5_file.close();
    }

    std::string FILE_NAME;
    std::string DATASET_NAME;
    static const int NX = 5;
    static const int NY = 6;
    static const int RANK = 2;

    H5::H5File hdf5_file;
};

/**
 * Test the version of the hdf5 library.
 *
 * Update this test when the library version is changed.
 * Keep the old version checks (change them to make them true) and add new checks for the new version.
 */
BOOST_AUTO_TEST_CASE(test_version)
{
    H5::Exception::dontPrint();

    unsigned majnum = 0;
    unsigned minnum = 0;
    unsigned relnum = 0;
    H5::H5Library::getLibVersion(majnum, minnum, relnum);

    BOOST_CHECK_EQUAL(1, majnum);
    BOOST_CHECK_EQUAL(8, minnum);
    BOOST_CHECK_EQUAL(16, relnum);

    //BOOST_FAIL("Nothing to test");
    BOOST_CHECK(true);
}

/**
 * Test to create a hdf5 file.
 *
 * Based on create.cpp example.
 */
BOOST_FIXTURE_TEST_CASE(test_create, Fixture)
{
    BOOST_CHECK_EQUAL(FILE_NAME, hdf5_file.getFileName());
    BOOST_CHECK_EQUAL(16777216, hdf5_file.getId());
    BOOST_CHECK_EQUAL(0, hdf5_file.getFreeSpace());
    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));
    BOOST_CHECK(H5::FileCreatPropList::DEFAULT == hdf5_file.getCreatePlist());

    //BOOST_FAIL("Nothing to test");
    BOOST_CHECK(true);
}

BOOST_FIXTURE_TEST_CASE(test_dataset, Fixture)
{
    /*
     * Data initialization.
     */
    // buffer for data to write
    int data[Fixture::NX][Fixture::NY];
    for (int j = 0; j < NX; j++)
    {
       for (int i = 0; i < NY; i++)
       {
           data[j][i] = i + j;
       }
    }
    /*
     * 0 1 2 3 4 5
     * 1 2 3 4 5 6
     * 2 3 4 5 6 7
     * 3 4 5 6 7 8
     * 4 5 6 7 8 9
     */

    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));

    /*
     * Define the size of the array and create the data space for fixed
     * size dataset.
     */
    // dataset dimensions
    hsize_t dimsf[2];
    dimsf[0] = Fixture::NX;
    dimsf[1] = Fixture::NY;
    H5::DataSpace dataspace(Fixture::RANK, dimsf );
    /*
     * Define datatype for the data in the file.
     * We will store little endian INT numbers.
     */
    H5::IntType datatype( H5::PredType::NATIVE_INT );
    datatype.setOrder( H5T_ORDER_LE );

    /*
     * Create a new dataset within the file using defined dataspace and
     * datatype and default dataset creation properties.
     */
    H5::DataSet dataset = hdf5_file.createDataSet( DATASET_NAME, datatype, dataspace );

    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(2, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));
    /*
     * Write the data to the dataset using default memory space, file
     * space, and transfer properties.
     */
    dataset.write( data, H5::PredType::NATIVE_INT );
    BOOST_CHECK_NE(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(4192, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(2, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));

    //BOOST_FAIL("Nothing to test");
    BOOST_CHECK(true);
}

BOOST_FIXTURE_TEST_CASE(test_group, Fixture)
{
    /*
    * Create a group in the file
    */

    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));

    const std::string group_name_ref = "Data";
    H5::Group group(hdf5_file.createGroup("/"+group_name_ref));

    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(2, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));

    BOOST_CHECK_EQUAL(1, hdf5_file.getNumObjs());
    BOOST_CHECK_EQUAL(0, group.getNumObjs());

    BOOST_CHECK_EQUAL(16777216, hdf5_file.getId());
    BOOST_CHECK_EQUAL(33554432, group.getId());
    BOOST_CHECK_EQUAL(33554432, group.getLocId());

    for (int index = 0; index < hdf5_file.getNumObjs(); ++index)
    {
        const std::string object_name = hdf5_file.getObjnameByIdx(index);
        if (index == 0)
        {
            BOOST_CHECK_EQUAL(group_name_ref, object_name);
            BOOST_CHECK_EQUAL(H5O_TYPE_GROUP, hdf5_file.childObjType(object_name));
            BOOST_CHECK_EQUAL(H5O_VERSION_1, hdf5_file.childObjVersion(object_name));

            H5::Group group_from_file = hdf5_file.openGroup(object_name);
            BOOST_CHECK_EQUAL(33554433, group_from_file.getId());
            BOOST_CHECK_EQUAL("Group", group_from_file.fromClass());
            BOOST_CHECK_EQUAL(H5I_GROUP, group_from_file.getHDFObjType());
            BOOST_CHECK_EQUAL(0, group_from_file.getNumAttrs());
        }
    }

    //BOOST_FAIL("Nothing to test");
    BOOST_CHECK(true);
}

BOOST_FIXTURE_TEST_CASE(test_attribute, Fixture)
{
    /*
    * Create a group in the file
    */

    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_ATTR));

    const std::string attribute_name_ref = "Version";
    const std::string attribute_value_ref = "4.0.0.0";
    // + 1 for trailing zero
    H5::StrType h5stringType(H5::PredType::C_S1, attribute_value_ref.length() + 1);

    BOOST_CHECK_EQUAL(false, hdf5_file.attrExists(attribute_name_ref));

    H5::Attribute attribute = hdf5_file.createAttribute(attribute_name_ref, h5stringType, H5::DataSpace(H5S_SCALAR));
    attribute.write(h5stringType, attribute_value_ref);

    BOOST_CHECK_EQUAL(2144, hdf5_file.getFileSize());
    BOOST_CHECK_EQUAL(2, hdf5_file.getObjCount());
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_FILE));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATASET));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_GROUP));
    BOOST_CHECK_EQUAL(0, hdf5_file.getObjCount(H5F_OBJ_DATATYPE));
    BOOST_CHECK_EQUAL(1, hdf5_file.getObjCount(H5F_OBJ_ATTR));

    BOOST_CHECK_EQUAL(0, hdf5_file.getNumObjs());
    BOOST_CHECK_EQUAL(1, hdf5_file.getNumAttrs());
    BOOST_CHECK_EQUAL(attribute_name_ref, attribute.getName());

    BOOST_CHECK_EQUAL(16777216, hdf5_file.getId());
    BOOST_CHECK_EQUAL(true, hdf5_file.attrExists(attribute_name_ref));
    BOOST_CHECK_EQUAL(100663296, attribute.getId());

    for (int index = 0; index < hdf5_file.getNumAttrs(); ++index)
    {
        const H5::Attribute attribute_from_file = hdf5_file.openAttribute(index);
        if (index == 0)
        {
            BOOST_CHECK_EQUAL(attribute_name_ref, attribute_from_file.getName());

            BOOST_CHECK_EQUAL("Attribute", attribute_from_file.fromClass());
            BOOST_CHECK_EQUAL(H5I_ATTR, attribute_from_file.getHDFObjType());
        }
    }

    //BOOST_FAIL("Nothing to test");
    BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
