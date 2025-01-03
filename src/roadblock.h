#ifndef ROAD_BLOCK_NODE_H
#define ROAD_BLOCK_NODE_H
#include <memory>
class RoadBlock {
public:
    int count{0};
    int left, right;
    int floor, ceiling;

    std::unique_ptr<RoadBlock> upper_left{nullptr};
    std::unique_ptr<RoadBlock> upper_right{nullptr};
    std::unique_ptr<RoadBlock>  lower_left{nullptr};
    std::unique_ptr<RoadBlock>  lower_right{nullptr};

    void UpdateCount();
     
    RoadBlock(int grid_width, int grid_height);

    RoadBlock(int left, int right, int floor, int ceiling):
            left(left),
            right(right),
            floor(floor),
            ceiling(ceiling) {}
  // Rule of Five
    ~RoadBlock();
    RoadBlock(const RoadBlock& other);                // Copy Constructor
    RoadBlock& operator=(const RoadBlock& other);     // Copy Assignment Operator
    RoadBlock(RoadBlock&& other) ;            // Move Constructor
    RoadBlock& operator=(RoadBlock&& other) ; // Move Assignment Operator
  
};

#endif