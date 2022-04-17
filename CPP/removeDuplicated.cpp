
#include <vector>
#include <iostream>

using namespace std;

int removeDuplicates(vector<int>& nums)
{
    if (nums.empty()) {
        return 0;
    }

    // 1,    1, 2.
    // left  ,  right
    int left =0, right =1;

    while (right < nums.size()) {
        if (nums[right] == nums[left]) {
            right ++;
            continue;
        }
        nums[++left] = nums[right++];
    }

    return 0;
}

int main()
{
    vector<int> v1= {0,0,1,1,1,2,2,3,3,4};

    removeDuplicates(v1);

    for (const auto e: v1) {
        cout<< e <<" ";
    }
    cout << endl;

    return 0;
}