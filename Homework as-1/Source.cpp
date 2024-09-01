#include <iostream>
#include <vector>
#include <algorithm> 
#include <thread>
#include <future>

std::vector<int>::iterator find_min_element
(std::vector<int>::iterator start, std::vector<int>::iterator end, std::promise<std::vector<int>::iterator>&& promise) 
{
    auto min_iter = start;
    for (auto it = start; it != end; ++it) {
        if (*it < *min_iter) {
            min_iter = it;
        }
    }
  
    promise.set_value(min_iter);
    return min_iter;
}


void selection_sort(std::vector<int>& arr) {
    size_t n = arr.size();

    for (size_t i = 0; i < n - 1; ++i) {
       
        std::promise<std::vector<int>::iterator> promise;

        std::future<std::vector<int>::iterator> future = promise.get_future();

        std::thread finder(find_min_element, arr.begin() + i, arr.end(), std::move(promise));
        finder.detach();

        std::vector<int>::iterator min_iter = future.get();

        std::swap(arr[i], *min_iter);
    }
}

int main() {
    std::vector<int> arr = { 64, 25, 12, 22, 11 };

    std::cout << "Before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    selection_sort(arr);

    std::cout << "After sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
