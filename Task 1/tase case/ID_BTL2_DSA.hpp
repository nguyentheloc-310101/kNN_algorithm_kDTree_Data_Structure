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
    bool search(const vector<int> &point);
    bool search(Node *root, const vector<int> &point, int level);
    void buildTree(const vector<vector<int>> &pointList);
    Node *buildTree(const vector<vector<int>> &pointList, int level);

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
// void kDTree::copy(Node *temp)
// {
//     if (temp == nullptr)
//         return;
//     copy(temp->left);
//     copy(temp->right);
//     insert(temp->data);
// }
// void kDTree::recInOrderTraversal(Node *temp) const
// {
//     if (temp == nullptr)
//         return;

//     recInOrderTraversal(temp->left);
//     temp->print();
//     recInOrderTraversal(temp->right);
// }
// int kDTree::tree_height(Node *root) const
// {
//     // Get the height of the tree
//     if (!root)
//         return 0;
//     else
//     {

//         int left_height = tree_height(root->left);
//         int right_height = tree_height(root->right);
//         if (left_height >= right_height)
//             return left_height + 1;
//         else
//             return right_height + 1;
//     }
// }
// void kDTree::recPreOrderTraversal(Node *temp) const
// {
//     if (temp == nullptr)
//         return;
//     temp->print();
//     recInOrderTraversal(temp->left);
//     recInOrderTraversal(temp->right);
// }
// void kDTree::recPostOrderTraversal(Node *temp) const
// {
//     //* bước 1: xét trường hợp Cây đang rỗng
//     if (temp == nullptr)
//         return;

//     //* bước 2: tìm cây con bên trái
//     recPostOrderTraversal(temp->left);

//     //* bước 3: tìm cây con bên phải
//     recPostOrderTraversal(temp->right);

//     temp->print();
//     //* vì cơ chế root in cuối cùng
// }
// // main function
// kDTree::kDTree(int k = 2)
// {
//     this->k = k;
//     this->root = nullptr;
//     this->count = 0;
// }
// kDTree::kDTree(const kDTree &other)
// {
//     this->k = other.k;
//     this->count = other.count;
//     this->root = other.root;
// }
// int kDTree::height() const
// {
//     return tree_height(this->root);
// }

// void kDTree::inorderTraversal() const
// {
//     this->recInOrderTraversal(this->root);
// };

// void kDTree::preorderTraversal() const
// {
//     this->recPreOrderTraversal(this->root);
// };

// void kDTree::insert(const vector<int> &point)
// {
//     this->root = this->insert(root, point, 0);
//     this->count++;
// }

// Node *kDTree::insert(Node *root, const vector<int> &point, int level)
// {
//     if (root == nullptr)
//     {
//         return new Node(point);
//     }

//     int alpha = level % this->k;

//     if (alpha == 0)
//     {
//         if (point[0] > root->data[0])
//         {
//             root->right = insert(root->right, point, level + 1);
//         }
//         else if (point[0] < root->data[0])
//         {
//             root->left = insert(root->left, point, level + 1);
//         }
//     }
//     else if (alpha == 1)
//     {
//         if (point[1] > root->data[1])
//         {
//             root->right = insert(root->right, point, level + 1);
//         }
//         else if (point[1] < root->data[1])
//         {
//             root->left = insert(root->left, point, level + 1);
//         }
//     }

//     return root;
// }

// void kDTree::remove(const vector<int> &point)
// {
//     return this->remove(root, point, 0);
// }

// void kDTree::remove(Node *root, const vector<int> &point, int level)
// {
//     if (root == nullptr)
//         return;

//     int alpha = level % k;

//     if (alpha == 0)
//     {
//         if (point[0] > root->data[0])
//             remove(root->right, point, level + 1);
//         else if (point[0] < root->data[0])
//             remove(root->left, point, level + 1);
//         else if (point[0] == root->data[0])
//         {
//             if (root->left == nullptr && root->right == nullptr)
//             {
//                 delete root;
//                 return;
//             }
//             else if (root->right != nullptr)
//             {
//                 root->data = root->right->data;
//                 remove(root->right, root->data, level + 1);
//             }
//             else if (root->right == nullptr && root->left != nullptr)
//             {
//                 root->data = root->left->data;
//                 remove(root->left, root->data, level + 1);
//             }
//         }
//     }
//     else if (alpha == 1)
//     {
//         if (point[1] > root->data[1])
//             remove(root->right, point, level + 1);
//         else if (point[1] < root->data[1])
//             remove(root->left, point, level + 1);
//         else if (point[1] == root->data[1])
//         {
//             if (root->left == nullptr && root->right == nullptr)
//             {
//                 delete root;
//                 return;
//             }
//             else if (root->right != nullptr)
//             {
//                 root->data = root->right->data;
//                 remove(root->right, root->data, level + 1);
//             }
//             else if (root->right == nullptr && root->left != nullptr)
//             {
//                 root->data = root->left->data;
//                 remove(root->left, root->data, level + 1);
//             }
//         }
//     }
// }

// bool kDTree::search(const vector<int> &point)
// {
//     return this->search(root, point, 0);
// }

// bool kDTree::search(Node *root, const vector<int> &point, int level)
// {
//     if (root == nullptr)
//         return false;

//     int alpha = level % k;

//     if (alpha == 0)
//     {
//         if (point[0] > root->data[0])
//             search(root->right, point, level + 1);
//         else if (point[0] < root->data[0])
//             search(root->left, point, level + 1);
//         else if (point[0] == root->data[0])
//             return true;
//     }
//     else if (alpha == 1)
//     {
//         if (point[1] > root->data[1])
//             search(root->right, point, level + 1);
//         else if (point[1] < root->data[1])
//             search(root->left, point, level + 1);
//         else if (point[1] == root->data[1])
//             return true;
//     }
// }

// void kDTree::buildTree(const vector<vector<int>> &pointList)
// {
//     this->root = this->buildTree(pointList, 0);
// }

// Node *kDTree::buildTree(const vector<vector<int>> &pointList, int level)
// {
//     vector<vector<int>> sortedPoints(pointList);

//     if (pointList.empty())
//     {
//         return this->root;
//     }

//     int alpha = level % k;

//     sort(pointList.begin(), pointList.end(), compareAsDim);

//     int median = (pointList.size() - 1) / 2;

//     this->insert(pointList[median]);

//     sortedPoints.erase(sortedPoints.begin() + median);

//     vector<vector<int>> leftPoints(sortedPoints.begin(), sortedPoints.begin() + median);
//     vector<vector<int>> rightPoints(sortedPoints.begin() + median + 1, sortedPoints.end());

//     root->left = buildTree(leftPoints, level + 1);
//     root->right = buildTree(rightPoints, level + 1);

//     return this->root;
// }

// bool compareAsDim(vector<int> i1, vector<int> i2, int alpha)
// {
//     return (i1[alpha] < i2[alpha]);
// }