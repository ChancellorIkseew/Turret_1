#pragma once
#ifndef T1_SYSTEM_EVENTS
#define T1_SYSTEM_EVENTS

#include <vector>

#include "map_structures/base_engine/base_engine.h"

namespace t1
{
	class Event
	{
	public:
		bool active = false;
		bool justTriggered = false;
		Event() = default;
		virtual ~Event() = default;
		virtual void process() = 0;
	};

	class MapChanged : public Event
	{
	private:
		std::vector<TileCoord> tiles;
	public:
		MapChanged() = default;
		MapChanged(std::vector<TileCoord> tiles) : tiles(std::move(tiles))
		{
			active = true;
			justTriggered = true;
		}
		void process() override final {}
	};


	enum class EventType
	{
		MAP_CHANGED
	};

}

#endif // T1_SYSTEM_EVENTS
