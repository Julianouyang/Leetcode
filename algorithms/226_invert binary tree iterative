TreeNode* invertTree(TreeNode* root) {
        if (!root)  return NULL;
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()){
            TreeNode* t = q.front();
            q.pop();
            TreeNode* temp = t->right;
            t->right = t->left;
            t->left = temp;
            if(t->left)
                q.push(t->left);
            if(t->right)
                q.push(t->right);
        }
        return root;
    }
