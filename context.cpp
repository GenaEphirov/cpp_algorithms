#include <string>
#include <iostream>
#include <vector>

using namespace std;

// вспомогательные функции
void print_ch(char* lt, int l){
    for (int i = 0; i < l; ++i){
        cout << lt[i] << " ";
    } cout << "\n";
}

void print_matrix(vector<vector<int>> v){
    int v_l = v.size();
    for(int i = 0; i < v_l; ++i){
        int vv_l = v[i].size();
        for(int j = 0; j < vv_l; ++j){
            cout << v[i][j] << " ";
        } cout << "\n";
    }
}

void print_3d_matrix(vector<vector<int>> v, int m){
    int row = 0;
    for( int i = 0; i<v.size(); ++i){
        for( int j = 0; j < m; ++j){
            cout << v[i][0] << " ";
        } cout << "\n";
    }
}

/*
2. 
Написать функцию которая принимает строку нажатых клавиш, а возвращает конечный текст.
Функция должна уметь обрабатывать команды 
<left> (стрелка влево), <right> (стрелка вправо), <bspace> (клавиша backspace), <delete> (клавиша delete).
Пример: "12389<left><bspace><delete>45" -> "12345"
*/

void erase(char* list, int length, int pos){
    for (int i = 0; i+pos < length-1; ++i){
        list[pos + i] = list[pos + i + 1];
    }
}

void prepare_place(char* list, int length, int pos){
    for (int i = length - 1; i > pos; --i){
        list[i] = list[i-1];
    }
}

string trainer(string raw_str){
    int l_r = raw_str.length();
    char* cache = new char[l_r];
    int cursor = 0;
    for(int i = 0; i < l_r; ++i){
        char sym = raw_str[i];
        int n_sym = static_cast<int>(sym);
        if(n_sym == static_cast<int>('<')){
            int j = 1;
            string command;
            while(i+j < l_r && static_cast<int>(raw_str[i+j]) != static_cast<int>('>')){
                command += raw_str[i+j];
                ++j;
            }
            if(command == "left"){ --cursor; }
            else if(command == "right"){ ++cursor; }
            else if(command == "bspace"){
                erase(cache, l_r, cursor-1);
                --cursor;
            }
            else if(command == "delete"){ erase(cache, l_r, cursor); }
            i += j;
        } else {
            prepare_place(cache, l_r, cursor);
            cache[cursor] = sym;
            ++cursor;
        }
    }
    string result = static_cast<string>(cache);
    delete[] cache;
    return result;
}

/*
3. 
Написать функцию которая принимает двумерный прямоугольный вектор, 
и возвращает символ, который выстроен 5 в ряд (в том числе и по диагонали).
Задание основывается на игре "крестики-нолики"
*/

int tic_tac_toe(vector<vector<int>> v){
    int n = v.size();
    int m = v[0].size();

    vector<vector<int>> power(n*m, vector<int>(4));
    for(int i = 0; i < n*m; ++i){
        for (int k = 0; k < 4; ++k){
            power[i][k] = 1;
        }
    }

    for (int i = 0; i < n; ++i){
        for (int j=0; j < m; ++j){
            int player = v[i][j];
            if(player == 0){ continue; }
            if(j+1 < m && v[i][j+1] == player){ power[i*m + j+1][0] += power[i*m + j][0]; }
            if(i+1 < n && j+1 < m && v[i+1][j+1] == player){ power[(i+1)*m + j+1][1] += power[i*m + j][1]; }
            if(i+1 < n && v[i+1][j] == player){ power[(i+1)*m + j][2] += power[i*m + j][2]; }
            if(i+1 < n && j-1 >= 0 && v[i+1][j-1] == player){ power[(i+1)*m + j-1][3] += power[i*m + j][3]; }
        }
    }
    int result = 0;
    for(int p = 0; p < n*m; ++p){
        for (int k = 0; k < 4; ++k){
            if(power[p][k] == 5){
                int i = p/m;
                int j = p%m;
                result = v[i][j];
            }
        }
    }
    return result;
}

int main(){
    string t_s = "12389<left><bspace><delete>45";
    cout << t_s << " -> " << trainer(t_s) << "\n";
    
    vector<vector<int>> board{
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 2, 1, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0}
    };
    
    /*
    vector<vector<int>> board( 8, vector<int>( 8 ) );
    for (int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if (i+j == 7 && i >= 3)
            { board[i][j] = 2; }
            else if (i == 3 && 1 <= j && j <= 4)
            { board[i][j] = 1; }
            else 
            { board[i][j] = 0; }
        }
    }
    */
    cout << "tic tac toe winner... " << tic_tac_toe(board) << "\n";

    int wait;
    cin >> wait;
    return 0;
}
