#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Функция, которая возвращает размер максимальной нулевой подматрицы в матрице M
int maxZeroSubmatrix(const vector<vector<int>>& M) {
  // Получаем размеры матрицы
  int n = M.size(); // количество строк
  int m = M[0].size(); // количество столбцов

  // Инициализируем переменную для хранения размера максимальной нулевой подматрицы
  int max_size = 0;

  // Для каждой возможной верхней левой ячейки подматрицы
  for (int i1 = 0; i1 < n; i1++) {
    for (int j1 = 0; j1 < m; j1++) {
      // Если ячейка содержит единицу, то пропускаем ее
      if (M[i1][j1] == 1) continue;
      // Для каждой возможной нижней правой ячейки подматрицы
      for (int i2 = i1; i2 < n; i2++) {
        for (int j2 = j1; j2 < m; j2++) {
          // Проверяем, что все ячейки в подматрице равны нулю
          bool is_zero = true;
          for (int i = i1; i <= i2; i++) {
            for (int j = j1; j <= j2; j++) {
              if (M[i][j] == 1) {
                is_zero = false;
                break;
              }
            }
            if (!is_zero) break;
          }
          // Если все ячейки в подматрице равны нулю, то обновляем размер максимальной нулевой подматрицы
          if (is_zero) {
            int width = j2 - j1 + 1;
            int height = i2 - i1 + 1;
            int size = width * height;
            max_size = max(max_size, size);
          }
        }
      }
    }
  }

  // Возвращаем размер максимальной нулевой подматрицы
  return max_size;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j)
            a[i][j] = str[j] - '0';
    }
    auto start = high_resolution_clock::now();
    maxZeroSubmatrix(a);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl;
    return 0;
}
