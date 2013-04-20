#ifndef CPPUNIT_POINT3_T_HPP
#define CPPUNIT_POINT3_T_HPP 1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <point3.hpp>
#include <GF.hpp>
#include <complex>

/**
 * A test case for point3
 */
class point3_TestCase : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( point3_TestCase );
  CPPUNIT_TEST( test_equal_to );
  CPPUNIT_TEST( test_equivalent );
  CPPUNIT_TEST( test_copy );
  CPPUNIT_TEST( test_assign );
  CPPUNIT_TEST( test_join );
  CPPUNIT_TEST( test_collinear );
  CPPUNIT_TEST( test_on_a_conic );
  CPPUNIT_TEST_SUITE_END();

protected:
  fun::point3<int> *_p0, *_p1, *_p2, *_p3;
  fun::point3<fun::GF<3> >   *_pg0, *_pg1, *_pg2, *_pg3;
  fun::point3<std::complex<int> >     *_pc0, *_pc1, *_pc2, *_pc3;

public:
  void setUp();
  void tearDown();

protected:
  /** Test equal to */
  void test_equal_to();

  /** Test equivalent */
  void test_equivalent();

  /** Test copy */
  void test_copy();

  /** Test assign */
  void test_assign();

  /** Test join */
  void test_join();

  /** Test collinear */
  void test_collinear();

  /** Test on a conic */
  void test_on_a_conic();
};

/** @} */

#endif
