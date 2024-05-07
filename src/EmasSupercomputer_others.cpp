#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <map>
#include <list>

using namespace std;

#define OHTERS_1

#ifdef OHTERS_1
int n, m;
char s[20][20];
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i=1; i<=n; i++) cin >> &s[i][1];
    int res = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            int len = 0;
            for (len=0; len<15; len++) {
                if (s[i+len][j] != 'G' || s[i-len][j] != 'G' || s[i][j-len] != 'G' || s[i][j+len] != 'G') break;
                s[i+len][j] = s[i-len][j] = s[i][j-len] = s[i][j+len] = 'T';
                int area1 = 4*len+1;
                for (int k=1; k<=n; k++) {
                    for (int l=1; l<=m; l++) {
                        if (s[k][l] != 'G') continue;
                        int len2 = 0;
                        while (s[k+len2][l] == 'G' && s[k-len2][l] == 'G' && s[k][l-len2] == 'G' && s[k][l+len2] == 'G') len2++;
                        res = max(res, area1 * (4*len2-3));
                    }
                }
            }
            for (int k=0; k<len; k++)
                s[i+k][j] = s[i-k][j] = s[i][j-k] = s[i][j+k] = 'G';
        }
    }
    cout << res << "\n";
    return 0;
}
#elif defined(OTHERS_2)
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#if defined(_MSC_VER) || __cplusplus > 199711L
#define aut(r,v) auto r = (v)
#else
#define aut(r,v) __typeof(v) r = (v)
#endif
#define each(it,o) for(aut(it, (o).begin()); it != (o).end(); ++ it)
#define all(o) (o).begin(), (o).end()
#define pb(x) push_back(x)
#define mp(x,y) make_pair((x),(y))
#define mset(m,v) memset(m,v,sizeof(m))
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef vector<int> vi; typedef pair<int, int> pii; typedef vector<pair<int, int> > vpii; typedef long long ll;
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }

int main() {
	int N; int M;
	while(~scanf("%d%d", &N, &M)) {
		vector<string> a(N);
		rep(i, N) cin >> a[i];
		int ans = 0;
		rep(y0, N) rep(x0, M) rer(s0, 1, min({ y0 + 1, N - y0, x0 + 1, M - x0 })) {
			vector<vector<bool> > good(N, vector<bool>(M));
			rep(i, N) rep(j, M)
				good[i][j] = a[i][j] == 'G';
			bool ok = true;
			rer(d, -s0 + 1, s0 - 1) {
				ok &= good[y0 + d][x0];
				ok &= good[y0][x0 + d];
				good[y0 + d][x0] = good[y0][x0 + d] = false;
			}
			if(!ok) continue;
			rep(y1, N) rep(x1, M) {
				int maxs1 = min({ y1 + 1, N - y1, x1 + 1, M - x1 });
				int s1 = maxs1;
				rer(d, -maxs1 + 1, maxs1 - 1) {
					if(!good[y1 + d][x1] || !good[y1][x1 + d])
						amin(s1, abs(d) - 1);
				}
				if(s1 > 0)
					amax(ans, ((s0 - 1) * 4 + 1) * ((s1 - 1) * 4 + 1));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
#elif defined(OTHERS_3)
int m,n,i,j,k,ans=0;
char s[20][20];

int cal() {
    int x,y,ss=0,p;
    for (k=0;k<min(min(i+1,m-i),min(j+1,n-j));k++)
        if (s[i+k][j]=='B' || s[i-k][j]=='B' || s[i][j+k]=='B' || s[i][j-k]=='B')
        break;
        else {
        s[i+k][j]=s[i-k][j]=s[i][j+k]=s[i][j-k]='B';
        for (x=0;x<m;x++)
            for (y=0;y<n;y++)
            if (s[x][y]=='G') {
            for (p=0;p<min(min(x+1,m-x),min(y+1,n-y));p++)
                if (s[x+p][y]=='B' || s[x-p][y]=='B' || s[x][y+p]=='B' || s[x][y-p]=='B')
                break;
            ss=max(ss,(k*4+1)*(p*4-3));
        }
    }
    for (k--;k>=0;k--)
        s[i+k][j]=s[i-k][j]=s[i][j+k]=s[i][j-k]='G';
    return ss;
}

int main() {
    cin>>m>>n;
    for (i=0;i<m;i++)
        scanf("%s",s[i]);
    for (i=0;i<m;i++)
    for (j=0;j<n;j++)
    if (s[i][j]=='G')
    ans=max(ans,cal());
    cout<<ans<<endl;
    return 0;
}

#elif defined(OTHERS_4)
char s[100][100];

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", s[i]);
    }
    bool mark[n][m];
    int answer = 0;
    for (int a = 0; a < n; ++ a) {
        for (int b = 0; b < m; ++ b) {
            if (s[a][b] == 'G') {
                memset(mark, false, sizeof(mark));
                for (int da = 0; ; ++ da) {
                    bool flag = true;
                    for (int k = 0; k < 4; ++ k) {
                        int tx = a + dx[k] * da;
                        int ty = b + dy[k] * da;
                        if (tx >= 0 && ty >= 0 && tx < n && ty < m && s[tx][ty] == 'G') {
                            mark[tx][ty] = true;
                        } else {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) {
                        break;
                    }
                    int area1 = da * 4 + 1;

                    for (int x = 0; x < n; ++ x) {
                        for (int y = 0; y < m; ++ y) {
                            if (s[x][y] == 'B' || mark[x][y]) {
                                continue;
                            }
                            int d = 0;
                            while (true) {
                                bool flag = true;
                                for (int k = 0; k < 4; ++ k) {
                                    int tx = x + dx[k] * (d + 1);
                                    int ty = y + dy[k] * (d + 1);
                                    if (tx >= 0 && ty >= 0 && tx < n && ty < m && s[tx][ty] == 'G' && !mark[tx][ty]) {

                                    } else {
                                        flag = false;
                                        break;
                                    }
                                }
                                if (!flag) {
                                    break;
                                }
                                ++ d;
                            }
                            int area2 = d * 4 + 1;
                            answer = max(answer, area1 * area2);
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", answer);

    return 0;
}
#elif defined(OTHERS_5)

const int MAXN = 20;
const int INF = 2147483647;
const int FIRST = -1;
const int SECOND = -2;

int n, m;
int grid[MAXN][MAXN];

void clearGrid(int value) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (grid[i][j] == value)
				grid[i][j] = 1;
		}
	}
}

int grow(int x, int y, int value) {
	if (grid[x][y] <= 0)
		return 0;
	int size = 1;
	int area = 1;
	while (grid[x + size][y] > 0 
		&& grid[x][y + size] > 0
		&& grid[x - size][y] > 0
		&& grid[x][y - size] > 0) {
		area += 4;
		grid[x + size][y] = value;
		grid[x][y + size] = value;
		grid[x - size][y] = value;
		grid[x][y - size] = value;
		++size;
	}
	return area;
}

int main(void)
{
#ifdef LOCAL
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif 


	scanf("%d %d", &n, &m);

	for (int i = 0; i < MAXN; ++i) {
		for (int j = 0; j < MAXN; ++j) {
			grid[i][j] = 0;
		}
	}

	for (int i = 1; i <= n; ++i) {
		scanf("\n");
		for (int j = 1; j <= m; ++j) {
			char c;
			scanf("%c", &c);
			if (c == 'G')
				grid[i][j] = 1;
		}
	}


	int maxAns = 0;
	for (int x1 = 1; x1 <= n; ++x1) {
		for (int y1 = 1; y1 <= m; ++y1) {
			int area1 = grow(x1, y1, FIRST);
			for (int x2 = 1; x2 <= n; ++x2) {
				for (int y2 = 1; y2 <= m; ++y2) {
					int area2 = grow(x2, y2, SECOND);
					if (area1 * area2 > maxAns)
						maxAns = area1 * area2;
					clearGrid(SECOND);
				}
			}
			clearGrid(FIRST);
		}
	}
	printf("%d", maxAns);
	return 0;
#endif