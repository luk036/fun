#ifndef CPPUNIT_LINE3_T_HPP
#define CPPUNIT_LINE3_T_HPP 1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <line3.hpp>
#include <GF.hpp>
#include <complex>

/**
 * A test case for line3
 */
class line3_TestCase : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( line3_TestCase );
  CPPUNIT_TEST( test_equal_to );
  CPPUNIT_TEST( test_equivalent );
  CPPUNIT_TEST( test_copy );
  CPPUNIT_TEST( test_assign );
  CPPUNIT_TEST( test_meet );
  CPPUNIT_TEST( test_concurrent );
  CPPUNIT_TEST_SUITE_END();

protected:
  fun::line3<int>     *_l0, *_l1, *_l2, *_l3;
  fun::line3<fun::GF<3> >   *_lg0, *_lg1, *_lg2, *_lg3;
  fun::line3<std::complex<int> >     *_lc0, *_lc1, *_lc2, *_lc3;

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

  /** Test meet */
  void test_meet();

  /** Test concurrent */
  void test_concurrent();

};

/** @} */

#endif
