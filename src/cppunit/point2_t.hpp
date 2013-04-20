#ifndef CPPUNIT_POINT2_T_HPP
#define CPPUNIT_POINT2_T_HPP 1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <point2.hpp>

/**
 * A test case for point2
 */
class point2_TestCase : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( point2_TestCase );
  CPPUNIT_TEST( test_equal_to );
  CPPUNIT_TEST( test_copy );
  CPPUNIT_TEST( test_assign );
  CPPUNIT_TEST( test_plus );
  CPPUNIT_TEST( test_minus );
  CPPUNIT_TEST( test_join );
  CPPUNIT_TEST( test_collinear );
  CPPUNIT_TEST( test_on_a_conic );
  CPPUNIT_TEST_SUITE_END();

protected:
  fun::point2<int> *_p0, *_p1, *_p2, *_p3;

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

  /** Test join */
  void test_join();

  /** Test collinear */
  void test_collinear();

  /** Test on a conic */
  void test_on_a_conic();
};

/** @} */

#endif
