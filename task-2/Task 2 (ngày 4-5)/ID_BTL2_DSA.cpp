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
    {
        return;
    }

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
        return max(left_height, right_height) + 1;
        // if (left_height >= right_height)
        //     return left_height + 1;
        // else
        //     return right_height + 1;
    }
}
void kDTree::recPreOrderTraversal(Node *temp) const
{
    if (temp == nullptr)
    {
        return;
    }
    temp->print();
    recPreOrderTraversal(temp->left);
    recPreOrderTraversal(temp->right);
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
int kDTree::nodeCount() const
{
    return this->count;
}
int kDTree::leafCount() const
{
    return this->recLeafCount(this->root);
}
int kDTree::recLeafCount(Node *temp) const
{
    if (temp == nullptr)
    {
        return 0;
    }
    if (!temp->left && !temp->right)
    {
        return 1;
    }

    return recLeafCount(temp->left) + recLeafCount(temp->right);
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

void kDTree::postorderTraversal() const
{
    this->recPostOrderTraversal(this->root);
}

void kDTree::insert(const vector<int> &point)
{
    if (point.size() > k)
    {
        return;
    }
    this->root = this->insert(root, point, 0);
    this->count++;
}

Node *kDTree::insert(Node *temp, const vector<int> &point, int level)
{

    if (temp == nullptr)
    {
        return new Node(point);
    }

    int alpha = level % this->k;

    if (point[alpha] >= temp->data[alpha])
    {
        temp->right = insert(temp->right, point, level + 1);
    }
    else if (point[alpha] < temp->data[alpha])
    {
        temp->left = insert(temp->left, point, level + 1);
    }

    return temp;
}

void kDTree::remove(const vector<int> &point)
{
    this->root = this->remove(root, point, 0);
}

Node *kDTree::remove(Node *root, const vector<int> &point, int level)
{
    if (root == nullptr)
        return nullptr;

    int alpha = level % k;

    if (point[alpha] >= root->data[alpha] && point != root->data)
    {
        root->right = remove(root->right, point, level + 1);
    }
    else if (point[alpha] < root->data[alpha])
    {
        root->left = remove(root->left, point, level + 1);
    }
    else if (point == root->data)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            this->count--;
            return nullptr;
        }
        else if (root->right != nullptr)
        {
            Node *temp = findMinValue(root->right, level + 1, alpha);
            root->data = temp->data;
            root->right = remove(root->right, temp->data, level + 1);
        }
        else if (root->right == nullptr && root->left != nullptr)
        {
            Node *temp = findMinValue(root->left, level + 1, alpha);
            root->data = temp->data;

            Node *temp1 = root->left;
            root->right = temp1;
            root->left = nullptr;

            root->right = remove(root->right, temp->data, level + 1);
        }
    }
    return root;
}

Node *kDTree::findMinValue(Node *root, int level, int alpha)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    int current_alpha = level % k;

    if (current_alpha == alpha)
    {
        if (root->left != nullptr)
        {
            return findMinValue(root->left, level + 1, alpha);
        }
        else
        {
            return root;
        }
    }
    else
    {
        Node *min_left = findMinValue(root->left, level + 1, alpha);
        Node *min_right = findMinValue(root->right, level + 1, alpha);

        Node *min_node = root;
        if (min_left != nullptr && min_left->data[alpha] < min_node->data[alpha])
        {
            min_node = min_left;
        }
        if (min_right != nullptr && min_right->data[alpha] < min_node->data[alpha])
        {
            min_node = min_right;
        }
        return min_node;
    }
}

bool kDTree::search(const vector<int> &point)
{
    // cout << this->search(root, point, 0) << endl;
    return search(root, point, 0);
}
bool kDTree::search(Node *root, const vector<int> &point, int level)
{
    if (root == nullptr)
        return false;

    int alpha = level % k;

    if (point == root->data)
    {
        return true;
    }

    if (point[alpha] >= root->data[alpha] && point != root->data)
        return search(root->right, point, level + 1);
    else if (point[alpha] < root->data[alpha])
        return search(root->left, point, level + 1);

    // Ensure a default return statement is present
    return false;
}

void kDTree::buildTree(const vector<vector<int>> &pointList)
{
    this->root = this->buildTree(pointList, 0);
    // this->printTree(root, 0);
}

Node *kDTree::buildTree(const vector<vector<int>> &pointList, int level)
{
    int size = pointList.size();
    if (size == 0)
    {
        return nullptr;
    }
    else if (size == 1)
    {
        this->count++;
        return new Node(pointList[0]);
    }
    else
    {
        // sort the pointList using merge sort
        int alpha = level % k;
        vector<vector<int>> sortedPointList = mergeSort(pointList, alpha);

        // find the median index
        int medianIndex = (size - 1) / 2;
        while (medianIndex > 0 && sortedPointList[medianIndex][alpha] == sortedPointList[medianIndex - 1][alpha])
        {
            medianIndex--;
        }

        // create a new node with the median point as its data
        Node *node = new Node(sortedPointList[medianIndex]);

        // split the pointList into left and right sublists
        vector<vector<int>> left(sortedPointList.begin(), sortedPointList.begin() + medianIndex);
        vector<vector<int>> right(sortedPointList.begin() + medianIndex + 1, sortedPointList.end());

        // recursively build the left and right subtrees
        node->left = buildTree(left, level + 1);
        node->right = buildTree(right, level + 1);

        this->count++;
        return node;
    }
}

vector<vector<int>> kDTree::mergeSort(const vector<vector<int>> &arr, int alpha)
{
    if (arr.size() <= 1)
    {
        return arr;
    }

    int mid = arr.size() / 2;

    vector<vector<int>> left(arr.begin(), arr.begin() + mid);
    vector<vector<int>> right(arr.begin() + mid, arr.end());

    left = mergeSort(left, alpha);
    right = mergeSort(right, alpha);

    return merge(left, right, alpha);
}

vector<vector<int>> kDTree::merge(vector<vector<int>> &left, vector<vector<int>> &right, int alpha)
{
    vector<vector<int>> result;

    while (!left.empty() && !right.empty())
    {
        if (left[0][alpha] <= right[0][alpha])
        {
            result.push_back(left[0]);
            left.erase(left.begin());
        }
        else
        {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    while (!left.empty())
    {
        result.push_back(left[0]);
        left.erase(left.begin());
    }

    while (!right.empty())
    {
        result.push_back(right[0]);
        right.erase(right.begin());
    }

    return result;
}

bool compareAsDim(vector<int> i1, vector<int> i2, int alpha)
{
    return (i1[alpha] <= i2[alpha]);
}

double distance(vector<int> a, vector<int> b)
{
    int sum = 0;
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        sum += pow((a[i] - b[i]), 2);
    }

    return sqrt(sum);
}

void kDTree::nearestNeighbour(const vector<int> &target, Node *&best)
{
    best = nullptr;
    nearestNeighbour(root, target, best, 0);
}

void kDTree::nearestNeighbour(Node *temp, const vector<int> &target, Node *&best, int level)
{
    if (!temp)
        return;

    if (!temp->left && !temp->right && !best)
        best = temp;

    int alpha = level % k;

    int d = abs(target[alpha] - temp->data[alpha]);

    if (target[alpha] < temp->data[alpha])
    {
        nearestNeighbour(temp->left, target, best, level + 1);
    }
    if (target[alpha] >= temp->data[alpha])
    {
        nearestNeighbour(temp->right, target, best, level + 1);
    }

    double r = distance(target, temp->data);

    if (!best || r < distance(target, best->data))
    {
        best = temp;
    }

    double R = distance(target, best->data);
    // cout << "\ntemp: " << temp->data[0] << " " << temp->data[1]
    //      << " best: " << best->data[0] << " " << best->data[1] << endl;
    // cout << "r: " << r << " R: " << R << endl;

    // cout << "\n temp go: " << temp->data[0] << " " << temp->data[1] << endl;

    if (d <= r)
    {
        if (target[alpha] >= temp->data[alpha])
        {
            nearestNeighbour(temp->left, target, best, level + 1);
        }
        else
        {
            nearestNeighbour(temp->right, target, best, level + 1);
        }
    }
}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<Node *> &bestList)
{
    this->kNearestNeighbour(root, target, k, bestList, 0);
}
void kDTree::kNearestNeighbour(Node *temp, const vector<int> &target, int k, vector<Node *> &bestList, int level)
{
    int alpha = level % this->k;

    if (temp == nullptr)
        return;
    if (temp->data[alpha] > target[alpha])
    {
        kNearestNeighbour(temp->left, target, k, bestList, level + 1);
        if (bestList.size() < k)
        {
            bestList.push_back(temp);
            // goi sort
            this->sortKNearest(target, bestList);
            this->kNearestNeighbour(temp->right, target, k, bestList, level + 1);
        }
        else
        {
            // khi  == full list
            double distanceLast = distanceCount(bestList.back()->data, target, this->k);
            double distanceTempToTarget = distanceCount(temp->data, target, this->k);

            if (distanceLast > distanceTempToTarget)
            {
                bestList.pop_back();
                bestList.push_back(temp);
                this->sortKNearest(target, bestList);
            }

            double DistanceCurrAlpha = abs(temp->data[alpha] - target[alpha]);
            if (DistanceCurrAlpha < distanceLast)
            {
                this->kNearestNeighbour(temp->right, target, k, bestList, level + 1);
            }
        }
    }
    else
    {
        kNearestNeighbour(temp->right, target, k, bestList, level + 1);
        if (bestList.size() < k)
        {
            bestList.push_back(temp);
            // goi sort
            this->sortKNearest(target, bestList);
            this->kNearestNeighbour(temp->left, target, k, bestList, level + 1);
        }
        else
        {

            double distanceLast = distanceCount(bestList.back()->data, target, this->k);
            double distanceTempToTarget = distanceCount(temp->data, target, this->k);

            if (distanceLast > distanceTempToTarget)
            {
                bestList.pop_back();
                bestList.push_back(temp);
                this->sortKNearest(target, bestList);
            }

            double DistanceCurrAlpha = abs(temp->data[alpha] - target[alpha]);
            if (DistanceCurrAlpha < distanceLast)
            {
                // sua
                this->kNearestNeighbour(temp->left, target, k, bestList, level + 1);
            }
        }
    }
}
// ham sort
void kDTree::sortKNearest(const vector<int> &target, vector<Node *> &bestList)
{
    int len = bestList.size();
    double *check = new double[len];
    for (int i = 0; i < len; i++)
    {
        double temp = distance(target, bestList[i]->data);
        check[i] = temp;
    }
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (check[j] > check[j + 1])
            {
                swap(check[j], check[j + 1]);
                swap(bestList[j], bestList[j + 1]);
            }
        }
    }
    delete[] check;
}

double kDTree::distanceCount(vector<int> data1, const vector<int> data2, int k)
{
    double sum = 0;
    for (int i = 0; i < k; i++)
    {
        double sumTemp = data1[i] - data2[i];
        sum += sumTemp * sumTemp;
    }
    return sqrt(sum);
}