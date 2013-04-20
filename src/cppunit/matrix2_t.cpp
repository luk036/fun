#include "matrix2_t.hpp"
#include <matrix2.hpp>

using namespace fun;

CPPUNIT_TEST_SUITE_REGISTRATION( matrix2_TestCase );

void matrix2_TestCase::setUp()
{
  _A0 = new matrix2<int>(2, 4, -4, 3);
  _A1 = new matrix2<int>(1, -2, 3, 2);
  _A2 = new matrix2<int>(-3, 2, 3, 2);
  _A3 = new matrix2<double>(4., -5., 3., 0.0);
}

void matrix2_TestCase::tearDown()
{
  delete _A0;
  delete _A1;
  delete _A2;
  delete _A3;
}

void matrix2_TestCase::test_equal_to()
{
  CPPUNIT_ASSERT( *_A0 == *_A0 );
  CPPUNIT_ASSERT( *_A1 == *_A1 );
  CPPUNIT_ASSERT( *_A2 == *_A2 );
  CPPUNIT_ASSERT( !(*_A0 == *_A1) );
  CPPUNIT_ASSERT( !(*_A1 == *_A2) );
  CPPUNIT_ASSERT( !(*_A2 == *_A0) );
}


void matrix2_TestCase::test_copy()
{
  CPPUNIT_ASSERT( matrix2<int>(*_A0) == *_A0 );
  CPPUNIT_ASSERT( matrix2<int>(*_A1) == *_A1 );
  CPPUNIT_ASSERT( matrix2<int>(*_A2) == *_A2 );
  CPPUNIT_ASSERT( matrix2<double>(*_A3) == *_A3 );
}

void matrix2_TestCase::test_assign()
{
  matrix2<int> B;
  CPPUNIT_ASSERT( (B = *_A0) == *_A0 );
  CPPUNIT_ASSERT( (B = *_A1) == *_A1 );
  CPPUNIT_ASSERT( (B = *_A2) == *_A2 );
}

void matrix2_TestCase::test_plus()
{
  CPPUNIT_ASSERT( *_A0 + *_A1 == *_A1 + *_A0 );
  CPPUNIT_ASSERT( *_A1 + *_A2 == *_A2 + *_A1 );
  CPPUNIT_ASSERT( *_A2 + *_A0 == *_A0 + *_A2 );

  CPPUNIT_ASSERT( (*_A0 + *_A1) + *_A2 == *_A0 + (*_A1 + *_A2)  );
}

void matrix2_TestCase::test_minus()
{
  CPPUNIT_ASSERT( (*_A0 - *_A1) - *_A2 == *_A0 - (*_A1 + *_A2)  );
}

void matrix2_TestCase::test_multiply()
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

void matrix2_TestCase::test_divide()
{
  CPPUNIT_ASSERT( (*_A3 / 2.) / 3. == *_A3 / 6.  );
}

void matrix2_TestCase::test_determinant()
{
  //CPPUNIT_ASSERT( _A0->det() * _A1->det() == (*_A0 * *_A1).det());
  CPPUNIT_ASSERT_EQUAL( _A0->det(), 22);
}

// void matrix2_TestCase::test_adjoint()
// {
//   matrix2<int> R = *_A0 * _A0->adj();
//   CPPUNIT_ASSERT( R.a() == _A0->det());
//   CPPUNIT_ASSERT( R.b() ==  0);
// }
