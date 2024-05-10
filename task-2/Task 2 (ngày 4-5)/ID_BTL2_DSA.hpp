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
        OUTPUT << " ";
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
    // ~kDTree();
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
    Node *remove(Node *root, const vector<int> &point, int level);
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

    Node *findMinValue(Node *root, int level, int alpha);
    vector<vector<int>> mergeSort(const vector<vector<int>> &arr, int alpha);
    vector<vector<int>> merge(vector<vector<int>> &left, vector<vector<int>> &right, int alpha);
    void nearestNeighbour(const vector<int> &target, Node *&best);
    void nearestNeighbour(Node *temp, const vector<int> &target, Node *&best, int level);
    void kNearestNeighbour(const vector<int> &target, int k, vector<Node *> &bestList);
    void kNearestNeighbour(Node *temp, const vector<int> &target, int k, vector<Node *> &bestList, int level);
    double distanceCount(vector<int> data1, const vector<int> data2, int k);
    void sortKNearest(const vector<int> &target, vector<Node *> &bestList);
    
    void printSpaces(int n)
    {
        for (int i = 0; i < n; ++i)
            cout << " ";
    }

    // Function to print BST in tree format recursively
    void printTree(Node *root, int space)
    {
        if (root == nullptr)
            return;

        const int spacing = 5; // Adjust spacing as needed

        // Increase distance between levels
        space += spacing;

        // Process right child first
        printTree(root->right, space);

        // Print current node after space count
        cout << endl;
        printSpaces(space - spacing);
        cout << "(";
        for (int i = 0; i < k; i++)
            cout << root->data[i] << ",";
        cout << ")";

        // Process left child
        printTree(root->left, space);
    }
};

class kNN
{
private:
    int k;

public:
    kNN(int k = 5);
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};