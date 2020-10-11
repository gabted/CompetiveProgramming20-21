/*
	execution time: 0.57 su G4G
	
	Time complexity: O(n), is a post-order visit
	
	Space Complexity: O(h), for recursive stack allocation
	
	Here are reported only the functions and structures used to implement
	the algorithm, I/O and tree-building operation are present in
	https://practice.geeksforgeeks.org/problems/maximum-path-sum/1
*/


struct result {
    int maximumPath;    //maximum leef-to-leef path inside a tree
    int maximumBranch;  //maximum root-to-leef path inside a tree
};

result computeMaxPath(Node* root){
    if(root == nullptr)
        return {0, 0};
    
    if(root->left == nullptr && root->right == nullptr){
       return {std::numeric_limits<int>::min(), root->data};   
    }else if (root->left == nullptr){
        result right = computeMaxPath(root->right);
        return {right.maximumPath, root->data+right.maximumBranch};
    }
    else if (root->right == nullptr){
        result left = computeMaxPath(root->left);
        return {left.maximumPath, root->data+left.maximumBranch};
    }
    else {
        result left = computeMaxPath(root->left);
        result right = computeMaxPath(root->right);
        int maxBranch = (root->data) + ((right.maximumBranch>left.maximumBranch)?right.maximumBranch:left.maximumBranch);
        int centerPath = root->data + right.maximumBranch + left.maximumBranch;
        int rightPath = right.maximumPath;
        int leftPath = left.maximumPath;
        int maxPath = std::max(centerPath, std::max(rightPath, leftPath));
        return {maxPath, maxBranch};
        
    }
}

int maxPathSum(Node* root)
{ 
    return computeMaxPath(root).maximumPath;  
}