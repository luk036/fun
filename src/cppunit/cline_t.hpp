#ifndef CPPUNIT_CLINE_T_HPP
#define CPPUNIT_CLINE_T_HPP 1

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cline.hpp>

/**
 * A test case for cline
 */
class cline_TestCase : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( cline_TestCase );
  CPPUNIT_TEST( test_equal_to );
  CPPUNIT_TEST( test_equivalent );
  CPPUNIT_TEST( test_copy );
  CPPUNIT_TEST( test_assign );
  CPPUNIT_TEST( test_meet );
  CPPUNIT_TEST( test_concurrent );
  CPPUNIT_TEST_SUITE_END();

protected:
  fun::cline     *_l0, *_l1, *_l2, *_l3;

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
