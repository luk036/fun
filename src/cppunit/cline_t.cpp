#include "cline_t.hpp"

using namespace fun;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( cline_TestCase );

void cline_TestCase::setUp()
{
  _l0 = new cline(5);
  _l1 = new cline(1);
  _l2 = new cline(4);
}

void cline_TestCase::tearDown()
{
  delete _l0;
  delete _l1;
  delete _l2;
}

void cline_TestCase::test_equal_to()
{
  cline l3(8);

  CPPUNIT_ASSERT( *_l0 == *_l0 );
  CPPUNIT_ASSERT( *_l1 != *_l0 );
  CPPUNIT_ASSERT( *_l1 != l3 );
}

void cline_TestCase::test_equivalent()
{
  cline l3(1);

  CPPUNIT_ASSERT( equiv(*_l0, *_l0) );
  CPPUNIT_ASSERT( !equiv(*_l1, *_l0) );
  CPPUNIT_ASSERT( equiv(*_l1, l3) );
}

void cline_TestCase::test_copy()
{
  CPPUNIT_ASSERT( cline(*_l0) == *_l0 );
  CPPUNIT_ASSERT( cline(*_l1) == *_l1 );
  CPPUNIT_ASSERT( cline(*_l2) == *_l2 );
}

void cline_TestCase::test_assign()
{
  cline m;
  CPPUNIT_ASSERT( (m = *_l0) == *_l0 );
  CPPUNIT_ASSERT( (m = *_l1) == *_l1 );
  CPPUNIT_ASSERT( (m = *_l2) == *_l2 );
}

void cline_TestCase::test_meet()
{
  CPPUNIT_ASSERT( equiv(meet(*_l0, *_l1), meet(*_l1, *_l0))  );
  CPPUNIT_ASSERT( equiv(meet(*_l1, *_l2), meet(*_l2, *_l1))  );
  CPPUNIT_ASSERT( equiv(meet(*_l2, *_l0), meet(*_l0, *_l2))  );
}

void cline_TestCase::test_concurrent()
{
  CPPUNIT_ASSERT( !concurrent(*_l0, *_l1, *_l2) );
}

