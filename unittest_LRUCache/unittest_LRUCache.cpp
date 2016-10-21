#include "gtest/gtest.h"
#include "LRUCache.h"

TEST(testNameScoreSorter, simpleTest)
{
	// max item size : 3
	// pair(key, value)
	LRUCache<std::string, std::string> cache(3);

	EXPECT_EQ(0, cache.Size());

	cache.Put("A", "1");
	cache.Put("B", "2");
	EXPECT_STREQ("1", cache.Get("A").get().c_str());
	EXPECT_STREQ("2", cache.Get("B").get().c_str());
	EXPECT_EQ(2, cache.Size());
	
	cache.Put("C", "3");
	EXPECT_STREQ("3", cache.Get("C").get().c_str());\
	EXPECT_EQ(3, cache.Size());

	boost::optional<std::string> op = cache.Get("C");
	EXPECT_TRUE(op.is_initialized());

	cache.Put("D", "4");
	EXPECT_FALSE(cache.Get("A").is_initialized());
	EXPECT_EQ(3, cache.Size());
}

TEST(testNameScoreSorter, putNewKeyTest)
{
	LRUCache<std::string, std::string> cache(3);

	cache.Put("A", "1");
	cache.Put("B", "2");
	EXPECT_STREQ("1", cache.Get("A").get().c_str());
	EXPECT_STREQ("2", cache.Get("B").get().c_str());

	cache.Put("C", "3");
	EXPECT_STREQ("3", cache.Get("C").get().c_str());
	EXPECT_EQ(3, cache.Size());

	cache.Put("D", "4");  
	EXPECT_FALSE(cache.Get("A").is_initialized()); //"A" shouldn't be in cache
	EXPECT_STREQ("2", cache.Get("B").get().c_str());
	EXPECT_STREQ("3", cache.Get("C").get().c_str());
	EXPECT_STREQ("4", cache.Get("D").get().c_str());
	EXPECT_EQ(3, cache.Size());

	cache.Put("E", "5");
	EXPECT_FALSE(cache.Get("B").is_initialized()); //"B" shouldn't be in cache
	EXPECT_STREQ("3", cache.Get("C").get().c_str());
	EXPECT_STREQ("4", cache.Get("D").get().c_str());
	EXPECT_STREQ("5", cache.Get("E").get().c_str());
	EXPECT_EQ(3, cache.Size());
}

TEST(testNameScoreSorter, putSameKeyWithDifferentValueTest)
{
	LRUCache<std::string, std::string> cache(3);

	cache.Put("A", "1");
	EXPECT_STREQ("1", cache.Get("A").get().c_str());
	cache.Put("A", "2");
	EXPECT_STREQ("2", cache.Get("A").get().c_str());
	EXPECT_EQ(1, cache.Size());

	// make cache full
	cache.Put("B", "2");
	cache.Put("C", "3");
	EXPECT_EQ(3, cache.Size());
	EXPECT_STREQ("2", cache.Get("B").get().c_str());
	EXPECT_STREQ("3", cache.Get("C").get().c_str());

	// put more values with key A
	cache.Put("A", "10");
	EXPECT_STREQ("10", cache.Get("A").get().c_str());
	EXPECT_STREQ("2", cache.Get("B").get().c_str());
	EXPECT_STREQ("3", cache.Get("C").get().c_str());
	EXPECT_EQ(3, cache.Size());

	cache.Put("A", "11");
	EXPECT_STREQ("11", cache.Get("A").get().c_str());
	EXPECT_STREQ("2", cache.Get("B").get().c_str());
	EXPECT_STREQ("3", cache.Get("C").get().c_str());
	EXPECT_EQ(3, cache.Size());

	// put different key value
	cache.Put("D", "1");
	EXPECT_FALSE(cache.Get("B").is_initialized()); //"B" shouldn't be in cache
	EXPECT_STREQ("11", cache.Get("A").get().c_str());
	EXPECT_STREQ("3", cache.Get("C").get().c_str());
	EXPECT_STREQ("1", cache.Get("D").get().c_str());
	EXPECT_EQ(3, cache.Size());
}

TEST(testNameScoreSorter, getNonExistKeyTest)
{
	LRUCache<std::string, std::string> cache(3);

	EXPECT_FALSE(cache.Get("A").is_initialized()); // not existing data

	cache.Put("A", "1");
	EXPECT_TRUE(cache.Get("A").is_initialized());
	EXPECT_STREQ("1", cache.Get("1").get().c_str());

	EXPECT_FALSE(cache.Get("B").is_initialized()); // not existing data
} 
