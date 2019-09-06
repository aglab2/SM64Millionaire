#pragma once

struct GraphNode
{
    /*0x00*/ s16 type; // structure type
    /*0x02*/ s16 flags; // hi = drawing layer, lo = rendering modes
    /*0x04*/ struct GraphNode *prev;
    /*0x08*/ struct GraphNode *next;
    /*0x0C*/ struct GraphNode *parent;
    /*0x10*/ struct GraphNode *children;
};