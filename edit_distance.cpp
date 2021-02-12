//executiontime on g4g: 0.01s
int editDistance(string s, string t)
{
    int n = s.length();
    int m = t.length();
    int** A = new int*[n+1];
    
    //first row
    A[0] = new int[m+1];
    for(int j = 0; j<=m; ++j)
        A[0][j] = j;
    //other rows
    for(int i = 1; i <=n; ++i){
        A[i] = new int[m+1];
        A[i][0] = i;
    }
    
    //fill matrix
    for(int i = 1; i<= n; ++i){
        for(int j = 1; j<= m; ++j){
            if(s[i-1] == t[j-1])
                A[i][j] = A[i-1][j-1];
            else
                A[i][j] = 1+min(A[i-1][j], min(A[i][j-1], A[i-1][j-1]));
        }
    }
    
     /*for(int i = 0; i<= n; i++){
        for(int j = 0; j<= m; ++j)
            std::cout<<A[i][j]<<" ";
        cout <<endl;
    }*/
    
    return A[n][m];
    
}