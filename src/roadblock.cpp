#include "roadblock.h"


RoadBlock::RoadBlock(int grid_width, int grid_height)
{
    left = floor = 0;
    right = grid_width;
    ceiling = grid_height;
}

void RoadBlock::UpdateCount()
{
    count = 0;
    if (upper_left != nullptr)
        count += upper_left->count;
    if (lower_left != nullptr)
        count += lower_left->count;
    if (upper_right != nullptr)
        count += upper_right->count;
    if (lower_right != nullptr)
        count += lower_right->count;
}

// Destructor
RoadBlock::~RoadBlock() {
    delete upper_left;
    delete upper_right;
    delete lower_left;
    delete lower_right;
}

// Copy Constructor
RoadBlock::RoadBlock(const RoadBlock& other)
    : count(other.count),
      left(other.left),
      right(other.right),
      floor(other.floor),
      ceiling(other.ceiling) {
    if (other.upper_left)
        upper_left = new RoadBlock(*other.upper_left);
    if (other.upper_right)
        upper_right = new RoadBlock(*other.upper_right);
    if (other.lower_left)
        lower_left = new RoadBlock(*other.lower_left);
    if (other.lower_right)
        lower_right = new RoadBlock(*other.lower_right);
}

// Copy Assignment Operator
RoadBlock& RoadBlock::operator=(const RoadBlock& other) {
    if (this == &other)
        return *this;

    // Giải phóng tài nguyên hiện tại
    delete upper_left;
    delete upper_right;
    delete lower_left;
    delete lower_right;

    // Sao chép dữ liệu từ đối tượng khác
    count = other.count;
    left = other.left;
    right = other.right;
    floor = other.floor;
    ceiling = other.ceiling;

    if (other.upper_left)
        upper_left = new RoadBlock(*other.upper_left);
    else
        upper_left = nullptr;

    if (other.upper_right)
        upper_right = new RoadBlock(*other.upper_right);
    else
        upper_right = nullptr;

    if (other.lower_left)
        lower_left = new RoadBlock(*other.lower_left);
    else
        lower_left = nullptr;

    if (other.lower_right)
        lower_right = new RoadBlock(*other.lower_right);
    else
        lower_right = nullptr;

    return *this;
}

// Move Constructor
RoadBlock::RoadBlock(RoadBlock&& other) noexcept
    : count(other.count),
      left(other.left),
      right(other.right),
      floor(other.floor),
      ceiling(other.ceiling),
      upper_left(other.upper_left),
      upper_right(other.upper_right),
      lower_left(other.lower_left),
      lower_right(other.lower_right) {
    other.upper_left = nullptr;
    other.upper_right = nullptr;
    other.lower_left = nullptr;
    other.lower_right = nullptr;
}

// Move Assignment Operator
RoadBlock& RoadBlock::operator=(RoadBlock&& other) noexcept {
    if (this == &other)
        return *this;

    // Giải phóng tài nguyên hiện tại
    delete upper_left;
    delete upper_right;
    delete lower_left;
    delete lower_right;

    // Chuyển tài nguyên từ đối tượng khác
    count = other.count;
    left = other.left;
    right = other.right;
    floor = other.floor;
    ceiling = other.ceiling;

    upper_left = other.upper_left;
    upper_right = other.upper_right;
    lower_left = other.lower_left;
    lower_right = other.lower_right;

    other.upper_left = nullptr;
    other.upper_right = nullptr;
    other.lower_left = nullptr;
    other.lower_right = nullptr;

    return *this;
}