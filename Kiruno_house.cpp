#include <cstdio>
#include <cstring>
using namespace std;
/** LGP3693 Kiruno's House */

/** Const Data */
const int MAX_X = 20, MAX_Y = 20, MAX_H = 25;
const int dx[8] = {-1, -1,  0,  1,  1,  1,  0, -1};
const int dy[8] = { 0, -1, -1, -1,  0,  1,  1,  1};
const int ddx[6] = {0, 0, 0, 0, 1, -1};
const int ddy[6] = {0, 0, 1, -1, 0, 0};
const int ddh[6] = {1, -1, 0, 0, 0, 0};

/** Data */
bool is_ice_block[MAX_X][MAX_Y][MAX_H];
int frozen_degrees[MAX_X][MAX_Y];
int N, HR, HC, HX, HY, HM;
int kiruno_ice_block = 0;

/** Tool Func */
inline bool is_snowfield(int x) {
    return 0 <= x && x < N;
}
inline bool is_in_height(int h) {
    return 0 <= h && h <= HM;
}
inline bool is_in_range(int R, int C, int H) {
    return is_snowfield(R) && is_snowfield(C) && is_in_height(H);
}
inline bool is_under_height(int h) {
    return 0 <= h && h < HM;
}
bool has_dependence(int R, int C, int H) {
    bool ret = H == 0;
    for (int i = 0; i < 6; i++) {
        int nx = ddx[i] + R, ny = ddy[i] + C, nh = ddh[i] + H;
        if (is_in_range(nx, ny, nh)) {
            ret = ret || is_ice_block[nx][ny][nh];
        }
    }
    return ret;
}
/*
template <typename T, typename U>
struct pair {
    T first;
    U second;
};
template <typename T, typename U>
pair<T, U> make_pair(const T& a, const U& b) {
    pair<T, U> ret;
    ret.first = a; ret.second = b;
    return ret;
}
bool vis[MAX_X][MAX_Y][MAX_H];
// 返回True表10示接地
pair<bool, int> dfs_broken(int R, int C, int H) {
    if (!is_ice_block[R][C][H]) return make_pair(false, 0);
    if (H == 0) return make_pair(true, 1);
    pair<bool, int> ret = make_pair(false, 0);
    for (int i = 0; i < 6; i++) {
        if (is_in_range(R, C, H) && !vis[R][C][H]) {
            vis[R][C][H] = true;
            pair<bool, int> p = dfs_broken(R + ddx[i], C + ddy[i], H + ddh[i]);
            ret.first = ret.first || p.first;
            ret.second += p.second;
        }
    }
    return ret;
} */
int get_broken(int R, int C, int H) {
    //memset(vis, 0, sizeof(vis));
    //int ret = 0;
    //pair<bool, int> p = dfs_broken(R, C, H);
    //return p.first ? 0 : p.second;
    return 0;
}
/** Operation */
void ICE_BARRAGE(int R, int C, int D, int S) {
    int ndx = dx[D], ndy = dy[D], total = 0;
    for (int i = 0; i <= S; i++) {
        int nx = R + ndx * i, ny = C + ndy * i;
        if (is_ice_block[nx][ny][0]) break;
        if (!is_snowfield(nx) || !is_snowfield(ny)) break;
        if (frozen_degrees[nx][ny] == 4) continue;
        frozen_degrees[nx][ny] += 1;
        total += 1;
    }
    printf("CIRNO FREEZED %d BLOCK(S)\n", total);
}

void MAKE_ICE_BLOCK() {
    int total = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (frozen_degrees[i][j] == 4) {
                frozen_degrees[i][j] = 0;
                total += 1;
            }
        }
    }
    kiruno_ice_block += total;
    printf("CIRNO MADE %d ICE BLOCK(S),NOW SHE HAS %d ICE BLOCK(S)\n", 
        total, kiruno_ice_block);
}

void PUT_ICE_BLOCK(int R, int C, int H) {
    if (kiruno_ice_block == 0) {
        printf("CIRNO HAS NO ICE_BLOCK\n");
    } else if (is_ice_block[R][C][H]) {
        printf("BAKA CIRNO,CAN'T PUT HERE\n");
    } else if (!has_dependence(R, C, H)) {
        printf("BAKA CIRNO,CAN'T PUT HERE\n");
    } else if (R < HR || HR + HX - 1 < R || C < HC || HC + HY - 1 < C) {
        printf("CIRNO MISSED THE PLACE\n");
        kiruno_ice_block -= 1;
        is_ice_block[R][C][H] = true;
        if (H == 0) frozen_degrees[R][C] = 0;
    } else if (HR + 1 <= R && R <= HR + HX - 2 && HC + 1 <= C && C <= HC + HY - 2) {
        printf("CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE\n");
        kiruno_ice_block -= 1;
        is_ice_block[R][C][H] = true;
        if (H == 0) frozen_degrees[R][C] = 0;
    } else {
        kiruno_ice_block -= 1;
        is_ice_block[R][C][H] = true;
        if (H == 0) frozen_degrees[R][C] = 0;
        printf("CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS %d ICE_BLOCK(S)\n", kiruno_ice_block);
    }
}

void REMOVE_ICE_BLOCK(int R, int C, int H) {
    if (!is_ice_block[R][C][H]) {
        printf("BAKA CIRNO,THERE IS NO ICE_BLOCK\n");
    } else {
        kiruno_ice_block += 1;
        is_ice_block[R][C][H] = false;  
        // TODO write get_broken
        int broken = get_broken(R, C, H);
        if (broken) {
            printf("CIRNO REMOVED AN ICE_BLOCK,AND %d BLOCK(S) ARE BROKEN\n", broken);
        } else {
            printf("CIRNO REMOVED AN ICE_BLOCK\n");
        }
    }
}

/** Main Func */
void main_loop(int M) {
    int R, C, D, S, H;
    char op[100];
    for (int i = 1; i <= M; i++) {
        scanf("%s", op);
        if (strcmp(op, "ICE_BARRAGE") == 0) {
            scanf("%d %d %d %d", &R, &C, &D, &S);
            ICE_BARRAGE(R, C, D, S);
        } else if (strcmp(op, "MAKE_ICE_BLOCK") == 0) {
            MAKE_ICE_BLOCK();
        } else if (strcmp(op, "PUT_ICE_BLOCK") == 0) {
            scanf("%d %d %d", &R, &C, &H);
            PUT_ICE_BLOCK(R, C, H);
        } else if (strcmp(op, "REMOVE_ICE_BLOCK") == 0) {
            scanf("%d %d %d", &R, &C, &H);
            REMOVE_ICE_BLOCK(R, C, H);
        }
    }
}
int main() {
    scanf("%d %d", &N, &HM);
    scanf("%d %d %d %d", &HR, &HC, &HX, &HY);

    int M;
    scanf("%d", &M);
    main_loop(M);
    return 0;
}