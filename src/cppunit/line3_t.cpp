#include "line3_t.hpp"
#include <point3.hpp>

using namespace fun;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( line3_TestCase );

void line3_TestCase::setUp()
{
  _l0 = new line3<int>(3, 7, 5);
  _l1 = new line3<int>(1, 2, 1);
  _l2 = new line3<int>(3, 8, 4);

  _lg0 = new line3<GF<3> >(0, 1, 2);
  _lg1 = new line3<GF<3> >(1, 1, 1);
  _lg2 = new line3<GF<3> >(2, 2, 1);

  _lc0 = new line3<complex<int> >(complex<int>(3,1), 7, 5);
  _lc1 = new line3<complex<int> >(1, 2, complex<int>(3,1));
  _lc2 = new line3<complex<int> >(3, complex<int>(8,1), 4);  
}

void line3_TestCase::tearDown()
{
  delete _l0;
  delete _l1;
  delete _l2;

  delete _lg0;
  delete _lg1;
  delete _lg2;

  delete _lc0;
  delete _lc1;
  delete _lc2;
}

void line3_TestCase::test_equal_to()
{
  line3<int> l3(0, 8, 4);

  CPPUNIT_ASSERT( *_l0 == *_l0 );
  CPPUNIT_ASSERT( *_l1 != *_l0 );
  CPPUNIT_ASSERT( *_l1 != l3 );

  line3<GF<3> > lg3(2, 2, 2); // same as l1 from projective view

  CPPUNIT_ASSERT( *_lg0 == *_lg0 );
  CPPUNIT_ASSERT( *_lg1 != *_lg0 );
  CPPUNIT_ASSERT( *_lg1 != lg3 );

  line3<complex<int> > lc3(complex<int>(3,-1), complex<int>(6,-2), 10);

  CPPUNIT_ASSERT( *_lc0 == *_lc0 );
  CPPUNIT_ASSERT( *_lc1 != *_lc0 );
  CPPUNIT_ASSERT( *_lc1 != lc3 );
}

void line3_TestCase::test_equivalent()
{
  line3<int> l3(4, 8, 4); // same as l1 from projective view

  CPPUNIT_ASSERT( equiv(*_l0, *_l0) );
  CPPUNIT_ASSERT( !equiv(*_l1, *_l0) );
  CPPUNIT_ASSERT( equiv(*_l1, l3) );

  line3<GF<3> > lg3(2, 2, 2); // same as l1 from projective view

  CPPUNIT_ASSERT( equiv(*_lg0, *_lg0) );
  CPPUNIT_ASSERT( !equiv(*_lg1, *_lg0) );
  CPPUNIT_ASSERT( equiv(*_lg1, lg3) );

  line3<complex<int> > lc3(complex<int>(3,-1), complex<int>(6,-2), 10);
  CPPUNIT_ASSERT( equiv(*_lc0, *_lc0) );
  CPPUNIT_ASSERT( !equiv(*_lc1, *_lc0) );
  CPPUNIT_ASSERT( equiv(*_lc1, lc3) );
}

void line3_TestCase::test_copy()
{
  CPPUNIT_ASSERT( line3<int>(*_l0) == *_l0 );
  CPPUNIT_ASSERT( line3<int>(*_l1) == *_l1 );
  CPPUNIT_ASSERT( line3<int>(*_l2) == *_l2 );

  CPPUNIT_ASSERT( line3<GF<3> >(*_lg0) == *_lg0 );
  CPPUNIT_ASSERT( line3<GF<3> >(*_lg1) == *_lg1 );
  CPPUNIT_ASSERT( line3<GF<3> >(*_lg2) == *_lg2 );

  CPPUNIT_ASSERT( line3<complex<int> >(*_lc0) == *_lc0 );
  CPPUNIT_ASSERT( line3<complex<int> >(*_lc1) == *_lc1 );
  CPPUNIT_ASSERT( line3<complex<int> >(*_lc2) == *_lc2 );
}

void line3_TestCase::test_assign()
{
  line3<int> m;
  CPPUNIT_ASSERT( (m = *_l0) == *_l0 );
  CPPUNIT_ASSERT( (m = *_l1) == *_l1 );
  CPPUNIT_ASSERT( (m = *_l2) == *_l2 );

  line3<GF<3> > mg;
  CPPUNIT_ASSERT( (mg = *_lg0) == *_lg0 );
  CPPUNIT_ASSERT( (mg = *_lg1) == *_lg1 );
  CPPUNIT_ASSERT( (mg = *_lg2) == *_lg2 );

  line3<complex<int> > mc;
  CPPUNIT_ASSERT( (mc = *_lc0) == *_lc0 );
  CPPUNIT_ASSERT( (mc = *_lc1) == *_lc1 );
  CPPUNIT_ASSERT( (mc = *_lc2) == *_lc2 );
}

void line3_TestCase::test_meet()
{
  CPPUNIT_ASSERT( equiv(meet(*_l0, *_l1), meet(*_l1, *_l0))  );
  CPPUNIT_ASSERT( equiv(meet(*_l1, *_l2), meet(*_l2, *_l1))  );
  CPPUNIT_ASSERT( equiv(meet(*_l2, *_l0), meet(*_l0, *_l2))  );

  CPPUNIT_ASSERT( equiv(meet(*_lg0, *_lg1), meet(*_lg1, *_lg0))  );
  CPPUNIT_ASSERT( equiv(meet(*_lg1, *_lg2), meet(*_lg2, *_lg1))  );
  CPPUNIT_ASSERT( equiv(meet(*_lg2, *_lg0), meet(*_lg0, *_lg2))  );

  CPPUNIT_ASSERT( equiv(meet(*_lc0, *_lc1), meet(*_lc1, *_lc0))  );
  CPPUNIT_ASSERT( equiv(meet(*_lc1, *_lc2), meet(*_lc2, *_lc1))  );
  CPPUNIT_ASSERT( equiv(meet(*_lc2, *_lc0), meet(*_lc0, *_lc2))  );
}

void line3_TestCase::test_concurrent()
{
  CPPUNIT_ASSERT( !concurrent(*_l0, *_l1, *_l2) );
  CPPUNIT_ASSERT( !concurrent(*_lg0, *_lg1, *_lg2) );
  CPPUNIT_ASSERT( !concurrent(*_lc0, *_lc1, *_lc2) );
}

