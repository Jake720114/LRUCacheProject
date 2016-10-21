#pragma once
#include <list>
#include <unordered_map>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <iterator>

template<class KEY, class VALUE>
class LRUCache {
public:
	LRUCache(std::size_t a_maxItems) : maxItems_(a_maxItems) { }

	inline boost::optional<VALUE> Get(const KEY& a_key)
	{
		auto itr = map_.find(a_key);
		if (itr != map_.end()) {

			// move to front in list_
			if ((*itr).second != list_.begin()) {
				// make new pair and push front
				list_.push_front(std::make_pair(a_key, (*(*itr).second).second));
				// remove old one
				list_.erase((*itr).second);
				// update map
				map_[a_key] = list_.begin();
			}

			std::list<PairType>::iterator iter = (*itr).second;

			return boost::optional<VALUE>((*iter).second);
		}

		boost::optional<VALUE> op;
		return boost::optional<VALUE>();
	}

	inline void Put(const KEY& a_key, const VALUE& a_value)
	{
		auto itr = map_.find(a_key);
		if (itr != map_.end()) {
			// key is in cache
			//1. remove from list_
			list_.erase((*itr).second);
			//2. push front
			list_.push_front(std::make_pair(a_key, a_value));
			//3. map update	
			map_[a_key] = list_.begin();
		}
		else {
			// key is not in the cache
			//1. push_front
			list_.push_front(std::make_pair(a_key, a_value));
			//2. map update
			map_[a_key] = list_.begin();
		}

		// after push_front 
		if (list_.size() > maxItems_) {
			PairType aPair = list_.back();
			list_.pop_back();
			map_.erase(aPair.first);
		}
	}

	inline const size_t Size() const
	{
		return list_.size();
	}

private: 
	typedef typename std::pair<KEY, VALUE> PairType;
	typedef typename std::list<PairType> ListType;
	std::list<PairType> list_;
	std::unordered_map<KEY, typename ListType::iterator > map_;
	std::size_t maxItems_;
};