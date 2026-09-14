#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int slow = 0;

    for (int fast = 1; fast < nums.size(); ++fast)
    {
        if (nums[fast] != nums[slow])
        {
            ++slow;
            nums[slow] = nums[fast];
        }
    }

    return slow + 1;
}

int main()
{
    vector<int> nums = {1, 1, 2, 2, 3};

    int k = removeDuplicates(nums);

    cout << "Unique count: " << k << endl;

    cout << "Array: ";

    for (int i = 0; i < k; ++i)
    {
        cout << nums[i] << " ";
    }

    cout << endl;

    return 0;
}
