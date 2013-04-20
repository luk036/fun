#ifndef CPPUNIT_VECTOR3_T_HPP
#define CPPUNIT_VECTOR3_T_HPP 1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector3.hpp>

/**
 * A test case for vector3
 */
class vector3_TestCase : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( vector3_TestCase );
  CPPUNIT_TEST( test_equal_to );
  CPPUNIT_TEST( test_copy );
  CPPUNIT_TEST( test_assign );
  CPPUNIT_TEST( test_plus );
  CPPUNIT_TEST( test_minus );
  CPPUNIT_TEST( test_multiply );
  CPPUNIT_TEST( test_divide );
  CPPUNIT_TEST( test_dot );
  CPPUNIT_TEST( test_cross );
  CPPUNIT_TEST( test_det );
  CPPUNIT_TEST_SUITE_END();

protected:
  fun::vector3<int> *_v0, *_v1, *_v2;
  fun::vector3<double>  *_v3;

public:
  void setUp();
  void tearDown();

protected:
  /** Test equal to */
  void test_equal_to();

  /** Test copy */
  void test_copy();

  /** Test assign */
  void test_assign();

  /** Test plus */
  void test_plus();

  /** Test minus */
  void test_minus();

  /** Test multiply */
  void test_multiply();

  /** Test divide */
  void test_divide();

  /** Test inner product */
  void test_dot();

  /** Test cross product */
  void test_cross();

  /** Test determinant */
  void test_det();
};

/** @} */

#endif
