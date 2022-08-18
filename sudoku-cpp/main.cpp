#include "iostream"
#include "vector"
using namespace std;

int n = 9;
int m = 9;

void print_board(vector<vector<int>> &v)
{
    for(int i=0;i<n;i++)
    {
        if(i%3==0 && i!=0)
            cout<<"------------------------"<<endl;
        for(int j=0;j<m;j++)
        {
            if(j%3==0 && j!=0)
                cout<<"|";
            if(j==8) cout<<v[i][j];
            else
            {
                cout<<v[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

pair<int,int> find_empty(vector<vector<int>> &v)
{
    pair<int,int> ans;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(v[i][j]==0)
            {
                ans.first=i;
                ans.second=j;
                return ans;
            }
        }
    }
    return {-1,-1};

}

bool valid(vector<vector<int>> &v,int num,pair<int,int> ans)
{
    // Check for the row
    for(int i=0;i<m;i++)
    {
        if(v[ans.first][i]==num && ans.second!=i) return false;
    }
    // Check for the column
    for(int i=0;i<n;i++)
    {
        if(v[i][ans.second]==num && ans.first!=i) return false;
    }
    // Check for the box
    int box_xindex = ans.first/3;
    int box_yindex = ans.second/3;
    for(int i=box_xindex*3;i<box_xindex*3+3;i++)
    {
        for(int j=box_yindex*3;j<box_yindex*3+3;j++)
        {
            if(v[i][j]==num && (i!=ans.first || j!=ans.second)) return false;
        }
    }
    return true;
}

bool solve(vector<vector<int>> &v)
{
    pair<int,int> ans;
    ans = find_empty(v);
    if(ans.first==-1 && ans.second==-1) return true;
    else
    {
        int l = ans.first, r = ans.second;
        for(int i=1;i<10;i++)
        {
            if(valid(v,i,{l,r}))
            {
                v[l][r] = i;
                if(solve(v)) return true;
                v[l][r] = 0;  // Backtracking
            }
        }
        return false;
    }
}
int main()
{
    vector<vector<int>> v{
            {7, 8, 0, 4, 0, 0, 1, 2, 0},
            {6, 0, 0, 0, 7, 5, 0, 0, 9},
            {0, 0, 0, 6, 0, 1, 0, 7, 8},
            {0, 0, 7, 0, 4, 0, 2, 6, 0},
            {0, 0, 1, 0, 5, 0, 9, 3, 0},
            {9, 0, 4, 0, 6, 0, 0, 0, 5},
            {0, 7, 0, 3, 0, 0, 0, 1, 2},
            {1, 2, 0, 0, 0, 7, 4, 0, 0},
            {0, 4, 9, 2, 0, 6, 0, 0, 7}
    };
    print_board(v);
    solve(v);
    cout<<"___________________________" << endl;
    print_board(v);
}
