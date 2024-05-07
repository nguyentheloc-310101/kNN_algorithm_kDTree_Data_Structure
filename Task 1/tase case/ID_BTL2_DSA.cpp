#include "ID_BTL2_DSA.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
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
kDTree::kDTree(int k)
{
    this->k = k;
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
            root->right = insert(root->right, point, level + 1);
        }
        else if (point[0] < root->data[0])
        {
            root->left = insert(root->left, point, level + 1);
        }
    }
    else if (alpha == 1)
    {
        if (point[1] > root->data[1])
        {
            root->right = insert(root->right, point, level + 1);
        }
        else if (point[1] < root->data[1])
        {
            root->left = insert(root->left, point, level + 1);
        }
    }

    return root;
}

void kDTree::remove(const vector<int> &point)
{
    return this->remove(root, point, 0);
}

void kDTree::remove(Node *root, const vector<int> &point, int level)
{
    if (root == nullptr)
        return;

    int alpha = level % k;

    if (alpha == 0)
    {
        if (point[0] > root->data[0])
            remove(root->right, point, level + 1);
        else if (point[0] < root->data[0])
            remove(root->left, point, level + 1);
        else if (point[0] == root->data[0])
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return;
            }
            else if (root->right != nullptr)
            {
                root->data = root->right->data;
                remove(root->right, root->data, level + 1);
            }
            else if (root->right == nullptr && root->left != nullptr)
            {
                root->data = root->left->data;
                remove(root->left, root->data, level + 1);
            }
        }
    }
    else if (alpha == 1)
    {
        if (point[1] > root->data[1])
            remove(root->right, point, level + 1);
        else if (point[1] < root->data[1])
            remove(root->left, point, level + 1);
        else if (point[1] == root->data[1])
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return;
            }
            else if (root->right != nullptr)
            {
                root->data = root->right->data;
                remove(root->right, root->data, level + 1);
            }
            else if (root->right == nullptr && root->left != nullptr)
            {
                root->data = root->left->data;
                remove(root->left, root->data, level + 1);
            }
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
            search(root->right, point, level + 1);
        else if (point[0] < root->data[0])
            search(root->left, point, level + 1);
        else if (point[0] == root->data[0])
            return true;
    }
    else if (alpha == 1)
    {
        if (point[1] > root->data[1])
            search(root->right, point, level + 1);
        else if (point[1] < root->data[1])
            search(root->left, point, level + 1);
        else if (point[1] == root->data[1])
            return true;
    }

    return false;
}

void kDTree::buildTree(const vector<vector<int>> &pointList)
{
    this->root = this->buildTree(pointList, 0);
}

Node *kDTree::buildTree(const vector<vector<int>> &pointList, int level)
{
    vector<vector<int>> sortedPoints(pointList);

    if (pointList.empty())
    {
        return this->root;
    }

    int alpha = level % k;

    sort(pointList.begin(), pointList.end(), [alpha](const vector<int> &a, const vector<int> &b)
         { return a[alpha] < b[alpha]; });

    int median = (pointList.size() - 1) / 2;

    this->insert(pointList[median]);

    sortedPoints.erase(sortedPoints.begin() + median);

    vector<vector<int>> leftPoints(sortedPoints.begin(), sortedPoints.begin() + median);
    vector<vector<int>> rightPoints(sortedPoints.begin() + median + 1, sortedPoints.end());

    root->left = buildTree(leftPoints, level + 1);
    root->right = buildTree(rightPoints, level + 1);

    return this->root;
}

bool compareAsDim(vector<int> i1, vector<int> i2, int alpha)
{
    return (i1[alpha] < i2[alpha]);
}