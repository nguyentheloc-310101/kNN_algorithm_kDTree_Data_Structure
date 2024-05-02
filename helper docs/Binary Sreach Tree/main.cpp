#include "Binary_Search_Trees.cpp"

//! lệnh chạy, chạy từng lệnh
//^ g++ -o main main.cpp Binary_Search_Trees.cpp -I.-std=c++11
//^ ./main file_input -> vd : ./main input.txt

//~ input - check insert and delete -> ./main input.txt
//~ input1 - check Get, IndexOf and Contains -> ./main input1.txt
//~ input2 - check selectionSort, subSingly_Linked_List, reverse -> ./main input2.txt

int main(int argc, char ** argv) {
    string str;
    cout << argv[1] << endl;
    ifstream input(argv[1]);
    int count = 1;
    BSTNode<int>* root = nullptr;

    while(getline(input, str)){
        stringstream ss(str);
        string signature;
        ss >> signature;
        if(signature == "Insertion")
        {
            int data;
            ss >> data;
            root = insertBTSNode(root, data);
            cout << "Insertion node " <<  data << " : hight " << heightBTS(root)  << endl;
            cout << "PreOrder : "; preoderBTS(root); cout << endl;
            cout << "InOrder : "; inoderBTS(root); cout << endl;
            cout << "PostOrder : "; postoderBTS(root); cout << endl;
            cout << "BFS : "; bfsBTS(root); cout << endl;
        }
        else if(signature == "Deletion")
        {
            int data;
            ss >> data;
            root = deleteBTSNode(root, data);
            cout << "Deletion node " <<  data << " : hight " << heightBTS(root)  << endl;
            cout << "PreOrder : "; preoderBTS(root); cout << endl;
            cout << "InOrder : "; inoderBTS(root); cout << endl;
            cout << "PostOrder : "; postoderBTS(root); cout << endl;
            cout << "BFS : "; bfsBTS(root); cout << endl;
        }
        else if (signature == "Find")
        {
            int data;
            ss >> data;
            cout << "Find node " <<  data << " : " << (findBTSNode(root, data)? "true" : "false")  << endl;
        }
        count++;
    }
    cout << "end " << endl;
    return 0;
}