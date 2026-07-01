#include <queue>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

struct Node
{
    int size;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(int s) : size(s) {}
    Node(int s, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : size(s), left(std::move(l)), right(std::move(r)) {}
};

struct Compare
{
    bool operator()(const std::unique_ptr<Node> &a,
                    const std::unique_ptr<Node> &b) const
    {
        return a->size > b->size; // min-heap
    }
};

void input(std::vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        int temp;
        std::cin >> temp;
        arr.push_back(temp);
    }
}

int main()
{
    int n;
    std::cout << "Enter number of size: ";
    std::cin >> n;

    if (n < 2)
    {
        std::cerr << "n must be at least 2\n";
        return 1;
    }

    std::vector<int> arr;
    input(arr, n);

    std::priority_queue<
        std::unique_ptr<Node>,
        std::vector<std::unique_ptr<Node>>,
        Compare
    > pq;

    for (int x : arr)
        pq.push(std::make_unique<Node>(x));

    while (pq.size() > 1)
    {
        auto a = std::move(pq.top()); pq.pop();
        auto b = std::move(pq.top()); pq.pop();

        pq.push(std::make_unique<Node>(
            a->size + b->size,
            std::move(a),
            std::move(b)
        ));
    }

    std::cout << pq.top()->size << std::endl;
}


// 1 ,2 ,3 ,5 ,7 ,9 ,20 ,21 ,30 ,31 ,35 ,40 ,60
// (1 2) ,3 ,5 ,7 ,9 ,20 ,21 ,30 ,31 ,35 ,40 ,60
// 5 ,((1 2) 3) ,7 ,9 ,20 ,21 ,30 ,31 ,35 ,40 ,60
// 7 ,9 ,(5 ((1 2) 3)) ,20 ,21 ,30 ,31 ,35 ,40 ,60
// (5 ((1 2) 3)) ,(7 9) ,20 ,21 ,30 ,31 ,35 ,40 ,60
// 20 ,21 ,((5 ((1 2) 3)) (7 9)) ,30 ,31 ,35  ,40 ,60
// //               27
// ((5 ((1 2) 3)) (7 9)) ,30 ,31 ,35 ,40 ,(20 21) ,60
// 31 ,35 ,40 ,(20 21) ,(((5 ((1 2) 3)) (7 9)) 30) ,60
// //                           57
// 40 ,(20 21) ,(((5 ((1 2) 3)) (7 9)) 30) ,60 ,(31 35)
// (((5 ((1 2) 3)) (7 9)) 30) ,60 ,(31 35) ,(40 (20 21))
// 60 ,(31 35) ,(40 (20 21)) ,((((5 ((1 2) 3)) (7 9)) 30) 60)
// //                                       117
// (40 (20 21)) ,((((5 ((1 2) 3)) (7 9)) 30) 60) ,(60 (31 35))
// //                                                 126
// (60 (31 35)) ,((40 (20 21)) ((((5 ((1 2) 3)) (7 9)) 30) 60))
// //                                  198
// ((60 (31 35)) ((40 (20 21)) ((((5 ((1 2) 3)) (7 9)) 30) 60)))
//                          264