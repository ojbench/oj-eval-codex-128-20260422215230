#include <bits/stdc++.h>
using namespace std;

static bool is_win(const array<string,3>& b, char c){
    // rows
    for(int i=0;i<3;i++) if(b[i][0]==c && b[i][1]==c && b[i][2]==c) return true;
    // cols
    for(int j=0;j<3;j++) if(b[0][j]==c && b[1][j]==c && b[2][j]==c) return true;
    // diags
    if(b[0][0]==c && b[1][1]==c && b[2][2]==c) return true;
    if(b[0][2]==c && b[1][1]==c && b[2][0]==c) return true;
    return false;
}

static int win_count(const array<string,3>& b, char c){
    int cnt=0;
    for(int i=0;i<3;i++) cnt += (b[i][0]==c && b[i][1]==c && b[i][2]==c);
    for(int j=0;j<3;j++) cnt += (b[0][j]==c && b[1][j]==c && b[2][j]==c);
    cnt += (b[0][0]==c && b[1][1]==c && b[2][2]==c);
    cnt += (b[0][2]==c && b[1][1]==c && b[2][0]==c);
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<string,3> b;
    for(int i=0;i<3;i++){
        if(!(cin >> b[i])) return 0; // if input missing
        if((int)b[i].size() < 3){
            cout << "invalid\n";
            return 0;
        }
        b[i] = b[i].substr(0,3);
    }

    int cx=0, co=0, empty=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            char ch = b[i][j];
            if(ch=='x') cx++;
            else if(ch=='o') co++;
            else if(ch=='-') empty++;
            else { cout << "invalid\n"; return 0; }
        }
    }

    int dx = cx - co;
    if(dx < 0 || dx > 1){
        cout << "invalid\n"; return 0;
    }

    int wx = win_count(b, 'x');
    int wo = win_count(b, 'o');

    if(wx>0 && wo>0){
        cout << "invalid\n"; return 0;
    }

    if(wx>0){
        if(dx != 1){ cout << "invalid\n"; return 0; }
        // Ensure last move by x created all winning lines
        bool ok=false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(b[i][j]=='x'){
                    auto prev = b;
                    prev[i][j] = '-';
                    // After removing last x, x should not be winning, and counts equal
                    if(!is_win(prev, 'x')){
                        // Also ensure o did not already win in previous state
                        if(!is_win(prev, 'o')){
                            ok = true;
                            break;
                        }
                    }
                }
            }
            if(ok) break;
        }
        if(!ok){ cout << "invalid\n"; return 0; }
        cout << "win\n"; return 0;
    }

    if(wo>0){
        if(dx != 0){ cout << "invalid\n"; return 0; }
        // Ensure last move by o created all winning lines
        bool ok=false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(b[i][j]=='o'){
                    auto prev = b;
                    prev[i][j] = '-';
                    if(!is_win(prev, 'o')){
                        if(!is_win(prev, 'x')){
                            ok = true;
                            break;
                        }
                    }
                }
            }
            if(ok) break;
        }
        if(!ok){ cout << "invalid\n"; return 0; }
        cout << "lose\n"; return 0;
    }

    if(empty==0){
        cout << "tie\n"; return 0;
    }

    cout << "ongoing\n";
    return 0;
}
