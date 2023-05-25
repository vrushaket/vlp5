#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

void bfs(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* node = q.front();
        q.pop();
        cout<<node->val<<" ";
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
}


void pbfs(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qs = q.size();
        #pragma omp parallel for
        for(int i=0; i<qs; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                q.pop();
                cout<<node->val<<" ";
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
}

void dfs(TreeNode* root){
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        TreeNode* node = s.top();
        s.pop();
        cout<<node->val<<" ";
        if(node->right) s.push(node->right);
        if(node->left) s.push(node->left);
    }
}


void pdfs(TreeNode* root){
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        int ss = s.size();
        #pragma omp parallel for
        for(int i=0; i<ss; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                s.pop();
                cout<<node->val<<" ";
                if(node->right) s.push(node->right);
                if(node->left) s.push(node->left);
            }
        }
    }
}

int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    auto start= omp_get_wtime();
    cout<<"bfs : ";
    bfs(root);
    cout<<endl;
    auto end= omp_get_wtime();
    cout<<"timetaken :"<<end-start<<endl;
    
    start= omp_get_wtime();
    cout<<"pbfs : ";
    pbfs(root);
    cout<<endl;
    end= omp_get_wtime();
    cout<<"timetaken :"<<end-start<<endl;

    cout<<"dfs : ";
    dfs(root);
    cout<<endl;

    cout<<"pdfs : ";
    pdfs(root);
    cout<<endl;
}
