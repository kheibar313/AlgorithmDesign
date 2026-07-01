#include <iostream>
#include <queue>
#include <vector>
#include <memory>

// ================= Node =================
struct Node
{
    int size;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int s) : size(s) {}
    Node(int s, std::shared_ptr<Node> l, std::shared_ptr<Node> r)
        : size(s), left(l), right(r) {}
};

// ================= Comparator =================
struct Compare
{
    bool operator()(const std::shared_ptr<Node>& a,
                    const std::shared_ptr<Node>& b) const
    {
        return a->size > b->size;
    }
};

// ================= Print Tree =================
void printTree(const std::shared_ptr<Node>& node,
               int depth = 0,
               const std::string& prefix = "")
{
    if (!node) return;

    for (int i = 0; i < depth; ++i)
        std::cout << "   ";

    std::cout << prefix << node->size << "\n";

    if (node->left || node->right)
    {
        printTree(node->left, depth + 1, "L: ");
        printTree(node->right, depth + 1, "R: ");
    }
}

// ================= Main =================
int main()
{
    int n;
    std::cout << "Enter number of sizes: ";
    std::cin >> n;

    if (n < 2)
    {
        std::cerr << "n must be at least 2\n";
        return 1;
    }

    std::priority_queue<
        std::shared_ptr<Node>,
        std::vector<std::shared_ptr<Node>>,
        Compare
    > pq;

    for (int i = 0; i < n; ++i)
    {
        int x;
        std::cin >> x;
        pq.push(std::make_shared<Node>(x));
    }

    while (pq.size() > 1)
    {
        auto a = pq.top(); pq.pop();
        auto b = pq.top(); pq.pop();

        pq.push(std::make_shared<Node>(a->size + b->size, a, b));
    }

    auto root = pq.top();

    std::cout << "\nFinal sum: " << root->size << "\n\n";
    std::cout << "Huffman Tree:\n";
    printTree(root);

    return 0;
}
