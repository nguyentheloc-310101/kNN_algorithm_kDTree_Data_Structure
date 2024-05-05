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
    kDTree(int k = 2);
    ~kDTree();
    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);
    int nodeCount() const;
    int height() const;
    int leafCount() const;
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    void insert(const vector<int> &point);
    Node *insert(Node *root, const vector<int> &point, int level);
    void remove(const vector<int> &point);
    void remove(Node *root, const vector<int> &point, int level);
    Node *findSmallest(Node *root);
    bool search(const vector<int> &point);
    bool search(Node *root, const vector<int> &point, int level);
    void buildTree(const vector<vector<int>> &pointList);

    void copy(Node *temp);
    void recInOrderTraversal(Node *temp) const;
    void recPreOrderTraversal(Node *temp) const;
    void recPostOrderTraversal(Node *temp) const;
    int recLeafCount(Node *temp) const;
    int tree_height(Node *root) const;
    // void nearestNeighbour(const vector<int> &target, Node *best);
    // void kNearestNeighbour(const vector<int> &target, int k, vector<Node *> &bestList);
};

// Please add more or modify as needed

/***Helper functions***/
// int heightBTS(Node *root)
// {
//     if (root == NULL)
//         return 0;
//     return 1 + max(heightBTS(root->left), heightBTS(root->right));
// }
void kDTree::copy(Node *temp)
{
    if (temp == nullptr)
        return;
    copy(temp->left);
    copy(temp->right);
    insert(temp->data);
}
void kDTree::recInOrderTraversal(Node *temp) const
{
    if (temp == nullptr)
        return;

    recInOrderTraversal(temp->left);
    temp->print();
    recInOrderTraversal(temp->right);
}

int kDTree::tree_height(Node *root) const
{
    // Get the height of the tree
    if (!root)
        return 0;
    else
    {

        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}
void kDTree::recPreOrderTraversal(Node *temp) const
{
    if (temp == nullptr)
        return;
    temp->print();
    recInOrderTraversal(temp->left);
    recInOrderTraversal(temp->right);
}

void kDTree::recPostOrderTraversal(Node *temp) const
{
    //* bước 1: xét trường hợp Cây đang rỗng
    if (temp == nullptr)
        return;

    //* bước 2: tìm cây con bên trái
    recPostOrderTraversal(temp->left);

    //* bước 3: tìm cây con bên phải
    recPostOrderTraversal(temp->right);

    temp->print();
    //* vì cơ chế root in cuối cùng
}
// main function
kDTree::kDTree(int k = 2)
{
    this->k = 2;
    this->root = nullptr;
    this->count = 0;
}
kDTree::kDTree(const kDTree &other)
{
    this->k = other.k;
    this->count = other.count;
    this->root = other.root;
}
int kDTree::height() const
{
    return tree_height(this->root);
}

void kDTree::inorderTraversal() const
{
    this->recInOrderTraversal(this->root);
};

void kDTree::preorderTraversal() const
{
    this->recPreOrderTraversal(this->root);
};

void kDTree::insert(const vector<int> &point)
{
    this->root = this->insert(root, point, 0);
    this->count++;
}

Node *kDTree::insert(Node *root, const vector<int> &point, int level)
{
    if (root == nullptr)
    {
        return new Node(point);
    }

    int alpha = level % this->k;

    if (alpha == 0)
    {
        if (point[0] > root->data[0])
        {
            root->right = insert(root->right, point, alpha);
        }
        else if (point[0] < root->data[0])
        {
            root->left = insert(root->left, point, alpha);
        }
    }
    else if (alpha == 1)
    {
        if (point[1] > root->data[1])
        {
            root->right = insert(root->right, point, alpha);
        }
        else if (point[1] < root->data[1])
        {
            root->left = insert(root->left, point, alpha);
        }
    }

    return root;
}

void kDTree::remove(const vector<int> &point)
{
    return this->remove(root, point, 0);
}

Node *kDTree::findSmallest(Node *root)
{
    Node* temp = root;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp;
}

void kDTree::remove(Node *root, const vector<int> &point, int level)
{
    if (root == nullptr)
        return;

    int alpha = level % k;

    if (alpha == 0)
    {
        if (point[0] > root->data[0])
            remove(root->right, point, alpha);
        else if (point[0] < root->data[0])
            remove(root->left, point, alpha);
        else if (point[0] == root->data[0])
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return;
            }
            else if (root->right != nullptr)
            {
                
            }
        }
    }
    else if (alpha == 1)
    {
        if (point[1] > root->data[1])
            remove(root->right, point, alpha);
        else if (point[1] < root->data[1])
            remove(root->left, point, alpha);
        else if (point[1] == root->data[1])
        {
        }
    }
}

bool kDTree::search(const vector<int> &point)
{
    return this->search(root, point, 0);
}

bool kDTree::search(Node *root, const vector<int> &point, int level)
{
    if (root == nullptr)
        return false;

    int alpha = level % k;

    if (alpha == 0)
    {
        if (point[0] > root->data[0])
            search(root->right, point, alpha);
        else if (point[0] < root->data[0])
            search(root->left, point, alpha);
        else if (point[0] == root->data[0])
            return true;
    }
    else if (alpha == 1)
    {
        if (point[1] > root->data[1])
            search(root->right, point, alpha);
        else if (point[1] < root->data[1])
            search(root->left, point, alpha);
        else if (point[1] == root->data[1])
            return true;
    }
}