#include "point3_t.hpp"
#include <point3.hpp>
#include <line3.hpp>

using namespace fun;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( point3_TestCase );

void point3_TestCase::setUp()
{
  _p0 = new point3<int>(3, 7, 5);
  _p1 = new point3<int>(1, 2, 1);
  _p2 = new point3<int>(3, 8, 4);

  _pg0 = new point3<GF<3> >(0, 1, 2);
  _pg1 = new point3<GF<3> >(1, 1, 1);
  _pg2 = new point3<GF<3> >(2, 2, 1);

  _pc0 = new point3<complex<int> >(complex<int>(3,1), 7, 5);
  _pc1 = new point3<complex<int> >(1, 2, complex<int>(3,1));
  _pc2 = new point3<complex<int> >(3, complex<int>(8,1), 4);  
}

void point3_TestCase::tearDown()
{
  delete _p0;
  delete _p1;
  delete _p2;

  delete _pg0;
  delete _pg1;
  delete _pg2;

  delete _pc0;
  delete _pc1;
  delete _pc2;
}

void point3_TestCase::test_equal_to()
{
  point3<int> p3(4, 8, 4); // same as p1 from projective view

  CPPUNIT_ASSERT( *_p0 == *_p0 );
  CPPUNIT_ASSERT( *_p1 != *_p0 );
  CPPUNIT_ASSERT( *_p1 != p3 );

  point3<GF<3> > pg3(2, 2, 2); // same as l1 from projective view

  CPPUNIT_ASSERT( *_pg0 == *_pg0 );
  CPPUNIT_ASSERT( *_pg1 != *_pg0 );
  CPPUNIT_ASSERT( *_pg1 != pg3 );

  point3<complex<int> > pc3(complex<int>(3,-1), complex<int>(6,-2), 10);

  CPPUNIT_ASSERT( *_pc0 == *_pc0 );
  CPPUNIT_ASSERT( *_pc1 != *_pc0 );
  CPPUNIT_ASSERT( *_pc1 != pc3 );
}

void point3_TestCase::test_equivalent()
{
  point3<int> p3(4, 8, 4); // same as p1 from projective view

  CPPUNIT_ASSERT( equiv(*_p0, *_p0) );
  CPPUNIT_ASSERT( !equiv(*_p1, *_p0) );
  CPPUNIT_ASSERT( equiv(*_p1, p3) );

  point3<GF<3> > pg3(2, 2, 2); // same as l1 from projective view

  CPPUNIT_ASSERT( equiv(*_pg0, *_pg0) );
  CPPUNIT_ASSERT( !equiv(*_pg1, *_pg0) );
  CPPUNIT_ASSERT( equiv(*_pg1, pg3) );

  point3<complex<int> > pc3(complex<int>(3,-1), complex<int>(6,-2), 10);
  CPPUNIT_ASSERT( equiv(*_pc0, *_pc0) );
  CPPUNIT_ASSERT( !equiv(*_pc1, *_pc0) );
  CPPUNIT_ASSERT( equiv(*_pc1, pc3) );
}

void point3_TestCase::test_copy()
{
  CPPUNIT_ASSERT( point3<int>(*_p0) == *_p0 );
  CPPUNIT_ASSERT( point3<int>(*_p1) == *_p1 );
  CPPUNIT_ASSERT( point3<int>(*_p2) == *_p2 );

  CPPUNIT_ASSERT( point3<GF<3> >(*_pg0) == *_pg0 );
  CPPUNIT_ASSERT( point3<GF<3> >(*_pg1) == *_pg1 );
  CPPUNIT_ASSERT( point3<GF<3> >(*_pg2) == *_pg2 );

  CPPUNIT_ASSERT( point3<complex<int> >(*_pc0) == *_pc0 );
  CPPUNIT_ASSERT( point3<complex<int> >(*_pc1) == *_pc1 );
  CPPUNIT_ASSERT( point3<complex<int> >(*_pc2) == *_pc2 );
}

void point3_TestCase::test_assign()
{
  point3<int> q;
  CPPUNIT_ASSERT( (q = *_p0) == *_p0 );
  CPPUNIT_ASSERT( (q = *_p1) == *_p1 );
  CPPUNIT_ASSERT( (q = *_p2) == *_p2 );

  point3<GF<3> > mg;
  CPPUNIT_ASSERT( (mg = *_pg0) == *_pg0 );
  CPPUNIT_ASSERT( (mg = *_pg1) == *_pg1 );
  CPPUNIT_ASSERT( (mg = *_pg2) == *_pg2 );

  point3<complex<int> > mc;
  CPPUNIT_ASSERT( (mc = *_pc0) == *_pc0 );
  CPPUNIT_ASSERT( (mc = *_pc1) == *_pc1 );
  CPPUNIT_ASSERT( (mc = *_pc2) == *_pc2 );
}


//xxx void point3_TestCase::test_plus()
//xxx {
//xxx   vector3<int> v(3, 4, 5);
//xxx   vector3<int> w(1, 3, 2);
//xxx   CPPUNIT_ASSERT( (*_p0 + v) + w == *_p0 + (v + w)  );
//xxx   CPPUNIT_ASSERT( (*_p1 + v) + w == *_p1 + (v + w)  );
//xxx   CPPUNIT_ASSERT( (*_p2 + v) + w == *_p2 + (v + w)  );
//xxx }
//xxx 
//xxx void point3_TestCase::test_minus()
//xxx {
//xxx   vector3<int> v(3, 4, 5);
//xxx   vector3<int> w(1, 3, 2);
//xxx   CPPUNIT_ASSERT( (*_p0 - v) - w == *_p0 - (v + w)  );
//xxx   CPPUNIT_ASSERT( (*_p1 - v) - w == *_p1 - (v + w)  );
//xxx   CPPUNIT_ASSERT( (*_p2 - v) - w == *_p2 - (v + w)  );
//xxx }

void point3_TestCase::test_join()
{
  CPPUNIT_ASSERT( equiv(join(*_p0, *_p1), join(*_p1, *_p0))  );
  CPPUNIT_ASSERT( equiv(join(*_p1, *_p2), join(*_p2, *_p1))  );
  CPPUNIT_ASSERT( equiv(join(*_p2, *_p0), join(*_p0, *_p2))  );

  CPPUNIT_ASSERT( equiv(join(*_pg0, *_pg1), join(*_pg1, *_pg0))  );
  CPPUNIT_ASSERT( equiv(join(*_pg1, *_pg2), join(*_pg2, *_pg1))  );
  CPPUNIT_ASSERT( equiv(join(*_pg2, *_pg0), join(*_pg0, *_pg2))  );

  CPPUNIT_ASSERT( equiv(join(*_pc0, *_pc1), join(*_pc1, *_pc0))  );
  CPPUNIT_ASSERT( equiv(join(*_pc1, *_pc2), join(*_pc2, *_pc1))  );
  CPPUNIT_ASSERT( equiv(join(*_pc2, *_pc0), join(*_pc0, *_pc2))  );
}

void point3_TestCase::test_collinear()
{
  CPPUNIT_ASSERT( !collinear(*_p0, *_p1, *_p2) );
  CPPUNIT_ASSERT( !collinear(*_pg0, *_pg1, *_pg2) );
  CPPUNIT_ASSERT( !collinear(*_pc0, *_pc1, *_pc2) );
}

void point3_TestCase::test_on_a_conic()
{
  CPPUNIT_ASSERT( on_a_conic(*_p0, *_p1, *_p2, *_p0, *_p1, *_p2) );
  CPPUNIT_ASSERT( on_a_conic(*_pg0, *_pg1, *_pg2, *_pg0, *_pg1, *_pg2) );
  CPPUNIT_ASSERT( on_a_conic(*_pc0, *_pc1, *_pc2, *_pc0, *_pc1, *_pc2) );
}
