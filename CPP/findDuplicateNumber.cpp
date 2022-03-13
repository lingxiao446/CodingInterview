
/*
Problem:
  Given a sort numbers and given a value to find out how many duplicate of the value in these numbers.
  if didn't exist, return 0.

Solution:
  1) find the fist position.
  2) find the last position.
  3) last - first + 1 is the result.
*/
#include <vector>
#include <iostream>

using namespace std;

int findFirstPosition(const vector<int>& vec, int value)
{
    if (vec.empty()) {
        return -1;
    }

    int left = 0, right = vec.size() - 1;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] == value) {
            right = mid;
        } else if (vec[mid] < value) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (vec[left] != value && vec[right] != value) {
        return -1;
    }

    if (vec[left] == value) {
        return left;
    }

    return right;
}

int findLastPosition(const vector<int>& vec, int value)
{
    if (vec.empty()) {
        return -1;
    }

    int left = 0, right = vec.size() - 1;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] == value) {
            left = mid;
        } else if (vec[mid] < value) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (vec[left] != value && vec[right] != value) {
        return -1;
    }

    if (vec[right] == value) {
        return right;
    }

    return left;
}

int findFistAndLastPosition(const vector<int>& v, int value, bool isFirst)
{
    if (v.empty()) {
        return -1;
    }

    int left = 0, right = v.size() - 1;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == value) {
            if (isFirst) {
                right = mid;
            } else {
                left = mid;
            }
        } else if (v[mid] < value) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (v[left] != value && v[right] != value) {
        return -1;
    }

    int index = -1;
    if (isFirst) {
        if (v[left] == value) {
            index = left;
        } else {
            index = right;
        }

    } else {
        if (v[right] == value) {
            index = right;
        } else {
            index = left;
        }
    }

    return index;
}

int findDuplicateNumber(const vector<int>& vec, int value)
{
    if (vec.empty()) {
        return 0;
    }

    //int left = findFirstPosition(vec, value);
    //int right = findLastPosition(vec, value);
    int left = findFistAndLastPosition(vec, value, true);
    int right = findFistAndLastPosition(vec, value, false);

    if (left < 0) {
        return 0;
    }

    cout << endl;
    cout << "left = " << left << ", right = " << right << endl;

    return right - left + 1;
}

int main()
{
    vector<int> v1 = {1, 3, 3, 3, 6, 6, 9, 9, 9, 12, 45, 67, 67, 88, 88, 88};
    cout << "v1={1, 3, 3, 3, 6, 6, 9, 9, 9, 12, 45, 67, 67, 88, 88, 88}" << endl;
    int n11 = findDuplicateNumber(v1, 5);
    cout << "The number of (5) in v1 is " << n11 << endl;
    int n12 = findDuplicateNumber(v1, 3);
    cout << "The number of (3) in v1 is " << n12 << endl;


    int n13 = findDuplicateNumber(v1, 9);
    cout << "The number of (9) in v1 is " << n13 << endl;
    int n14 = findDuplicateNumber(v1, 88);
    cout << "The number of (88) in v1 is " << n14 << endl;


    vector<int> v2 = {1, 2};
    int n2 = findDuplicateNumber(v2, 1);
    int n3 = findDuplicateNumber(v2, 7);
    cout << "the number of (1) in {1, 2} is " << n2 << endl;
    cout << "the number of (7) in {1, 2} is " << n3 << endl;

    return 0;
}



