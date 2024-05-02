#include "main.hpp"
// #include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct Node
{
    vector<int> data;
    Node *left;
    Node *right;
    Node(vector<int> data, Node *left = nullptr, Node *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    void print() const
    {
        OUTPUT << "(";
        for (int i = 0; i < data.size(); i++)
        {
            OUTPUT << data[i];
            if (i == data.size() - 1)
                OUTPUT << ")";
            else
                OUTPUT << ",";
        }
        OUTPUT << "\n";
    }
};

class kDTree
{
private:
    int k;
    Node *root;
    int count;

private:
    // hàm phụ nếu cần
public:
    kDTree(int k = 2)
    {
        this->k = 2;
        this->root = nullptr;
        this->count = 0;
    }
    ~kDTree();
    const kDTree &operator=(const kDTree &other)
    {
        if (this != &other)
        {
            this->k = other.k;
            this->count = other.count;
            this->root = this->copy(other.root);
        }
        return *this;
    }
    kDTree(const kDTree &other)
    {
        this->k = other.k;
        this->count = other.count;
        this->root = this->copy(other.root);
    }
    int nodeCount() const;
    int height() const
    {
        return recGetTreeHeight(this->root);
    }
    int leafCount() const
    {
        return recLeafCount(this->root);
    }
    void inorderTraversal() const
    {
        this->recInOrderTraversal(this->root);
    }
    void preorderTraversal() const
    {
        this->recPreOrderTraversal(this->root);
    }
    void postorderTraversal() const
    {
        this->recPostOrderTraversal(this->root);
    }
    void insert(const vector<int> &point)
    {
        this->root = this->recInsert(this->root, point, 0);
        this->count++;
    }
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    /**************************************************************************************************/
    Node *recInsert(Node *temp, const vector<int> &point, int level)
    {
        if (temp == nullptr)
        {
            temp = new Node(point);
            return temp;
        }

        int dimension = level % k;

        if (point[dimension] < temp->data[dimension])
        {
            if (temp->left == nullptr)
            {
                temp->left = new Node(point);
                return temp->left;
            }
            return recInsert(temp->left, point, level + 1);
        }
        else
        {
            if (temp->right == nullptr)
            {
                temp->right = new Node(point);
                return temp->right;
            }
            return recInsert(temp->right, point, level + 1);
        }
    }
    Node *copy(Node *temp)
    {

        if (temp == nullptr)
            return nullptr;

        Node *newRoot = new Node(temp->data);
        newRoot->left = copy(temp->left);
        newRoot->right = copy(temp->right);
        return newRoot;
    }
    void recInOrderTraversal(Node *temp) const
    {
        if (temp == nullptr)
            return;

        recInOrderTraversal(temp->left);
        temp->print();
        recInOrderTraversal(temp->right);
    }
    void recPreOrderTraversal(Node *temp) const
    {
        if (temp == nullptr)
            return;
        temp->print();
        recInOrderTraversal(temp->left);
        recInOrderTraversal(temp->right);
    }
    void recPostOrderTraversal(Node *temp) const
    {
        if (temp == nullptr)
            return;

        recPostOrderTraversal(temp->left);
        recPostOrderTraversal(temp->right);
        temp->print();
    }
    int recLeafCount(Node *temp) const
    {
        if (temp == nullptr)
            return 0;

        if (temp->left == nullptr && temp->right == nullptr)
            return 1;
        return recLeafCount(temp->left) + recLeafCount(temp->right);
    }
    int tree_height(Node *root) const;
    int recGetTreeHeight(Node *root) const
    {
        if (root == NULL)
            return 0;
        return 1 + max(recGetTreeHeight(root->left), recGetTreeHeight(root->right));
    }
    // void nearestNeighbour(const vector<int> &target, Node *best);
    // void kNearestNeighbour(const vector<int> &target, int k, vector<Node *> &bestList);
};

// Please add more or modify as needed
