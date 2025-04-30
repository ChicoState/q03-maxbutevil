/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, eq)
{
  Guesser object("Secret");
  ASSERT_EQ(object.match("Secret"), true);
}
TEST(GuesserTest, neq)
{
  Guesser object("Secret");
  ASSERT_EQ(object.match("sixcha"), false);
}
TEST(GuesserTest, too_long)
{
  Guesser object("Secret");
  ASSERT_EQ(object.match("Secrety"), false);
}
TEST(GuesserTest, too_short)
{
  Guesser object("Secret");
  ASSERT_EQ(object.match("Secre"), false);
}


TEST(GuesserTest, lc_ok)
{
  Guesser object("secret");
  ASSERT_EQ(object.match("secret"), true);
}
TEST(GuesserTest, lc_err)
{
  Guesser object("secret");
  ASSERT_EQ(object.match("sEcret"), false);
}
TEST(GuesserTest, caps_ok)
{
  Guesser object("SECRET");
  ASSERT_EQ(object.match("SECRET"), true);
}
TEST(GuesserTest, caps_err)
{
  Guesser object("SECRET");
  ASSERT_EQ(object.match("SECrET"), false);
}



TEST(GuesserTest, truncate_ok)
{
  Guesser object("0123456789012345678901234567890123456789");
  ASSERT_EQ(object.match("01234567890123456789012345678901"), true);
}
TEST(GuesserTest, truncate_err)
{
  Guesser object("0123456789012345678901234567890123456789");
	ASSERT_EQ(object.match("0123456789012345678901234567890123456789"), false);
}
TEST(GuesserTest, truncate_lock)
{
  Guesser object("0123456789012345678901234567890123456789");
	object.match("0123456789012345678901234567890123456789");
	ASSERT_EQ(object.match("01234567890123456789012345678901"), false);
}
TEST(GuesserTest, truncate_dist)
{
  Guesser object("0123456789012345678901234567890123456789");
	object.match("0123456789012345678901234567890123");
	ASSERT_EQ(object.match("01234567890123456789012345678901"), true);
}

TEST(GuesserTest, counts_down_on_lock)
{
  Guesser object("Secret");
	object.match("Secr");
	object.match("Secretly!");
  ASSERT_EQ(object.remaining(), 1);
}
TEST(GuesserTest, counts_down_after_lock) // fails with base implementation
{
  Guesser object("Secret");
	object.match("Brute Force");
	object.match("Secretly");
	ASSERT_EQ(object.remaining(), 1);
	
}
TEST(GuesserTest, stays_after_match)
{
  Guesser object("Secret");
	object.match("Secret");
	ASSERT_EQ(object.remaining(), 3);
}
TEST(GuesserTest, resets_after_match) // fails with base implementation
{
  Guesser object("Secret");
	object.match("Secretly");
	object.match("Secret");
	ASSERT_EQ(object.remaining(), 3);
}
TEST(GuesserTest, resets_again_after_match) // fails with base implementation
{
  Guesser object("Secret");
	object.match("Secretly");
	object.match("Secr");
	object.match("Secret");
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, lock)
{
  Guesser object("Secret");
	object.match("Brute Force");
	ASSERT_EQ(object.match("Secret"), false);
}
TEST(GuesserTest, lock_short)
{
  Guesser object("Secret");
	object.match("Sec");
	ASSERT_EQ(object.match("Secret"), false);
}
TEST(GuesserTest, lock_long)
{
  Guesser object("Secret");
	object.match("Secretly!");
	ASSERT_EQ(object.match("Secret"), false);
}
TEST(GuesserTest, lock_different)
{
  Guesser object("Secret");
	object.match("seCrEt");
	ASSERT_EQ(object.match("Secret"), false);
}
TEST(GuesserTest, lock_second)
{
  Guesser object("Secret");
	object.match("Secr");
	object.match("Secretly!");
  ASSERT_EQ(object.match("Secret"), false);
}

TEST(GuesserTest, two_attempts)
{
  Guesser object("Secret");
	object.match("Secr");
  ASSERT_EQ(object.match("Secret"), true);
}
TEST(GuesserTest, three_attempts)
{
  Guesser object("Secret");
	object.match("Secr");
	object.match("Secretly");
  ASSERT_EQ(object.match("Secret"), true);
}
TEST(GuesserTest, four_attempts)
{
  Guesser object("Secret");
	object.match("Secr");
	object.match("Secretly");
	object.match("Secret?");
  ASSERT_EQ(object.match("Secret"), false);
}

