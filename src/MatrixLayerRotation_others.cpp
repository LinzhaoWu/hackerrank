#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#if 1
int main()
{	int M, N, R;
	cin >> M >> N >> R;
    
	int mat[M][N];
	for(int i=0; i<M; i++)
	{	for(int j=0; j<N; j++)
		{	cin >> mat[i][j];	}
	}
	
	int sti=0, stj=0;
	vector<int> temp;
	//cout << endl << endl;
	for(int x=M-1, y=N-1; x>0 && y>0; x-=2, y-=2,sti++,stj++)
	{	int rot = R%(2*(x+y));
		int sz = 2*(x+y);
		int i=sti, j=stj;
		//cout << "x,y : " << x << "," << y << "\trot : "<< rot << endl;
		//cout << "A : " ;
		for(int cnt=0; cnt<sz; cnt++)
		{	//cout << mat[i][j] << "  ";
			temp.push_back(mat[i][j]);
			if(j==sti && i<sti+x)
			{	i++;	}
			else if(i==sti+x && j<stj+y)
			{	j++;	}
			else if(j==stj+y && i>sti)
			{	i--;	}
			else if(i==sti && j>stj)
			{	j--;	}
		}
		
		i=sti, j=stj;
		int npos;
		//cout << "\nRotated : ";
		for(int cnt=0; cnt<sz; cnt++)
		{	npos = (cnt-rot)%sz;
			npos = (npos<0)? npos+sz : npos;
			mat[i][j] = temp[npos];
			//cout << mat[i][j] << "  ";
			if(j==sti && i<sti+x)
			{	i++;	}
			else if(i==sti+x && j<stj+y)
			{	j++;	}
			else if(j==stj+y && i>sti)
			{	i--;	}
			else if(i==sti && j>stj)
			{	j--;	}
		}
		temp.clear();
		//cout << endl;
	}
	
	for(int i=0; i<M; i++)
	{	for(int j=0; j<N; j++)
		{	cout << mat[i][j] << " ";	}
		cout << endl;
	}
    return 0;
}
#else
#include <bits/stdc++.h>
using namespace std;

/*
So, this challenge can be broken into following parts:
1. Seperate each strip/layers from the original matrix.
2. Rotate each strip by R times.
3. Reformulate the matrix from the strip.

*/

typedef pair<int, int> coord;   // Defining a new type to represent each coordinates

int M, N, R;

void addLayer(vector<coord> &layer, int r, int c, int len, int rAdd, int cAdd) {
    while(len-- > 0) {
        layer.push_back(make_pair(r, c));
        r += rAdd;
        c += cAdd;
    }
}

// `rotate` function will read a MxN matrix and rotate it by R times.
vector<vector<int>> rotate(vector<vector<int>> matrix) {
    vector<vector<int>> ret(M, vector<int>(N));
    
    // Since minimum of `M` and `N` is even, it is guaranteed that there will be
    // `min(M, N)/2` layers.
    int nLayers = min(M, N)/2;
    
    // Now, we will rip all the layers. The i = 0 represents the first layer,
    // i = 1 represents second, and so on.
    
    int m = M, n = N;
    for(int i = 0; i < nLayers; i++) {
        vector<coord> layer;

        // Top strip
        int r = i, c = i;
        addLayer(layer, r, c, n-1, +0, +1);
       
        // Right strip
        r = layer.back().first;
        c = layer.back().second+1;
        addLayer(layer, r, c, m-1, +1, +0);

        // Bottom strip
        r = layer.back().first+1;
        c = layer.back().second;
        addLayer(layer, r, c, n-1, 0, -1);
        
        // Left strip
        r = layer.back().first;
        c = layer.back().second-1;
        addLayer(layer, r, c, m-1, -1, 0);

        // Checking
        /*
        for(auto x: layer)
            printf("(%d, %d) ", x.first, x.second);
        cout << endl;
        */
        
        int sz = layer.size();
        for(int id = 0; id < sz; id++) {
            int r1 = layer[id].first, c1 = layer[id].second;
            int r2 = layer[((id+R)%sz+sz)%sz].first, c2 = layer[((id+R)%sz+sz)%sz].second;
            ret[r1][c1] = matrix[r2][c2];
            //printf("[(%d, %d) <- (%d, %d): %d], ", r1, c1, r2, c2, ret[r1][c1]);
        }
        //cout << endl << endl;
        
        m -= 2;
        n -= 2;
    }

    return ret;
}

int main()
{
    // Reading the matrix.
    cin >> M >> N >> R;
    vector < vector<int> > matrix(M, vector<int>(N));
    
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }
    
    
    vector<vector<int> > ans = rotate(matrix);
    
    // Procedure to print output
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    

    return 0;
}
#endif