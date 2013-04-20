#include "matrix3_t.hpp"
#include <matrix3.hpp>

using namespace fun;

CPPUNIT_TEST_SUITE_REGISTRATION( matrix3_TestCase );

void matrix3_TestCase::setUp()
{
  _A0 = new matrix3<int>(2, 4, -4, 3, 4, 6, 1, 3, -1);
  _A1 = new matrix3<int>(1, 2, 3, 2, -2, 0, 6, 3, -2);
  _A2 = new matrix3<int>(-3, 2, 3, 2, -3, 5, -7, 2, 0);
  _A3 = new matrix3<double>(4., -5., 3., 0.0, 3.5, -2.3, 4.8, 1.2, -2.);
}

void matrix3_TestCase::tearDown()
{
  delete _A0;
  delete _A1;
  delete _A2;
  delete _A3;
}

void matrix3_TestCase::test_equal_to()
{
  CPPUNIT_ASSERT( *_A0 == *_A0 );
  CPPUNIT_ASSERT( *_A1 == *_A1 );
  CPPUNIT_ASSERT( *_A2 == *_A2 );
  CPPUNIT_ASSERT( !(*_A0 == *_A1) );
  CPPUNIT_ASSERT( !(*_A1 == *_A2) );
  CPPUNIT_ASSERT( !(*_A2 == *_A0) );
}


void matrix3_TestCase::test_copy()
{
  CPPUNIT_ASSERT( matrix3<int>(*_A0) == *_A0 );
  CPPUNIT_ASSERT( matrix3<int>(*_A1) == *_A1 );
  CPPUNIT_ASSERT( matrix3<int>(*_A2) == *_A2 );
  CPPUNIT_ASSERT( matrix3<double>(*_A3) == *_A3 );
}

void matrix3_TestCase::test_assign()
{
  matrix3<int> B;
  CPPUNIT_ASSERT( (B = *_A0) == *_A0 );
  CPPUNIT_ASSERT( (B = *_A1) == *_A1 );
  CPPUNIT_ASSERT( (B = *_A2) == *_A2 );
}

void matrix3_TestCase::test_plus()
{
  CPPUNIT_ASSERT( *_A0 + *_A1 == *_A1 + *_A0 );
  CPPUNIT_ASSERT( *_A1 + *_A2 == *_A2 + *_A1 );
  CPPUNIT_ASSERT( *_A2 + *_A0 == *_A0 + *_A2 );

  CPPUNIT_ASSERT( (*_A0 + *_A1) + *_A2 == *_A0 + (*_A1 + *_A2)  );
}

void matrix3_TestCase::test_minus()
{
  CPPUNIT_ASSERT( (*_A0 - *_A1) - *_A2 == *_A0 - (*_A1 + *_A2)  );
}

void matrix3_TestCase::test_multiply()
{
  CPPUNIT_ASSERT( *_A0 * 3 == 3 * *_A0  );
  CPPUNIT_ASSERT( *_A1 * 3 == 3 * *_A1  );
  CPPUNIT_ASSERT( *_A2 * 3 == 3 * *_A2  );
  //CPPUNIT_ASSERT( *_A3 * 3. == 3 * *_A2  );
  CPPUNIT_ASSERT( (*_A0 * 2) * 3 == *_A0 * 6  );
  CPPUNIT_ASSERT( (*_A1 * 2) * 3 == *_A1 * 6  );
  CPPUNIT_ASSERT( (*_A2 * 2) * 3 == *_A2 * 6  );
  CPPUNIT_ASSERT( (*_A3 * 2.) * 3. == *_A3 * 6.  );
}

void matrix3_TestCase::test_divide()
{
  CPPUNIT_ASSERT( (*_A3 / 2.) / 3. == *_A3 / 6.  );
}

void matrix3_TestCase::test_determinant()
{
  CPPUNIT_ASSERT( _A0->det() * _A1->det() == (*_A0 * *_A1).det());
  CPPUNIT_ASSERT_EQUAL( _A0->det(), -28);
}

void matrix3_TestCase::test_adjoint()
{
  matrix3<int> R = *_A0 * _A0->adj();
  CPPUNIT_ASSERT( R.a() == _A0->det());
  CPPUNIT_ASSERT( R.b() ==  0);
}
