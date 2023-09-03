//
// Created by parallels on 9/3/23.
//

#ifndef NETWORK_CHANNEL_MAP_H
#define NETWORK_CHANNEL_MAP_H
#include "channel.h"


struct channel_map {
    void **entries;

    /* The number of entries available in entries */
    int nentries;
};

int map_make_space(struct channel_map *map, int slot, int msize);

void map_init(struct channel_map *map);
#endif //NETWORK_CHANNEL_MAP_H
