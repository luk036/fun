#include "vector3_t.hpp"
#include <vector3.hpp>

using namespace fun;

CPPUNIT_TEST_SUITE_REGISTRATION( vector3_TestCase );

void vector3_TestCase::setUp()
{
  _v0 = new vector3<int>(2, 4, -4);
  _v1 = new vector3<int>(1, 2, 3);
  _v2 = new vector3<int>(-3, 2, 3);
  _v3 = new vector3<double>(4., -5., 3.);
}

void vector3_TestCase::tearDown()
{
  delete _v0;
  delete _v1;
  delete _v2;
  delete _v3;
}

void vector3_TestCase::test_equal_to()
{
  CPPUNIT_ASSERT( *_v0 == *_v0 );
  CPPUNIT_ASSERT( *_v1 == *_v1 );
  CPPUNIT_ASSERT( *_v2 == *_v2 );
  CPPUNIT_ASSERT( !(*_v0 == *_v1) );
  CPPUNIT_ASSERT( !(*_v1 == *_v2) );
  CPPUNIT_ASSERT( !(*_v2 == *_v0) );
}


void vector3_TestCase::test_copy()
{
  CPPUNIT_ASSERT( vector3<int>(*_v0) == *_v0 );
  CPPUNIT_ASSERT( vector3<int>(*_v1) == *_v1 );
  CPPUNIT_ASSERT( vector3<int>(*_v2) == *_v2 );
  CPPUNIT_ASSERT( vector3<double>(*_v3) == *_v3 );
}

void vector3_TestCase::test_assign()
{
  vector3<int> w(0, 0, 0);
  CPPUNIT_ASSERT( (w = *_v0) == *_v0 );
  CPPUNIT_ASSERT( (w = *_v1) == *_v1 );
  CPPUNIT_ASSERT( (w = *_v2) == *_v2 );
}

void vector3_TestCase::test_plus()
{
  vector3<int> v(3, 4, 5);
  vector3<int> w(1, 3, 2);

  CPPUNIT_ASSERT( *_v0 + w == w + *_v0 );
  CPPUNIT_ASSERT( *_v1 + w == w + *_v1 );
  CPPUNIT_ASSERT( *_v2 + w == w + *_v2 );

  CPPUNIT_ASSERT( (*_v0 + v) + w == *_v0 + (v + w)  );
  CPPUNIT_ASSERT( (*_v1 + v) + w == *_v1 + (v + w)  );
  CPPUNIT_ASSERT( (*_v2 + v) + w == *_v2 + (v + w)  );
}

void vector3_TestCase::test_minus()
{
  vector3<int> v(3, 4, 5);
  vector3<int> w(1, 3, 2);

  CPPUNIT_ASSERT( (*_v0 - v) - w == *_v0 - (v + w)  );
  CPPUNIT_ASSERT( (*_v1 - v) - w == *_v1 - (v + w)  );
  CPPUNIT_ASSERT( (*_v2 - v) - w == *_v2 - (v + w)  );
}

void vector3_TestCase::test_multiply()
{
  CPPUNIT_ASSERT( *_v0 * 3 == 3 * *_v0  );
  CPPUNIT_ASSERT( *_v1 * 3 == 3 * *_v1  );
  CPPUNIT_ASSERT( *_v2 * 3 == 3 * *_v2  );
  //CPPUNIT_ASSERT( *_v3 * 3. == 3 * *_v2  );
  CPPUNIT_ASSERT( (*_v0 * 2) * 3 == *_v0 * 6  );
  CPPUNIT_ASSERT( (*_v1 * 2) * 3 == *_v1 * 6  );
  CPPUNIT_ASSERT( (*_v2 * 2) * 3 == *_v2 * 6  );
  CPPUNIT_ASSERT( (*_v3 * 2.) * 3. == *_v3 * 6.  );
}

void vector3_TestCase::test_divide()
{
  CPPUNIT_ASSERT( (*_v3 / 2.) / 3. == *_v3 / 6.  );
}

void vector3_TestCase::test_dot()
{
  CPPUNIT_ASSERT( dot(*_v0, *_v1) == dot(*_v1, *_v0) );
  CPPUNIT_ASSERT( dot(*_v1, *_v2) == dot(*_v2, *_v1) );
  CPPUNIT_ASSERT( dot(*_v2, *_v0) == dot(*_v0, *_v2) );

  CPPUNIT_ASSERT( dot(2 * *_v0, *_v1) == 2 * dot(*_v1, *_v0) );
  CPPUNIT_ASSERT( dot(2 * *_v1, *_v2) == 2 * dot(*_v2, *_v1) );
  CPPUNIT_ASSERT( dot(2 * *_v2, *_v0) == 2 * dot(*_v0, *_v2) );
}

void vector3_TestCase::test_cross()
{
  CPPUNIT_ASSERT( cross(*_v0, *_v1) == -cross(*_v1, *_v0) );
  CPPUNIT_ASSERT( cross(*_v1, *_v2) == -cross(*_v2, *_v1) );
  CPPUNIT_ASSERT( cross(*_v2, *_v0) == -cross(*_v0, *_v2) );
}

void vector3_TestCase::test_det()
{
  CPPUNIT_ASSERT( det(*_v0, *_v1, *_v2) == -det(*_v1, *_v0, *_v2) );
}
