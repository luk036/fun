#include "point2_t.hpp"
#include <point2.hpp>
#include <vector2.hpp>
#include <line3.hpp>

using namespace fun;

CPPUNIT_TEST_SUITE_REGISTRATION( point2_TestCase );

void point2_TestCase::setUp()
{
  _p0 = new point2<int>(3, 7);
  _p1 = new point2<int>(1, 2);
  _p2 = new point2<int>(3, 8);
}

void point2_TestCase::tearDown()
{
  delete _p0;
  delete _p1;
  delete _p2;
}

void point2_TestCase::test_equal_to()
{
  CPPUNIT_ASSERT( *_p0 == *_p0 );
  CPPUNIT_ASSERT( *_p1 != *_p0 );
}

void point2_TestCase::test_copy()
{
  CPPUNIT_ASSERT( point2<int>(*_p0) == *_p0 );
  CPPUNIT_ASSERT( point2<int>(*_p1) == *_p1 );
  CPPUNIT_ASSERT( point2<int>(*_p2) == *_p2 );
}

void point2_TestCase::test_assign()
{
  point2<int> q;
  CPPUNIT_ASSERT( (q = *_p0) == *_p0 );
  CPPUNIT_ASSERT( (q = *_p1) == *_p1 );
  CPPUNIT_ASSERT( (q = *_p2) == *_p2 );
}


void point2_TestCase::test_plus()
{
  vector2<int> v(3, 4);
  vector2<int> w(1, 3);
  CPPUNIT_ASSERT( (*_p0 + v) + w == *_p0 + (v + w)  );
  CPPUNIT_ASSERT( (*_p1 + v) + w == *_p1 + (v + w)  );
  CPPUNIT_ASSERT( (*_p2 + v) + w == *_p2 + (v + w)  );
}

void point2_TestCase::test_minus()
{
  vector2<int> v(3, 4);
  vector2<int> w(1, 3);
  CPPUNIT_ASSERT( (*_p0 - v) - w == *_p0 - (v + w)  );
  CPPUNIT_ASSERT( (*_p1 - v) - w == *_p1 - (v + w)  );
  CPPUNIT_ASSERT( (*_p2 - v) - w == *_p2 - (v + w)  );
}

void point2_TestCase::test_join()
{
  CPPUNIT_ASSERT( equiv(join(*_p0, *_p1), join(*_p1, *_p0))  );
  CPPUNIT_ASSERT( equiv(join(*_p1, *_p2), join(*_p2, *_p1))  );
  CPPUNIT_ASSERT( equiv(join(*_p2, *_p0), join(*_p0, *_p2))  );
}

void point2_TestCase::test_collinear()
{
  CPPUNIT_ASSERT( !collinear(*_p0, *_p1, *_p2) );
}

void point2_TestCase::test_on_a_conic()
{
  CPPUNIT_ASSERT( on_a_conic(*_p0, *_p1, *_p2, *_p0, *_p1, *_p2) );
}
