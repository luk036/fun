#ifndef CPPUNIT_MATRIX3_T_HPP
#define CPPUNIT_MATRIX3_T_HPP 1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <matrix3.hpp>

/**
 * A test case for matrix3
 */
class matrix3_TestCase : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( matrix3_TestCase );
  CPPUNIT_TEST( test_equal_to );
  CPPUNIT_TEST( test_copy );
  CPPUNIT_TEST( test_assign );
  CPPUNIT_TEST( test_plus );
  CPPUNIT_TEST( test_minus );
  CPPUNIT_TEST( test_multiply );
  CPPUNIT_TEST( test_divide );
  CPPUNIT_TEST( test_determinant );
  CPPUNIT_TEST( test_adjoint );


  CPPUNIT_TEST_SUITE_END();

protected:
  fun::matrix3<int> *_A0, *_A1, *_A2;
  fun::matrix3<double>  *_A3;

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

  /** Test plus */
  void test_minus();

  /** Test multiply */
  void test_multiply();

  /** Test divide */
  void test_divide();

  /** Test determinant */
  void test_determinant();

  /** Test adjoint */
  void test_adjoint();
};

/** @} */

#endif
