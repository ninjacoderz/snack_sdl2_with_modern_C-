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
    // Do nothing because unique pointer auto release
}

// Copy Constructor
RoadBlock::RoadBlock(const RoadBlock& other)
    : count(other.count),
      left(other.left),
      right(other.right),
      floor(other.floor),
      ceiling(other.ceiling) {
    // Không sao chép std::unique_ptr mà thay vào đó tạo một unique_ptr mới từ đối tượng đã sao chép
    if (other.upper_left)
        upper_left = std::make_unique<RoadBlock>(*other.upper_left);
    if (other.upper_right)
        upper_right = std::make_unique<RoadBlock>(*other.upper_right);
    if (other.lower_left)
        lower_left = std::make_unique<RoadBlock>(*other.lower_left);
    if (other.lower_right)
        lower_right = std::make_unique<RoadBlock>(*other.lower_right);
}

// Copy Assignment Operator
RoadBlock& RoadBlock::operator=(const RoadBlock& other) {
    if (this == &other) // Tránh tự gán
        return *this;

    // Sao chép các giá trị
    count = other.count;
    left = other.left;
    right = other.right;
    floor = other.floor;
    ceiling = other.ceiling;

    // Gán lại các con trỏ unique_ptr bằng cách sử dụng std::make_unique
    if (other.upper_left)
        upper_left = std::make_unique<RoadBlock>(*other.upper_left);
    else
        upper_left = nullptr;

    if (other.upper_right)
        upper_right = std::make_unique<RoadBlock>(*other.upper_right);
    else
        upper_right = nullptr;

    if (other.lower_left)
        lower_left = std::make_unique<RoadBlock>(*other.lower_left);
    else
        lower_left = nullptr;

    if (other.lower_right)
        lower_right = std::make_unique<RoadBlock>(*other.lower_right);
    else
        lower_right = nullptr;

    return *this;
}

// Move Constructor
RoadBlock::RoadBlock(RoadBlock&& other)
    : count(other.count),
      left(other.left),
      right(other.right),
      floor(other.floor),
      ceiling(other.ceiling),
      upper_left(std::move(other.upper_left)),  // Di chuyển, không sao chép
      upper_right(std::move(other.upper_right)), // Di chuyển, không sao chép
      lower_left(std::move(other.lower_left)),   // Di chuyển, không sao chép
      lower_right(std::move(other.lower_right))  // Di chuyển, không sao chép
{
    // Sau khi di chuyển, các con trỏ trong 'other' sẽ được null, không cần thiết phải gán lại
    other.upper_left = nullptr;
    other.upper_right = nullptr;
    other.lower_left = nullptr;
    other.lower_right = nullptr;
}


// Move Assignment Operator
RoadBlock& RoadBlock::operator=(RoadBlock&& other) {
    if (this == &other)
        return *this; // Tránh tự gán

    // Chuyển tài nguyên từ đối tượng khác
    count = other.count;
    left = other.left;
    right = other.right;
    floor = other.floor;
    ceiling = other.ceiling;

    upper_left = std::move(other.upper_left);   // Di chuyển
    upper_right = std::move(other.upper_right); // Di chuyển
    lower_left = std::move(other.lower_left);   // Di chuyển
    lower_right = std::move(other.lower_right); // Di chuyển

    // Sau khi di chuyển, các con trỏ trong 'other' sẽ được null, không cần thiết phải gán lại
    other.upper_left = nullptr;
    other.upper_right = nullptr;
    other.lower_left = nullptr;
    other.lower_right = nullptr;

    return *this;
}